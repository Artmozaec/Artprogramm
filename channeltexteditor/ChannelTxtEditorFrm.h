//---------------------------------------------------------------------------


#ifndef ChannelTxtEditorFrmH
#define ChannelTxtEditorFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include "FilmEditorFrm.h"
#include "TextSelection.cpp"
#include "WeekTextMap.h"
#include "FilmsMap.h"

//---------------------------------------------------------------------------
class TFilmEditor;
class WeekTextMap;
class TChannelText : public TFrame
{
__published:	// IDE-managed Components
        TMemo *channelTextEditor;
        TPopupMenu *popupMenu;
	TMenuItem *MTextToFilmName;
        TMenuItem *MToDirector;
        TMenuItem *MToYear;
	TLabel *currentDayLabel;
	TLabel *currentTimeLabel;
        void __fastcall MTextToFilmNameClick(TObject *Sender);
        void __fastcall MToDirectorClick(TObject *Sender);
        void __fastcall MToYearClick(TObject *Sender);
	void __fastcall channelTextEditorKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall channelTextEditorClick(TObject *Sender);
	void __fastcall channelTextEditorContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
	void __fastcall channelTextEditorChange(TObject *Sender);

public:		// User declarations
        __fastcall TChannelText(TComponent* Owner);
        //Показать файл по пути patch и установить курсор в position
        void showText(TStringList *textList, TextSelection selection);

        //Текст из редактора
        AnsiString *getText();

        void setSelection(TextSelection selection);
        void changeFilmEditor(TFilmEditor *inFilmEditor);

        //Были-ли изменения
        bool isChanged();
private:	// User declarations
        TFilmEditor *filmEditor;

        //соответствие позиици в тексте дню недели
        WeekTextMap *weekTextMap;

	//Карта фильмов
        FilmsMap *filmsMap;

        //Управляющий класс
        TArtProgramm *artDirect;

        void createWeekTextMap();

        void createFilmMap();

        void dayLabelRefresh();

        void timeLabelRefresh();

        void destroyMaps();

        //Выделенный фрагмент год?
        bool isYearSelected();

        //Если изменений в тексте небыло, оно false
        bool chastity;

};
//---------------------------------------------------------------------------
extern PACKAGE TChannelText *ChannelText;
//---------------------------------------------------------------------------
#endif
