#include "ShowTime.h"

ShowTime::ShowTime(AnsiString timeString){
	hour = getHourValue(timeString);
	minute = getMinuteValue(timeString);

	if (!checkValue(hour, minute)){
		hour = ERROR_VALUE;
		minute = ERROR_VALUE;
	}
}


int ShowTime::getHour(){
	return hour;
}
int ShowTime::getMinute(){
	return minute;
}

AnsiString ShowTime::getString(){
	if ((hour == ERROR_VALUE) || (minute == ERROR_VALUE)) return *new AnsiString("ньхайю бпелемх!");
        AnsiString hourStr;
        AnsiString minuteStr;

	if (hour<10){
	        hourStr = *new AnsiString("0"+IntToStr(hour));
        }else{
        	hourStr = *new AnsiString(IntToStr(hour));
        }


        if (minute<10){
	        minuteStr = *new AnsiString("0"+IntToStr(minute));
        }else{
	        minuteStr = *new AnsiString(IntToStr(minute));
        }


	return *new AnsiString(hourStr + ':' + minuteStr);
}

ShowTime::ShowTime(int inHour, int inMinut){
	hour = inHour;
	minute = inMinut;
	
	if (!checkValue(hour, minute)){
		hour = ERROR_VALUE;
		minute = ERROR_VALUE;
	}
}

bool ShowTime::checkValue(int inHour, int inMinut){
	if (((0<=inHour) && (inHour<=24)) && ((0<=inMinut)&&(inMinut<=60))) return true;
	return false;
}


int ShowTime::getHourValue(AnsiString timeString){
	int result;
	AnsiString hourStr = timeString.SubString(0,2);
	try{
		result = StrToInt(hourStr);
	}catch(...){
		result = ERROR_VALUE;
	}
	return result;
}

int ShowTime::getMinuteValue(AnsiString timeString){
	int result;
	AnsiString minuteStr = timeString.SubString(4,2);
	try{
		result = StrToInt(minuteStr);
	}catch(...){
		result = ERROR_VALUE;
	}
	return result;

}