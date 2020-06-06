#ifndef WeekDayH
#define WeekDayH
#include <vcl.h>

class WeekDay{
public:
	WeekDay(int inDay);
        WeekDay(AnsiString inDay);
	AnsiString getDayString();
	int getDayInt();


	//�������� �������� ������� �� 1 ���� �����
	bool nextDay();

	//��������� ���� ���� ������
	bool equals(WeekDay inWeekDay);

        //������ ���� ������
        static TStringList *getDayList();

        //�������� ��� ������
        //static AnsiString getStringToNumber(int dayNumber);

        static const char *EMPTY_WEEK_DAY;
private:
	int day;
        static const char *weekDays[];

        int analyzeStringDay(AnsiString dayStr);

};


#endif