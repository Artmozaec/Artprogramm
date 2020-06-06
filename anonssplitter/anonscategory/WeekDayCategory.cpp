#include "WeekDayCategory.h"
#include <cassert>

WeekDayCategory::WeekDayCategory():
NOT_DIFINITION(-1)
{

	//������ �� ��������
	dayIndex = NOT_DIFINITION;
	
	//���������� ��� ������

    weekDays =  new TStringList();
    weekDays->Add( *(new AnsiString("�� ���� ������")));
    weekDays->Add( *(new AnsiString("�����������")));
    weekDays->Add( *(new AnsiString("�������")));
    weekDays->Add( *(new AnsiString("�����")));
    weekDays->Add( *(new AnsiString("�������")));
    weekDays->Add( *(new AnsiString("�������")));
    weekDays->Add( *(new AnsiString("�������")));
    weekDays->Add( *(new AnsiString("������")));
    weekDays->Add( *(new AnsiString("�����������")));
}


WeekDay WeekDayCategory::getWeekDay(){
        assert(dayIndex != NOT_DIFINITION);
	//(������ - �������)
        if (dayIndex == 7) return *new WeekDay(weekDays->Strings[dayIndex-1]);
        return *new WeekDay(weekDays->Strings[dayIndex]);
}

bool WeekDayCategory::search(StringContainer *stringContainer){
	//�������� ������ ���������� ��� � ������
        do{
		dayIndex = stringContainer->searchStringList(weekDays);

		//���� �� ���� �� ����� �� �������
		if (dayIndex==stringContainer->NOT_SEARCH){
			dayIndex = NOT_DIFINITION;
			return false;
                }

                //���� ��������� ������������������ ��������� ��������
                if (isTrueWeekDay(stringContainer)){
                     return true;
                } else {
                     movePointerFront(stringContainer);
                }
        }while(true);


        return true;
}

bool WeekDayCategory::isTrueWeekDay(StringContainer *stringContainer){
	//���������� ������� �������
        stringContainer->memoryPosition();

        //���� ������� ������
        if (!stringContainer->searchSymbols()) return false;

        AnsiString weekDayStr = stringContainer->getSubstringInMemoryPositionToCurrent();

	stringContainer->restorePosition();

        if (weekDays->Strings[dayIndex] == weekDayStr) return true;

        return false;
}

//���������� ������ ���� ������ �������� ���������
bool WeekDayCategory::contentCategory(AnsiString inString){
	return false;
}

CategoryType WeekDayCategory::getCategoryType(){
	return WEEK_DAY_TYPE;
}



void WeekDayCategory::movePointerFront(StringContainer *stringContainer){
	assert(dayIndex != NOT_DIFINITION);
	stringContainer->movePointerFrontTo(weekDays->Strings[dayIndex].Length());
}
