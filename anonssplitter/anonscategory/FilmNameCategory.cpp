#include "FilmNameCategory.h"
#include "TimeCategory.h"
#include "StringsUtilites.h"

FilmNameCategory::FilmNameCategory(){
}


bool FilmNameCategory::search(StringContainer *stringContainer){
	TimeCategory *timeCategory = new TimeCategory();

        //С начала ищем время
	if (!timeCategory->search(stringContainer)) return false;

        //Сдвигаемся вперёд
        timeCategory->movePointerFront(stringContainer);

        //Ищем русские буквы или цифру
        if (! stringContainer->searchRussianOrDigit()) return false;

        //Запоминаем текущую позицию, это - начало названия фильма
        stringContainer->memoryPosition();

        //Ищем перенос строки - это конец названия фильма
        if (! stringContainer->searchString( *new AnsiString("\r\n"))) return false;

        //От запомненной позиции до теущей
        filmName = stringContainer->getSubstringInMemoryPositionToCurrent();

        //Восстанавливаем позицию
        stringContainer->restorePosition();

        return true;
}


AnsiString FilmNameCategory::getCategoryString(){
        AnsiString returnStr = filmName;
        trimString(&returnStr);
        return returnStr;
}

CategoryType FilmNameCategory::getCategoryType(){
	return FILM_NAME_TYPE;

}


//возвращает истину если строка содержит категорию
bool FilmNameCategory::contentCategory(AnsiString inString){
	return false;
}


void FilmNameCategory::movePointerFront(StringContainer *stringContainer){
	stringContainer->movePointerFrontTo(filmName.Length());
}


