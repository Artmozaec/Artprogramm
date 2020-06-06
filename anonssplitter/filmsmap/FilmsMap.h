#ifndef FilmsMapH
#define FilmsMapH
#include <vcl.h>
#include "TextSelection.cpp"
#include "ShowTime.h"

class FilmsMap{
public:
	FilmsMap();
	void createMap(AnsiString *channelText);

	AnsiString getFilmText(AnsiString *channelText);

        ShowTime getTimeInPosition(int position);

	bool isOk();
	//В случае ошибки парсинга возвращает координаты выделения места ошибки в тексте
	TextSelection getErrorSelectionInText();
private:
        static const int MAP_SIZE = 100;
	//Указатель на текущий фильм
        int mapPointer;
	//Текущая длинна карты
	int mapLength;
	int filmBegin[MAP_SIZE];
	int filmLength[MAP_SIZE];
        ShowTime *showTimeArray[MAP_SIZE];

	//Выделение ошибочного фрагмента анализируемого текста
        TextSelection errSelection;

        bool parseError;

        //Добавляет в карту координаты нового фильма
        void addFilmToMap(int begin, int length, ShowTime showTime);

	//Смещает указатель на следующий фильм
        bool nextFilm();
};
#endif