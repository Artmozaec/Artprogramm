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

        //���������� ������ ���� ������ �������� ���������
        virtual bool contentCategory(AnsiString inString);

        //�������� ��������� �����
        virtual void movePointerFront(StringContainer *stringContainer);
private:
	//������� ����
	AnsiString yearPattern;


	AnsiString yearString;

	//�������� �������� �������� �������
	TStringList *timePatterns;

        bool chechYearValue(AnsiString str);

        //������� ���
        int currentYear;
};
#endif