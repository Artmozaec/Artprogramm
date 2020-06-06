#ifndef TimeCategoryH
#define TimeCategoryH
#include <vcl.h>
#include "Category.h"
#include "StringContainer.h"
#include "ShowTime.h"

class TimeCategory:Category{

public:
	TimeCategory();

        ShowTime getTime();
        virtual bool search(StringContainer *stringContainer);
        virtual CategoryType getCategoryType();

        //���������� ������ ���� ������ �������� ���������
        virtual bool contentCategory(AnsiString inString);

        //�������� ��������� �����
        virtual void movePointerFront(StringContainer *stringContainer);
private:
	ShowTime *showTime;

	//�������� �������� �������� �������
	TStringList *timePatterns;
};

#endif

