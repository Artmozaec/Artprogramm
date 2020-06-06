#include "TimeCategory.h"
#include "StringContainer.h"

TimeCategory::TimeCategory(){
	//Инициируем паттерны категорий
	timePatterns = new TStringList();
	timePatterns->Add( *(new AnsiString("00.00")));
	timePatterns->Add( *(new AnsiString("00:00")));
}

ShowTime TimeCategory::getTime(){
	return *showTime;
}

bool TimeCategory::search(StringContainer *stringContainer){
        do{
		if (stringContainer->searchPatternList(timePatterns) == StringContainer::NOT_SEARCH) return false;
		showTime = new ShowTime(stringContainer->getSubstringInCurrentPosition(5));
        }while(showTime->getHour() == ShowTime::ERROR_VALUE);
        return true;
}

CategoryType TimeCategory::getCategoryType(){
	return TIME_TYPE;
}

//возвращает истину если строка содержит категорию
bool TimeCategory::contentCategory(AnsiString inString){
        return false;
}


//сместить указатель вперёд
void TimeCategory::movePointerFront(StringContainer *stringContainer){
	stringContainer->movePointerFrontTo(5);
}
