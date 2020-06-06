//Работа со строкой
//Классификация символов, запоминанме позиции, извлечение подстроки


#ifndef StringContainerH
#define StringContainerH
#include "CharClasses.cpp"
#include <vcl.h>
#include "CharClassificator.h"

class StringContainer{

public:
	StringContainer(AnsiString *);

        //Возвращает подстроку от позиции в памяти до текущей
        AnsiString getSubstringInMemoryPositionToCurrent();

        //Возвращает подстроку от текущей позиции length символов
	AnsiString getSubstringInCurrentPosition(int length);

	//---------------------------------------------------------------//
	//Поиск в контенте различных полностью определённых типов данных год, время или строка

	//Обозначает неудачный поиск возвращаемый следующими функциями
	static const int NOT_SEARCH = -1;

        ///Установка нужной позиции
	//Поиск ведётся до первой встречи с русским символом, найденная позиция является текущей
	bool searchRussian();

        //Посик до первой русской буквы или цифры
        bool searchRussianOrDigit();

        //Поиск до первого символа
	bool searchSymbols();
        //Возможно они пронадобятся в будущем
        //bool searchEnglish();
        //bool searchDigit();
        ///////////////////////////////////////////////////////////////////

        //Поиск в строке паттерна
        //в паттерне символы имеют точное соответствие, числа и буквы определяются как множества чисел и букв (русские английские)
        bool searchPattern(AnsiString pattern);

        int searchPatternList(TStringList *patterns);

	//Поиск ведётся до первой встречи searchStr, возвращается позиция указателя
	bool searchString(AnsiString serchStr);

	//Поиск ведется до первой встречи с одной из строк списка strings
	int searchStringList(TStringList *searchStrings);


        ////////////////////////////////////////////////////////////////////
        //Работа с позицией указателя
        int getCurrentPosition();

        //Смещает указатель вперёд на length символов
        void movePointerFrontTo(int length);
	void memoryPosition();
	void restorePosition();
        //Позиционирует указатель в конце
        void goToEndPosition();

        void goToStartPosition();

        //Последняя ли позиция?
        bool isEndPosition();

        /////////////////////////////////////////////////////////////////////


private:

	CharClassificator *charClassificator;

        AnsiString contentStr;

	//Указатель на текущий символ в строке
        int currentPointer;

	//Память указателья, memoryPosition() - restorePosition()
        int positionMemory;

        //начальное состояние
        const int NOT_DIFINITION;


        /////////////////////////////////////
        //Проверяет наличие последовательности символов искомой строки от текущей позиции
        //Возвращается номер строки по списку с которой возникло совпадение

        //Проверяет наличие последовательности паттерна, от позиции position
        bool isPattern(AnsiString patten, int position);

        bool isSearchString(AnsiString searchStr, int position);

        ///////////////////////////////////////

        int findRussian();

        //Поиск до первого символа
        int findSymbols();

        //Посик до первой русской буквы или цифры
        int findRussianOrDigit();

        int findPattern(AnsiString pattern);

        int findString(AnsiString serchStr);
};

//char *findEnglish();

//char *findDigit();
#endif