#ifndef YearCategoryH
#define YearCategoryH
#include <vcl.h>
#include "Category.h"
#include "StringContainer.h"

class YearCategory:Category{

public:
	YearCategory();

        AnsiString getCategoryString();
        virtual bool search(StringContainer *stringContainer);
        virtual CategoryType getCategoryType();

        //возвращает истину если строка содержит категорию
        virtual bool contentCategory(AnsiString inString);

        //сместить указатель вперёд
        virtual void movePointerFront(StringContainer *stringContainer);
private:
	//Паттерн года
	AnsiString yearPattern;


	AnsiString yearString;

	//Содержит описание форматов времени
	TStringList *timePatterns;

        bool chechYearValue(AnsiString str);

        //Текущий год
        int currentYear;
};
#endif