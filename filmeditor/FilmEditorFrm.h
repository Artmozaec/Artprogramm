//---------------------------------------------------------------------------


#ifndef FilmEditorFrmH
#define FilmEditorFrmH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <vcl\Clipbrd.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include "Film.h"
#include "WeekDay.h"
#include "FileSearchFrm.h"

#include "ImageViewer.h"
#include "ImageManager.h"
#include "TextSelection.cpp"
#include "ShowTime.h"

//---------------------------------------------------------------------------
class TArtProgramm;
class TFileSearch;
class TFilmEditor : public TFrame
{
__published:	// IDE-managed Components
        TListBox *actors;
        TListBox *directors;
        TListBox *filmNames;

        TEdit *year;

        TLabel *NamesLabel;
        TLabel *ActorsLabel;
        TLabel *YearLabel;
        TLabel *DirectorsLabel;


        TButton *saveChangeButton;
        TButton *fileSearchButton;
        TButton *renameImageFileButton;
        TButton *assignExternalImageButton;

        TPopupMenu *listEditPopup;
        TMemo *filmText;

        TPanel *dayAndChannelPanel;
        TPanel *fileImagesPanel;

        TComboBox *weekDayBox;
        TComboBox *channelBox;
        TComboBox *imageFileBox;


        TImageViewerFrame *imageViewerFrame;
        TMenuItem *MChangeToBased;
        TMenuItem *MDelete;
        TMenuItem *MPasteInBuffer;
	TComboBox *filmTypeBox;
	TLabel *TimeLabel;

        //����� ���� �������� �� ������
        void __fastcall MPasteInBufferClick(TObject *Sender);


        void __fastcall change(TObject *Sender);
        void __fastcall changeWeekDayBox(TObject *Sender);
        void __fastcall saveChangeButtonClick(TObject *Sender);
        void __fastcall channelBoxClick(TObject *Sender);
        void __fastcall fileSearchButtonClick(TObject *Sender);
        void __fastcall imageFileBoxChange(TObject *Sender);
        void __fastcall assignExternalImageButtonClick(TObject *Sender);
        void __fastcall renameImageFileButtonClick(TObject *Sender);
        void __fastcall fieldDblClick(TObject *Sender);
        void __fastcall ListPopUpMenuCreator(TObject *Sender,
          TPoint &MousePos, bool &Handled);
        void __fastcall MDeleteClick(TObject *Sender);
        void __fastcall MChangeToBasedClick(TObject *Sender);
        void __fastcall listHint(TObject *Sender, TShiftState Shift, int X,
          int Y);
        void __fastcall KeyDownListBox(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall fieldToClboard(TObject *Sender);


public:		// User declarations
        __fastcall TFilmEditor(TComponent* Owner);

        //���������� ���������� ������ �� ������
        void showFilm(Film *film);

        //�������� ��������
        void clean();

        //����� ������� �����?
        bool canCloseFilm();

        //////////������� �������� ������///////////////
        void addFilmName(AnsiString inName);
        void addFilmImage(AnsiString imFilmImage);
        void addDirector(AnsiString inDirector);
        void addActor(AnsiString inActor);
        void changeYear(AnsiString inName);
        void changeWeekDay(AnsiString weekDayString);
        void setSelection(TextSelection inTextSelection);
        void setShowTime(ShowTime showTime);
        //���������� �� �������� ������
        bool nameFilmFill();

        //�������-�� ��������, ����-�� ��� �����?
        bool isActive();

        void setImageManager(ImageManager *inImageManager);
private:	// User declarations
        //������ �� ������������� � ������ ������ �����
        Film *film;

        //����������� �����
        TArtProgramm *artDirect;

        //�������� �����������
        ImageManager *imageManager;

        TFileSearch *fileSearchFrm;

        TStringList *createFieldsList();

        TextSelection textSelection;

        //���� ������������ ���������� ��������� � �������� ������ ������
        bool chastity;

        //���� ���������� - �������� ������
        bool active;

        //�������������� ��������� ������������
        void chastityRecovery();

        //��������� ������������
        void chastityDestroy();

        void saveChanges();

        //����������� �������� ����� ����� ����������� ������
        bool allDataCorrect();

        //���������� �����������
        void showImage(AnsiString name);

        //���������� ������
        void showStringEditor(AnsiString *str);

        /////////////���������� ����������� ������//////////////
        void enable();
        void disable();
        /////////////////////////////////////////////////////////
        //��� �� ������� ���� ����������
        bool allBasedFieldFill();

        ////////////���������� ������/////////////
        void setEnableRenameImageFileButton();
        void setEnableAssignExternalImageButton();

	//�������� ������� ����� � ���� ����������� � � ������� ������
        bool nameIsRepeat(AnsiString name);

        //��������� ������ ����� � ������������ � ������
        AnsiString createFileNameString();

        void pasteTextToCliboard(AnsiString text);

};
//---------------------------------------------------------------------------
extern PACKAGE TFilmEditor *FilmEditor;
//---------------------------------------------------------------------------
#endif
