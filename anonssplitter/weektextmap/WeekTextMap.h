#ifndef WeekTextMapH
#define WeekTextMapH
#include "WeekDay.h"
#include "TextSelection.cpp"

class TChannelText;
class WeekTextMap{
public:
	WeekTextMap();

	WeekDay weekDayInPosition(int position);

	void createMap(AnsiString *inString);

	bool isOk();

	//В случае ошибки парсинга возвращает координаты выделения места ошибки в тексте
	TextSelection getErrorSelectionInText();
private:
	//Текущая длинна карты
	int mapLength;
	int dayIndexes[8];
	int dayBegin[8];

        void addDayToMap(WeekDay day, int begin);

	//Даёт индекс дня, если находит, если нет возвращает -1
        int getIndexDay(int day);

	//Выделение ошибочного фрагмента анализируемого текста
        TextSelection errSelection;

        bool parseError;
};
#endif