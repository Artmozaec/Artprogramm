#include "YearCategory.h"
#include <DateUtils.hpp>

YearCategory::YearCategory(){
	yearPattern = *new AnsiString("0000");

        TDateTime currentDate = Date();

        currentYear = YearOf(currentDate);
}

AnsiString YearCategory::getCategoryString(){
	return yearString;
}


bool YearCategory::search(StringContainer *stringContainer){
	do{
        	if (!stringContainer->searchPattern(yearPattern)) return false;
        	yearString = stringContainer->getSubstringInCurrentPosition(yearPattern.Length());
                movePointerFront(stringContainer);
        }while(!chechYearValue(yearString));
        return true;
}

CategoryType YearCategory::getCategoryType(){
	return YEAR_TYPE;
}

//возвращает истину если строка содержит категорию
bool YearCategory::contentCategory(AnsiString inString){
        StringContainer *container = new StringContainer(&inString);
        if (container->searchPattern(yearPattern)) return true;
        return false;

}


bool YearCategory::chechYearValue(AnsiString str){
        int val;
	try{
		val = StrToInt(str);
        }catch(...){
        	return false;
        }

        if ((1920<=val) && (val<=currentYear)) return true;
        return false;
}

void YearCategory::movePointerFront(StringContainer *stringContainer){
	stringContainer->movePointerFrontTo(yearPattern.Length());
}
