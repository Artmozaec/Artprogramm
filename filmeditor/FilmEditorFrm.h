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

        //Пункт меню вставить их буфера
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

        //Отобразить информацию фильма на фрейме
        void showFilm(Film *film);

        //Очистить редактор
        void clean();

        //Можно закрыть фильм?
        bool canCloseFilm();

        //////////ВНЕШНЯЯ РЕДАКЦИЯ ФИЛЬМА///////////////
        void addFilmName(AnsiString inName);
        void addFilmImage(AnsiString imFilmImage);
        void addDirector(AnsiString inDirector);
        void addActor(AnsiString inActor);
        void changeYear(AnsiString inName);
        void changeWeekDay(AnsiString weekDayString);
        void setSelection(TextSelection inTextSelection);
        void setShowTime(ShowTime showTime);
        //Заполненны ли названия фильма
        bool nameFilmFill();

        //Активен-ли редактор, есть-ли там фильм?
        bool isActive();

        void setImageManager(ImageManager *inImageManager);
private:	// User declarations
        //Ссылка на редактируемый в данный момент фильм
        Film *film;

        //Управляющий класс
        TArtProgramm *artDirect;

        //Менеджер изображений
        ImageManager *imageManager;

        TFileSearch *fileSearchFrm;

        TStringList *createFieldsList();

        TextSelection textSelection;

        //Ключ определяющий внесённость изменений в исходные данные фильма
        bool chastity;

        //Ключ активности - редакции фильма
        bool active;

        //Восстановление состояния неизменности
        void chastityRecovery();

        //Нарушение неизменности
        void chastityDestroy();

        void saveChanges();

        //Контрольная проверка полей перед сохранением фильма
        bool allDataCorrect();

        //Отобразить изображение
        void showImage(AnsiString name);

        //Отобразить строку
        void showStringEditor(AnsiString *str);

        /////////////УПРАВЛЕНИЕ АКТИВНОМТЬЮ ФРЕЙМА//////////////
        void enable();
        void disable();
        /////////////////////////////////////////////////////////
        //Все ли базовые поля заполненны
        bool allBasedFieldFill();

        ////////////АКТИВНОСТЬ КНОПОК/////////////
        void setEnableRenameImageFileButton();
        void setEnableAssignExternalImageButton();

	//Проверка повтора имени в базе изображений и в текущем списке
        bool nameIsRepeat(AnsiString name);

        //Генерация нового имени в соответствии с полями
        AnsiString createFileNameString();

        void pasteTextToCliboard(AnsiString text);

};
//---------------------------------------------------------------------------
extern PACKAGE TFilmEditor *FilmEditor;
//---------------------------------------------------------------------------
#endif
