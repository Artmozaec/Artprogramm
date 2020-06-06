#include "WeekDay.h"

const char *WeekDay::EMPTY_WEEK_DAY = "!!! ОШИБКА ДНЯ НЕДЕЛИ !!!";

const char *WeekDay::weekDays[8]={
        EMPTY_WEEK_DAY,
        "понедельник",
        "вторник",
        "среда",
        "четверг",
        "пятница",
        "суббота",
        "воскресенье"
};

WeekDay::WeekDay(AnsiString inDay){
    day=analyzeStringDay(inDay);
}

WeekDay::WeekDay(int inDay){
	if ((inDay>7)||(inDay<0)){
		day=0;
	} else {
		day = inDay;
	}
}

/*
AnsiString WeekDay::getStringToNumber(int dayNumber){
        if ((dayNumber>0) && (dayNumber<=7)){
                return *new AnsiString(WeekDay::weekDays[day]);
        }
        return *new AnsiString(WeekDay::weekDays[0]);

}
*/

TStringList *WeekDay::getDayList(){
        TStringList *dayList = new TStringList();
        dayList->Add( *new AnsiString(weekDays[0]));
        dayList->Add( *new AnsiString(weekDays[1]));
        dayList->Add( *new AnsiString(weekDays[2]));
        dayList->Add( *new AnsiString(weekDays[3]));
        dayList->Add( *new AnsiString(weekDays[4]));
        dayList->Add( *new AnsiString(weekDays[5]));
        dayList->Add( *new AnsiString(weekDays[6]));
        dayList->Add( *new AnsiString(weekDays[7]));

        return dayList;
}



int WeekDay::analyzeStringDay(AnsiString dayStr){
        for (int ch=1; ch<=7; ch++){
             if (dayStr == weekDays[ch]) return ch;
        }
        return 0;
}

AnsiString WeekDay::getDayString(){
        return *new AnsiString(WeekDay::weekDays[day]);

}

int WeekDay::getDayInt(){
        return day;
}


bool WeekDay::nextDay(){
	day++;
	if(day>7){
		day--;
		return false;
	}
	return true;
}

bool WeekDay::equals(WeekDay inWeekDay){
        if (this->getDayInt() == inWeekDay.getDayInt()) return true;
        return false;
}
