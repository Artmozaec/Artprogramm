#ifndef TimeH
#define TimeH
#include <vcl.h>
class ShowTime{
public:
	ShowTime(AnsiString timeString);
	ShowTime(int inHour, int inMinut);

        int getHour();
	int getMinute();
        AnsiString getString();

	static const int ERROR_VALUE = -1;
private:
	int hour;
	int minute;
	
	int getHourValue(AnsiString timeString);
	int getMinuteValue(AnsiString timeString);
	bool checkValue(int inHour, int inMinut);
	

};
#endif