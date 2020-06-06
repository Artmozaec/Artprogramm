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

        //возвращает истину если строка содержит категорию
        virtual bool contentCategory(AnsiString inString);

        //сместить указатель вперёд
        virtual void movePointerFront(StringContainer *stringContainer);
private:
	ShowTime *showTime;

	//Содержит описание форматов времени
	TStringList *timePatterns;
};

#endif

