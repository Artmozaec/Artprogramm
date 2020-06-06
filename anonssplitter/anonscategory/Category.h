#ifndef CategoryH
#define CategoryH
#include <vcl.h>
#include "StringContainer.h"
#include "AnonsCategoryType.cpp"
class Category{

public:
	virtual bool search(StringContainer *stringContainer)=0;

	//����������� ��� ��������� ���� ������, ����� ���
	virtual CategoryType getCategoryType()=0;

        //���������� ������ ���� ������ �������� ���������
        virtual bool contentCategory(AnsiString inString)=0;

        //�������� ��������� �����
        virtual void movePointerFront(StringContainer *stringContainer)=0;
protected:

};
#endif