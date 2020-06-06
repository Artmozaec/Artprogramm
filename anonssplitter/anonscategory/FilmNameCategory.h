#ifndef FilmNameCategoryH
#define FilmNameCategoryH
#include <vcl.h>
#include "Category.h"
#include "StringContainer.h"

class FilmNameCategory:Category{
public:
	FilmNameCategory();

        AnsiString getCategoryString();
        virtual bool search(StringContainer *stringContainer);
        virtual CategoryType getCategoryType();

        //возвращает истину если строка содержит категорию
        virtual bool contentCategory(AnsiString inString);

        //сместить указатель вперёд
        virtual void movePointerFront(StringContainer *stringContainer);
private:
	AnsiString filmName;

};
#endif