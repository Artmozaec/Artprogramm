#include "DirectorCategory.h"
#include "StringContainer.h"
#include "StringsUtilites.h"

DirectorCategory::DirectorCategory(){
	directorLabel = new TStringList();
        directorLabel->Add( *new AnsiString("���������"));
        directorLabel->Add( *new AnsiString("��������"));
        directorLabel->Add( *new AnsiString("��������"));
        directorLabel->Add( *new AnsiString("�������"));
        directorLabel->Add( *new AnsiString("�������"));
        directorLabel->Add( *new AnsiString("������"));


        //��������� ������ �
        directorLabel->Add( *new AnsiString("����c����"));
        directorLabel->Add( *new AnsiString("����c���"));
        directorLabel->Add( *new AnsiString("����c���"));
        directorLabel->Add( *new AnsiString("����c��"));
        directorLabel->Add( *new AnsiString("����c��"));



        //��������� ������ �
        directorLabel->Add( *new AnsiString("�����c���"));
        directorLabel->Add( *new AnsiString("�����c��"));
        directorLabel->Add( *new AnsiString("�����c��"));

}


//������ �� directorsString
TStringList *DirectorCategory::getCategoryList(){
        AnsiString text = directorsString;
        trimString(&text);
        AnsiString delimiters = *new AnsiString(",");
        TStringList *result = new TStringList();

        if (directorsString.IsEmpty()) return result;
        int end = 0;


        while ((end = text.Pos(delimiters)) != 0){
		result->Add(text.SubString(0, end-1).Trim());
                text = text.SubString(end+1, text.Length());
        }

        result->Add(text.Trim());

        return result;
}

bool DirectorCategory::search(StringContainer *stringContainer){
	//���� ������ ���������
        int searchIndex = stringContainer->searchStringList(directorLabel);

	if (searchIndex == StringContainer::NOT_SEARCH) return false;

        //��������� ����� �� ������ �����
        stringContainer->movePointerFrontTo(directorLabel->Strings[searchIndex].Length());

	//���������� ������� �������
        stringContainer->memoryPosition();

        //���� ������� ������
	stringContainer->searchString( *new AnsiString("\r\n"));

        directorsString = stringContainer->getSubstringInMemoryPositionToCurrent();

        //��������������� �������
        stringContainer->restorePosition();

        return true;
}


CategoryType DirectorCategory::getCategoryType(){
	return DIRECTOR_TYPE;
}

//���������� ������ ���� ������ �������� ���������
bool DirectorCategory::contentCategory(AnsiString inString){
	return false;
}

void DirectorCategory::movePointerFront(StringContainer *stringContainer){
	stringContainer->movePointerFrontTo(directorsString.Length());
}
