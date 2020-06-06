//---------------------------------------------------------------------------

#ifndef ArtProgrammFrmH
#define ArtProgrammFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AnonsTree.h"
#include "ChannelTxtEditorFrm.h"
#include "FilmEditorFrm.h"
#include "FileAnonsObserver.h"
#include <ImgList.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "ImageManager.h"
#include "SessionManager.h"
#include "SettingsManager.h"
#include <Buttons.hpp>
#include "ReplaceAnonsTextChecker.h"
#include "ChannelFilesAndNames.h"
#include "FilmsInWeekDaysFrm.h"

class ReplaceAnonsTextChecker;
//class ChannelFilesAndNames;
//---------------------------------------------------------------------------
class TArtProgramm : public TForm
{
__published:	// IDE-managed Components
        TAnonsTree *anonsTree;
        TFilmEditor *filmEditor;
        TChannelText *channelTextEditor;
        TImageList *actionImages;

        TActionList *actionList;
        TAction *ANewFilm;
        TAction *ADeleteFilm;
        TAction *ACloseSession;
        TAction *ANewSession;
	TAction *ASplitFilmsInCurrentChannel;

        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;

        TButton *closeSessionButton;
        TButton *startNewSessionButton;
	TButton *refreshButton;
	TButton *historyButton;
	TButton *settingsButton;
	TButton *anonsSplitButon;

	TGroupBox *trackingGroup;
	TSpeedButton *speedButtonTracking;
	TFilmsInWeekDaysFrame *filmsInWeekDaysFrame;

        void __fastcall ANewFilmExecute(TObject *Sender);
        void __fastcall ADeleteExecute(TObject *Sender);
        void __fastcall ACloseSessionExecute(TObject *Sender);
        void __fastcall ANewSessionExecute(TObject *Sender);
	void __fastcall ASplitFilmsInCurrentChannelExecute(TObject *Sender);
	void __fastcall refreshButtonClick(TObject *Sender);
	void __fastcall speedButtonTrackingClick(TObject *Sender);
	void __fastcall historyButtonClick(TObject *Sender);
	void __fastcall settingsButtonClick(TObject *Sender);

public:		// User declarations
        __fastcall TArtProgramm(TComponent* Owner);
        //Найден новый файл канала
        void newChannelDetected(AnsiString fileName);

        //Удалён файл канала
        void deleteChannelDetected(AnsiString fileName);

        //Отобразить фильм и текст анонса
        bool showFilm(Film *film);

        //Отобразить текст анонса
        bool showTextChannel(AnsiString channelName);

        //Обновить кнопки и компоненты
        void refresh();

        //Возвращает список доступных каналов
        TStringList *getCurrentChannelsList();


        //Показывает форму выбора картинки
        //При этом отображаются только те файлы которые не связвнны не с одним фильмом
        AnsiString showFreeFileSelector();

        //создаёт, добавляет в контейнер и отображает новый фильм
        void addNewFilm();

        //Сохраняет всё дерево
        void saveSession();

        //Остановка слежения за директорией анонсов
        void stopTrackingAnonsFolder();
private:	// User declarations
	//Обозревает и отслеживает файлы во входной директории текстов
	FileAnonsObserver *fileAnonsObserver;

	//Хранит всю сессию - созданные фильмы
	FilmContainer *filmContainer;

	//Хранит доступные текущие каналы
	ChannelFilesAndNames *channelFilesAndNames;

	//Менеджер изображений
	ImageManager *imageManager;

	Film *newFilmCreator();

	//Удаляет выбранный в дереве фильм
	void deleteSelectedFilm();

	//Очищает выделенный канал от сохранённых фильмов
	void clearSelectedChannel();

	//Операции при показе нового файла анонса
	void showChannelText(AnsiString fileName, TextSelection selection);

	//Менеджер сессиий
	SessionManager *sessionManager;
		
	//Менеджер настроек
	SettingsManager *settingsManager;

        //
        ReplaceAnonsTextChecker *replaceAnonsTextChecker;
};
//---------------------------------------------------------------------------
extern PACKAGE TArtProgramm *ArtProgramm;
//---------------------------------------------------------------------------
#endif
