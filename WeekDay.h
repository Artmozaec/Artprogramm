#ifndef WeekDayH
#define WeekDayH
#include <vcl.h>

class WeekDay{
public:
	WeekDay(int inDay);
        WeekDay(AnsiString inDay);
	AnsiString getDayString();
	int getDayInt();


	//Сдвигает значение объекта на 1 день вперёд
	bool nextDay();

	//Сравнение двух дней недели
	bool equals(WeekDay inWeekDay);

        //Список дней недели
        static TStringList *getDayList();

        //Название дня недели
        //static AnsiString getStringToNumber(int dayNumber);

        static const char *EMPTY_WEEK_DAY;
private:
	int day;
        static const char *weekDays[];

        int analyzeStringDay(AnsiString dayStr);

};


#endif