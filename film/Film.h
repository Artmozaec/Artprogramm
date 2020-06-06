#ifndef FilmSplitterH
#define FilmSplitterH
#include <vcl.h>
#include "WeekDay.h"
#include "ShowTime.h"
#include "TextSelection.cpp"
#include "FilmType.cpp"

class Film{
public:
	Film(int inWeekDay, AnsiString inChannel);

	/////////////////////////////////////////////////////////
	WeekDay getWeekDay();
	void setWeekDay(int newWeekDay);
        void setWeekDay(WeekDay newWeekDay);

	AnsiString getChannel();
	void setChannel(AnsiString inChannel);

        /////////////////»Ã≈Õ¿ ‘»À‹Ã¿///////////////////////
	TStringList *getFilmNames();
        void setFilmNames(TStringList *inNames);
        AnsiString getBaseFilmName();
        void setBaseFilmName(AnsiString baseName);

	TStringList *getDirectors();
        void setDirectors(TStringList *inDirectors);

	TStringList *getActors();
        void setActors(TStringList *inActors);

	AnsiString getYear();
        void setYear(AnsiString inYear);




        ////////////////////»«Œ¡–¿∆≈Õ»ﬂ —¬ﬂ«¿ÕÕ€≈ — ‘»À‹ÃŒÃ/////////////
        TStringList *getImageNames();
        void setImageNames(TStringList *inImages);
        AnsiString getBaseImageName();
        void setBaseImageName(AnsiString baseName);
	bool imageExist();

        /////////////////////¬˚‰ÂÎÂÌËÂ/////////////////
        TextSelection getSelection();
        void setSelection(TextSelection newSelection);

        /////////////////////¬ÂÏˇ œÓÍ‡Á‡//////////////
        void setShowTime(ShowTime inShowTime);
        ShowTime getShowTime();


        ////////////////////“ËÔ ÙËÎ¸Ï‡/////////////////
        FilmType getType();
        void setFilmType(FilmType inType);
        AnsiString getTypeString();
private:

	TStringList *filmNames;
	TStringList *directors;
	TStringList *actors;
        TStringList *filmImages;

        TextSelection textSelection;

        AnsiString filmYear;
	AnsiString channel;

	WeekDay *weekDay;

        ShowTime *showTime;

        FilmType filmType;

};


#endif