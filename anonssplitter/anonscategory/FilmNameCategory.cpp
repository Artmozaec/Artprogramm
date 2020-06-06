#include "FilmNameCategory.h"
#include "TimeCategory.h"
#include "StringsUtilites.h"

FilmNameCategory::FilmNameCategory(){
}


bool FilmNameCategory::search(StringContainer *stringContainer){
	TimeCategory *timeCategory = new TimeCategory();

        //� ������ ���� �����
	if (!timeCategory->search(stringContainer)) return false;

        //���������� �����
        timeCategory->movePointerFront(stringContainer);

        //���� ������� ����� ��� �����
        if (! stringContainer->searchRussianOrDigit()) return false;

        //���������� ������� �������, ��� - ������ �������� ������
        stringContainer->memoryPosition();

        //���� ������� ������ - ��� ����� �������� ������
        if (! stringContainer->searchString( *new AnsiString("\r\n"))) return false;

        //�� ����������� ������� �� ������
        filmName = stringContainer->getSubstringInMemoryPositionToCurrent();

        //��������������� �������
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


//���������� ������ ���� ������ �������� ���������
bool FilmNameCategory::contentCategory(AnsiString inString){
	return false;
}


void FilmNameCategory::movePointerFront(StringContainer *stringContainer){
	stringContainer->movePointerFrontTo(filmName.Length());
}


