//---------------------------------------------------------------------------

#ifndef FileAnonsObserverH
#define FileAnonsObserverH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TArtProgramm;
class FileAnonsObserver : public TThread
{
public:
        __fastcall FileAnonsObserver(bool CreateSuspended, TArtProgramm *inListener);

        //Очищает лист файлов
        void clear();

        //Даёт список файлов
        TStringList *getFilesList();

        //Возвращает текст заключённый в fileName
        TStringList *getChannelText(AnsiString fileName);

        //остановить слежение
        void stopTracking();

        //Возобновить слежение
        void startTracking();

        //Запускает процесс поиска новых файлов
	void __fastcall refresh();
		
		void setAnonsTextPatch(AnsiString inAnonsTextPatch);
protected:
        void __fastcall Execute();

private:
	//Слушатель метод которого вызывается при обнаружении новых файлов
	TArtProgramm *listener;

        //Путь к папке с текстами анонсов
        AnsiString anonsTextPatch;

        //лист в котором хранится основной список файлов анонсов
        TStringList *anonsFiles;

        //Поиск добавленных в папку анонсов файлов
        void searchAddedFiles(TStringList *folderContent);

        //Поиск удалённых из папки анонсов файлов
        void searchDeletedFiles(TStringList *folderContent);

        //Если он истина - происходит просмотр директории анонсов
        bool observe;
};
//---------------------------------------------------------------------------
#endif
