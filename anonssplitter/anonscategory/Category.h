#ifndef CategoryH
#define CategoryH
#include <vcl.h>
#include "StringContainer.h"
#include "AnonsCategoryType.cpp"
class Category{

public:
	virtual bool search(StringContainer *stringContainer)=0;

	//Возвращеает тип категории день недели, время итд
	virtual CategoryType getCategoryType()=0;

        //возвращает истину если строка содержит категорию
        virtual bool contentCategory(AnsiString inString)=0;

        //сместить указатель вперёд
        virtual void movePointerFront(StringContainer *stringContainer)=0;
protected:

};
#endif