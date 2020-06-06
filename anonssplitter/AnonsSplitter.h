#ifndef AnonsSplitterH
#define AnonsSplitterH
#include "TextSelection.cpp"
#include "WeekTextMap.h"
#include "FilmsMap.h"
#include "FilmContainer.h"
#include "Film.h"

class AnonsSplitter{
public:
	AnonsSplitter(FilmContainer *inFilmContainer);

	//Старт парсинга текста channelText,
	void splitChannel(AnsiString *channelText, AnsiString channelName);

	//В случае ошибки парсинга возвращает координаты выделения места ошибки в тексте
	TextSelection getErrorSelectionInText();

	//Всё ли в порядке? Проверка сострояния парсера, после р
	bool isOk();


private:
        AnsiString *channelText;
        AnsiString channelName;

        FilmContainer *filmContainer;
	WeekTextMap *weekTextMap;
	FilmsMap *filmsMap;
	TextSelection errSelection;
	bool parseError;

        //Добавляет все фильмы канала в контейнер
        void loadFilmsToContainer();

        Film *createFilm();
};
#endif