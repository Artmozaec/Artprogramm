#ifndef DirectorCategoryH
#define DirectorCategoryH
#include <vcl.h>
#include "Category.h"
#include "StringContainer.h"

class DirectorCategory:Category{
public:
	DirectorCategory();

        TStringList *getCategoryList();

        virtual bool search(StringContainer *stringContainer);
        virtual CategoryType getCategoryType();

        //возвращает истину если строка содержит категорию
        virtual bool contentCategory(AnsiString inString);

        //сместить указатель вперёд
        virtual void movePointerFront(StringContainer *stringContainer);
private:
	TStringList *directorLabel;
        AnsiString directorsString;
};
#endif