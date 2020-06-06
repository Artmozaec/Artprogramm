#ifndef WeekDayCategoryH
#define WeekDayCategoryH
#include <vcl.h>
#include "Category.h"
#include "StringContainer.h"
#include "WeekDay.h";

class WeekDayCategory:Category{

public:
	WeekDayCategory();

        virtual bool search(StringContainer *stringContainer);
        virtual CategoryType getCategoryType();
        //���������� ������ ���� ������ �������� ���������
        virtual bool contentCategory(AnsiString inString);


	WeekDay getWeekDay();

        //�������� ��������� �����
        virtual void movePointerFront(StringContainer *stringContainer);
private:
	const int NOT_DIFINITION; //�� ��������
	//������ ��������� ���������
	AnsiString *endCategory;

	//�������� �������� �������� �������
	TStringList *weekDays;

	//�������� ������ ���������� ��� ������
	int dayIndex;

        bool isTrueWeekDay(StringContainer *stringContainer);

};

#endif
