//---------------------------------------------------------------------------


#ifndef FilmsInWeekDaysFrmH
#define FilmsInWeekDaysFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include "FilmContainer.h"

//---------------------------------------------------------------------------
class TFilmsInWeekDaysFrame : public TFrame
{
__published:	// IDE-managed Components
        TListBox *weekDaysList;
        TListBox *filmsDaySum;
        void __fastcall weekDaysListDblClick(TObject *Sender);
        void __fastcall selectReset(TObject *Sender);
public:		// User declarations

        __fastcall TFilmsInWeekDaysFrame(TComponent* Owner);
        void refresh();

        void setFilmContainer(FilmContainer *inFilmContainer);
private:	// User declarations

        //Контейнер
	FilmContainer *filmContainer;

        void updateWeekDaySum();
        void buildDayFilmsList();
};
//---------------------------------------------------------------------------
extern PACKAGE TFilmsInWeekDaysFrame *FilmsInWeekDaysFrame;
//---------------------------------------------------------------------------
#endif
