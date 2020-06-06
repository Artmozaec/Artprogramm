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

        //���������� ������ ���� ������ �������� ���������
        virtual bool contentCategory(AnsiString inString);

        //�������� ��������� �����
        virtual void movePointerFront(StringContainer *stringContainer);
private:
	TStringList *directorLabel;
        AnsiString directorsString;
};
#endif