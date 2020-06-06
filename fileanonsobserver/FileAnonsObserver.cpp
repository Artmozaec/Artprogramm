//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#pragma package(smart_init)
#include "ArtProgrammFrm.h"
#include "FileAnonsObserver.h"
#include "FileOperations.cpp"
#include "FileReaderWriter.h"

#include <SysUtils.hpp>
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall FileAnonsObserver::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall FileAnonsObserver::FileAnonsObserver(bool CreateSuspended, TArtProgramm *inListener)
        : TThread(CreateSuspended)
{
        listener = inListener;
        anonsTextPatch = *new AnsiString();
        anonsFiles = new TStringList();

        //Сразу запускаем просмотр
        observe = true;
}


//Поиск добавленных в папку анонсов файлов
void FileAnonsObserver::searchAddedFiles(TStringList *folderContent){
        for (int ch=0; ch<folderContent->Count; ch++){
                 //Если текущей строки нет в основном списке
                 if (anonsFiles->IndexOf(folderContent->Strings[ch]) == -1){
                        //Добавляем имя файла в основной срисок
                        anonsFiles->Add(folderContent->Strings[ch]);

                        //Вызываем метод члушателя - новый файл!
                        listener->newChannelDetected(folderContent->Strings[ch]);

                 }
        }
}


//Поиск удалённых из папки анонсов файлов
void FileAnonsObserver::searchDeletedFiles(TStringList *folderContent){

        int ch=0;
        while (ch<anonsFiles->Count){
                //Если не найдена строка основного списка в текущем содержимом
                //Значит файл удалён!
                if (folderContent->IndexOf(anonsFiles->Strings[ch]) == -1){
                        //Метод слушателя файл удалён
                        listener->deleteChannelDetected(anonsFiles->Strings[ch]);


                        //Удаляем имя файла из внутреннего спска
                        anonsFiles->Delete(ch);

                        //Продливаем цикл без итерации ch
                        continue;
                }

                ch++;
       }
}


//Запускает процесс поиска новых файлов
void __fastcall FileAnonsObserver::refresh(){
	TStringList *folderContent = new TStringList();
        //ShowMessage("refre");
	if (DirectoryExists(anonsTextPatch)){
		//Получаем список файлов из директории анонсов на текущий момент
		getDirectoryContent(anonsTextPatch, folderContent);

		//Ищем добавленные файлы
		searchAddedFiles(folderContent);

		//Ищем удалённые файлы
		searchDeletedFiles(folderContent);
	} else {
        	ShowMessage("Не доступна папка анонсов! Наблюдение приостановлено");
                observe = false;
                listener->stopTrackingAnonsFolder();
	}
}

//---------------------------------------------------------------------------
void __fastcall FileAnonsObserver::Execute()
{
        //---- Place thread code here ----
        while (!Terminated){
                if (observe) Synchronize(refresh);
                Sleep(10000);
        }
}

TStringList *FileAnonsObserver::getChannelText(AnsiString fileName){
	TStringList *textList;
	FileReaderWriter *reader = new FileReaderWriter();

        textList = reader->readDosText(anonsTextPatch+fileName);

        return textList;
}



//остановить слежение
void FileAnonsObserver::stopTracking(){
	observe = false;
}

//Возобновить слежение
void FileAnonsObserver::startTracking(){
	observe = true;
}

void FileAnonsObserver::setAnonsTextPatch(AnsiString inAnonsTextPatch){
	anonsTextPatch = inAnonsTextPatch;
}
//---------------------------------------------------------------------------
