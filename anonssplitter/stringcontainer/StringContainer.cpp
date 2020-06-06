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


//Возвращает подстроку от позиции в памяти до текущей
AnsiString StringContainer::getSubstringInMemoryPositionToCurrent(){
        if (positionMemory == NOT_DIFINITION) return NULL;
	return contentStr.SubString(positionMemory, currentPointer-positionMemory);
}

//Возвращает подстроку от текущей позиции length символов
AnsiString StringContainer::getSubstringInCurrentPosition(int length){
        AnsiString result;
        result = contentStr.SubString(currentPointer, length);
        return result;

}


//////////////////ПОИСКИ ТИПОВ ДПННЫХ///////////////////////////////
//Посик до первой буквы или цифры
bool StringContainer::searchRussianOrDigit(){
	//Ищем русские буквы или цифру
	int findPtr = findRussianOrDigit();
        if (findPtr == NOT_SEARCH) return false;
        currentPointer = findPtr;
        return true;
}

//Посик до первой русской буквы или цифры
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
	//Ищем русские буквы
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

/////////ПОИСК ПОДСТРОКИ В СТРОКЕ////////////////////


//Поиск ведётся до первой встречи searchStr, возвращается позиция указателя
bool StringContainer::searchString(AnsiString searchStr){
	int findPtr = findString(searchStr);
        if (findPtr == NOT_SEARCH) return false;
        currentPointer = findPtr;
        return true;
}

//Поиск ведется до первой встречи с одной из строк списка strings
//Возвращается номер строки по списку с которой возникло совпадение
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


//Проверяет наличие последовательности символов искомой строки от текущей позиции
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


//////////////////////////////ПОИСКИ ПАТТЕРНОВ///////////////////////////////////

bool StringContainer::isPattern(AnsiString pattern, int position){
	//Вмещается ли паттерн в остаток строки
        if ((pattern.Length()+position-1)>contentStr.Length()) return false;

        for (int ch=1; ch<pattern.Length()+1; ch++){
                //Если текущий элемент паттерна - символ
                if (charClassificator->classificateCurrentChar(pattern[ch]) == SYMBOLS){
                	//Сравниваем его с соответствущим элементом строки на прямую
                        //Если значения не совпадают это не паттерн
                        if (contentStr[position+ch-1] != pattern[ch]) return false;
                } else {
                //Не символ, значит сравниваем по классам символов
                        //Если классы символов не совпадают, это не паттерн
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


//Ищем в строке первой встречи с одним из елементов patterns
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
//Работа с позицией указателя

int StringContainer::getCurrentPosition(){
        return currentPointer-1; //Так как счёт в AnsiString с 1! 
}

void StringContainer::movePointerFrontTo(int length){
        currentPointer+=length;
	//Проверка выхода за границы, если размер больше чем длинна строки, урезаем её до размера строки
        if (currentPointer>contentStr.Length()) goToEndPosition();
}


void StringContainer::memoryPosition(){
	positionMemory = currentPointer;
}


void StringContainer::restorePosition(){
	assert(positionMemory != NOT_DIFINITION);
	currentPointer = positionMemory;
}


//Позиционирует указатель в конце
void StringContainer::goToEndPosition(){
        currentPointer = contentStr.Length()-1;
}


void StringContainer::goToStartPosition(){
	currentPointer = 1;
}

/*
//Последняя ли позиция?
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














