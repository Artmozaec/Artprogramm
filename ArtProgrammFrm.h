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
        //������ ����� ���� ������
        void newChannelDetected(AnsiString fileName);

        //����� ���� ������
        void deleteChannelDetected(AnsiString fileName);

        //���������� ����� � ����� ������
        bool showFilm(Film *film);

        //���������� ����� ������
        bool showTextChannel(AnsiString channelName);

        //�������� ������ � ����������
        void refresh();

        //���������� ������ ��������� �������
        TStringList *getCurrentChannelsList();


        //���������� ����� ������ ��������
        //��� ���� ������������ ������ �� ����� ������� �� �������� �� � ����� �������
        AnsiString showFreeFileSelector();

        //������, ��������� � ��������� � ���������� ����� �����
        void addNewFilm();

        //��������� �� ������
        void saveSession();

        //��������� �������� �� ����������� �������
        void stopTrackingAnonsFolder();
private:	// User declarations
	//���������� � ����������� ����� �� ������� ���������� �������
	FileAnonsObserver *fileAnonsObserver;

	//������ ��� ������ - ��������� ������
	FilmContainer *filmContainer;

	//������ ��������� ������� ������
	ChannelFilesAndNames *channelFilesAndNames;

	//�������� �����������
	ImageManager *imageManager;

	Film *newFilmCreator();

	//������� ��������� � ������ �����
	void deleteSelectedFilm();

	//������� ���������� ����� �� ���������� �������
	void clearSelectedChannel();

	//�������� ��� ������ ������ ����� ������
	void showChannelText(AnsiString fileName, TextSelection selection);

	//�������� �������
	SessionManager *sessionManager;
		
	//�������� ��������
	SettingsManager *settingsManager;

        //
        ReplaceAnonsTextChecker *replaceAnonsTextChecker;
};
//---------------------------------------------------------------------------
extern PACKAGE TArtProgramm *ArtProgramm;
//---------------------------------------------------------------------------
#endif
