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
        //возвращает истину если строка содержит категорию
        virtual bool contentCategory(AnsiString inString);


	WeekDay getWeekDay();

        //сместить указатель вперёд
        virtual void movePointerFront(StringContainer *stringContainer);
private:
	const int NOT_DIFINITION; //Не определён
	//Строка окончания категории
	AnsiString *endCategory;

	//Содержит описание форматов времени
	TStringList *weekDays;

	//Содержит индекс найденного дня недели
	int dayIndex;

        bool isTrueWeekDay(StringContainer *stringContainer);

};

#endif
