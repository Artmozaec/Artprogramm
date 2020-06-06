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

        //���������� ������ ���� ������ �������� ���������
        virtual bool contentCategory(AnsiString inString);

        //�������� ��������� �����
        virtual void movePointerFront(StringContainer *stringContainer);
private:
	AnsiString filmName;

};
#endif