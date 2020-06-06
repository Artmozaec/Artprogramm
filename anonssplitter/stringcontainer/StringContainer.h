//������ �� �������
//������������� ��������, ����������� �������, ���������� ���������


#ifndef StringContainerH
#define StringContainerH
#include "CharClasses.cpp"
#include <vcl.h>
#include "CharClassificator.h"

class StringContainer{

public:
	StringContainer(AnsiString *);

        //���������� ��������� �� ������� � ������ �� �������
        AnsiString getSubstringInMemoryPositionToCurrent();

        //���������� ��������� �� ������� ������� length ��������
	AnsiString getSubstringInCurrentPosition(int length);

	//---------------------------------------------------------------//
	//����� � �������� ��������� ��������� ����������� ����� ������ ���, ����� ��� ������

	//���������� ��������� ����� ������������ ���������� ���������
	static const int NOT_SEARCH = -1;

        ///��������� ������ �������
	//����� ������ �� ������ ������� � ������� ��������, ��������� ������� �������� �������
	bool searchRussian();

        //����� �� ������ ������� ����� ��� �����
        bool searchRussianOrDigit();

        //����� �� ������� �������
	bool searchSymbols();
        //�������� ��� ������������ � �������
        //bool searchEnglish();
        //bool searchDigit();
        ///////////////////////////////////////////////////////////////////

        //����� � ������ ��������
        //� �������� ������� ����� ������ ������������, ����� � ����� ������������ ��� ��������� ����� � ���� (������� ����������)
        bool searchPattern(AnsiString pattern);

        int searchPatternList(TStringList *patterns);

	//����� ������ �� ������ ������� searchStr, ������������ ������� ���������
	bool searchString(AnsiString serchStr);

	//����� ������� �� ������ ������� � ����� �� ����� ������ strings
	int searchStringList(TStringList *searchStrings);


        ////////////////////////////////////////////////////////////////////
        //������ � �������� ���������
        int getCurrentPosition();

        //������� ��������� ����� �� length ��������
        void movePointerFrontTo(int length);
	void memoryPosition();
	void restorePosition();
        //������������� ��������� � �����
        void goToEndPosition();

        void goToStartPosition();

        //��������� �� �������?
        bool isEndPosition();

        /////////////////////////////////////////////////////////////////////


private:

	CharClassificator *charClassificator;

        AnsiString contentStr;

	//��������� �� ������� ������ � ������
        int currentPointer;

	//������ ����������, memoryPosition() - restorePosition()
        int positionMemory;

        //��������� ���������
        const int NOT_DIFINITION;


        /////////////////////////////////////
        //��������� ������� ������������������ �������� ������� ������ �� ������� �������
        //������������ ����� ������ �� ������ � ������� �������� ����������

        //��������� ������� ������������������ ��������, �� ������� position
        bool isPattern(AnsiString patten, int position);

        bool isSearchString(AnsiString searchStr, int position);

        ///////////////////////////////////////

        int findRussian();

        //����� �� ������� �������
        int findSymbols();

        //����� �� ������ ������� ����� ��� �����
        int findRussianOrDigit();

        int findPattern(AnsiString pattern);

        int findString(AnsiString serchStr);
};

//char *findEnglish();

//char *findDigit();
#endif