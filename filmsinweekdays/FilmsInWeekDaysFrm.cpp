//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FilmsInWeekDaysFrm.h"
#include "WeekDay.h"
#include "FilmContainerUtilites.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFilmsInWeekDaysFrame *FilmsInWeekDaysFrame;
//---------------------------------------------------------------------------
__fastcall TFilmsInWeekDaysFrame::TFilmsInWeekDaysFrame(TComponent* Owner)
        : TFrame(Owner)
{

}

//---------------------------------------------------------------------------


void TFilmsInWeekDaysFrame::refresh(){
        WeekDay *day = new WeekDay(1);
        do{
                filmsDaySum->Items->Strings[day->getDayInt()-1] = IntToStr(getImagesInDay(*day, filmContainer));
        }while(day->nextDay());

        //Снимаем выделение, на всякий случай, для красоты
        weekDaysList->ItemIndex = -1;
}


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void TFilmsInWeekDaysFrame::setFilmContainer(FilmContainer *inFilmContainer){
        filmContainer = inFilmContainer;
}

void __fastcall TFilmsInWeekDaysFrame::weekDaysListDblClick(TObject *Sender)
{
        /*
        WeekDay *day = new WeekDay(weekDaysList->ItemIndex+1);
        imageManager->openDayFolder(*day);
        */
        weekDaysList->ItemIndex = -1;

}


void __fastcall TFilmsInWeekDaysFrame::selectReset(TObject *Sender)
{
        filmsDaySum->ItemIndex = -1;
}
//---------------------------------------------------------------------------

