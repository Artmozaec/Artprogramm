#include "StringContainer.h"
#include <cassert>

#include <SysUtils.hpp>
StringContainer::StringContainer(AnsiString *inStr):
	NOT_DIFINITION(-1)
{
        contentStr = *inStr;

        currentPointer = 1;

	positionMemory = NOT_DIFINITION;

        charClassificator = new CharClassificator();
}


//���������� ��������� �� ������� � ������ �� �������
AnsiString StringContainer::getSubstringInMemoryPositionToCurrent(){
        if (positionMemory == NOT_DIFINITION) return NULL;
	return contentStr.SubString(positionMemory, currentPointer-positionMemory);
}

//���������� ��������� �� ������� ������� length ��������
AnsiString StringContainer::getSubstringInCurrentPosition(int length){
        AnsiString result;
        result = contentStr.SubString(currentPointer, length);
        return result;

}


//////////////////������ ����� ������///////////////////////////////
//����� �� ������ ����� ��� �����
bool StringContainer::searchRussianOrDigit(){
	//���� ������� ����� ��� �����
	int findPtr = findRussianOrDigit();
        if (findPtr == NOT_SEARCH) return false;
        currentPointer = findPtr;
        return true;
}

//����� �� ������ ������� ����� ��� �����
int StringContainer::findRussianOrDigit(){
	CharClass curClass;
	for (int ch=currentPointer; ch<contentStr.Length(); ch++){
		curClass = charClassificator->classificateCurrentChar(contentStr[ch]);
           	if ((curClass == RUSSIAN_UPPERCASE) || (curClass == RUSSIAN_LOWERCASE) || (curClass == DIGITS))
                {
                	return ch;
		}
        }

        return NOT_SEARCH;
}

bool StringContainer::searchRussian(){
	//���� ������� �����
	int findPtr = findRussian();
        if (findPtr == NOT_SEARCH) return false;
        currentPointer = findPtr;
        return true;
}


int StringContainer::findRussian(){
	CharClass curClass;
	for (int ch=currentPointer; ch<contentStr.Length(); ch++){
		curClass = charClassificator->classificateCurrentChar(contentStr[ch]);
           	if ((curClass == RUSSIAN_UPPERCASE) || (curClass == RUSSIAN_LOWERCASE))
                {
                	return ch;
		}
        }

        return NOT_SEARCH;
}


bool StringContainer::searchSymbols(){
	int findPtr = findSymbols();
        if (findPtr == NOT_SEARCH) return false;
        currentPointer = findPtr;
        return true;
}


int StringContainer::findSymbols(){
	CharClass curClass;
	for (int ch=currentPointer; ch<contentStr.Length(); ch++){
		curClass = charClassificator->classificateCurrentChar(contentStr[ch]);
           	if ((curClass == SYMBOLS) || (curClass == DIRECTION))
                {
                	return ch;
		}
        }

        return NOT_SEARCH;
}

/////////����� ��������� � ������////////////////////


//����� ������ �� ������ ������� searchStr, ������������ ������� ���������
bool StringContainer::searchString(AnsiString searchStr){
	int findPtr = findString(searchStr);
        if (findPtr == NOT_SEARCH) return false;
        currentPointer = findPtr;
        return true;
}

//����� ������� �� ������ ������� � ����� �� ����� ������ strings
//������������ ����� ������ �� ������ � ������� �������� ����������
int StringContainer::searchStringList(TStringList *searchStrings){
	for (int contentCh=currentPointer; contentCh<contentStr.Length(); contentCh++){
        	for(int stringsCh=0; stringsCh<searchStrings->Count; stringsCh++){
			if (isSearchString(searchStrings->Strings[stringsCh], contentCh)){
				currentPointer = contentCh;
                		return stringsCh;
                	}
	        }
        }
        return NOT_SEARCH;
}


//��������� ������� ������������������ �������� ������� ������ �� ������� �������
bool StringContainer::isSearchString(AnsiString searchStr, int position){
	for (int ch=1; ch<searchStr.Length()+1; ch++){
        	if (searchStr[ch] != contentStr[position+ch-1]) return false;
        }
        return true;
}


int StringContainer::findString(AnsiString serchStr){
	for (int ch=currentPointer; ch<contentStr.Length(); ch++){
        	if (isSearchString(serchStr, ch)) return ch;
        }

        return NOT_SEARCH;
}


//////////////////////////////������ ���������///////////////////////////////////

bool StringContainer::isPattern(AnsiString pattern, int position){
	//��������� �� ������� � ������� ������
        if ((pattern.Length()+position-1)>contentStr.Length()) return false;

        for (int ch=1; ch<pattern.Length()+1; ch++){
                //���� ������� ������� �������� - ������
                if (charClassificator->classificateCurrentChar(pattern[ch]) == SYMBOLS){
                	//���������� ��� � �������������� ��������� ������ �� ������
                        //���� �������� �� ��������� ��� �� �������
                        if (contentStr[position+ch-1] != pattern[ch]) return false;
                } else {
                //�� ������, ������ ���������� �� ������� ��������
                        //���� ������ �������� �� ���������, ��� �� �������
                        if ( (charClassificator->classificateCurrentChar(contentStr[position+ch-1])) !=
                             (charClassificator->classificateCurrentChar(pattern[ch])) )  return false;
                }
        }
        return true;
}

bool StringContainer::searchPattern(AnsiString pattern){
	int findPtr = findPattern(pattern);
        if (findPtr == NOT_SEARCH) return false;
        currentPointer = findPtr;
        return true;
}


int StringContainer::findPattern(AnsiString pattern){
	for (int ch=currentPointer; ch<contentStr.Length(); ch++){
        	if (isPattern(pattern, ch)) return ch;
        }

        return NOT_SEARCH;
}


//���� � ������ ������ ������� � ����� �� ��������� patterns
int StringContainer::searchPatternList(TStringList *patterns){
	for (int contentCh=currentPointer; contentCh<contentStr.Length(); contentCh++){
		for (int patternsCh=0; patternsCh<patterns->Count; patternsCh++){
        		if (isPattern(patterns->Strings[patternsCh], contentCh)){
                                currentPointer = contentCh;
				return patternsCh;
                        }
        	}
        }
	return NOT_SEARCH;
}
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
//������ � �������� ���������

int StringContainer::getCurrentPosition(){
        return currentPointer-1; //��� ��� ���� � AnsiString � 1! 
}

void StringContainer::movePointerFrontTo(int length){
        currentPointer+=length;
	//�������� ������ �� �������, ���� ������ ������ ��� ������ ������, ������� � �� ������� ������
        if (currentPointer>contentStr.Length()) goToEndPosition();
}


void StringContainer::memoryPosition(){
	positionMemory = currentPointer;
}


void StringContainer::restorePosition(){
	assert(positionMemory != NOT_DIFINITION);
	currentPointer = positionMemory;
}


//������������� ��������� � �����
void StringContainer::goToEndPosition(){
        currentPointer = contentStr.Length()-1;
}


void StringContainer::goToStartPosition(){
	currentPointer = 1;
}

/*
//��������� �� �������?
bool StringContainer::isEndPosition(){
        if (positionPointer == contentLength-1) return true;
        return false;
}
*/

///////////////////////////////////////////










/*
char *StringContainer::findEnglish(){
}

char *StringContainer::findDigit(){
}

{
}
*/














