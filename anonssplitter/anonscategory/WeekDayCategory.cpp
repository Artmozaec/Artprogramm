#include "WeekDayCategory.h"
#include <cassert>

WeekDayCategory::WeekDayCategory():
NOT_DIFINITION(-1)
{

	//Индекс не определён
	dayIndex = NOT_DIFINITION;
	
	//Инициируем дни недели

    weekDays =  new TStringList();
    weekDays->Add( *(new AnsiString("НЕ ДЕНЬ НЕДЕЛИ")));
    weekDays->Add( *(new AnsiString("понедельник")));
    weekDays->Add( *(new AnsiString("вторник")));
    weekDays->Add( *(new AnsiString("среда")));
    weekDays->Add( *(new AnsiString("четверг")));
    weekDays->Add( *(new AnsiString("пятница")));
    weekDays->Add( *(new AnsiString("суббота")));
    weekDays->Add( *(new AnsiString("субота")));
    weekDays->Add( *(new AnsiString("воскресенье")));
}


WeekDay WeekDayCategory::getWeekDay(){
        assert(dayIndex != NOT_DIFINITION);
	//(субота - суббота)
        if (dayIndex == 7) return *new WeekDay(weekDays->Strings[dayIndex-1]);
        return *new WeekDay(weekDays->Strings[dayIndex]);
}

bool WeekDayCategory::search(StringContainer *stringContainer){
	//Получаем индекс найденного дня в списке
        do{
		dayIndex = stringContainer->searchStringList(weekDays);

		//Если ни одна из строк не найдена
		if (dayIndex==stringContainer->NOT_SEARCH){
			dayIndex = NOT_DIFINITION;
			return false;
                }

                //Если найденная последовательность кончается символом
                if (isTrueWeekDay(stringContainer)){
                     return true;
                } else {
                     movePointerFront(stringContainer);
                }
        }while(true);


        return true;
}

bool WeekDayCategory::isTrueWeekDay(StringContainer *stringContainer){
	//Запоминаем текущую позицию
        stringContainer->memoryPosition();

        //Ищем впереди символ
        if (!stringContainer->searchSymbols()) return false;

        AnsiString weekDayStr = stringContainer->getSubstringInMemoryPositionToCurrent();

	stringContainer->restorePosition();

        if (weekDays->Strings[dayIndex] == weekDayStr) return true;

        return false;
}

//возвращает истину если строка содержит категорию
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
