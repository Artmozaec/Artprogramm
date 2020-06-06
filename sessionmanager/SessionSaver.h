#ifndef SessionSaverH
#define SessionSaverH
#include "Film.h"
#include "tinyxml.h"
#include <vcl.h>
#include "XMLElements.cpp"

class SessionSaver{
public:
	SessionSaver(AnsiString inPatch);
	void addFilm(Film *film);
	void saveFile();
private:
	//Создатели списков
        //Имена фильма
        TiXmlElement *createFilmNames(Film *film);

        //Режиссеры
        TiXmlElement *createFilmDirectors(Film *film);

        //Файлы изображений к фильму
        TiXmlElement *createImages(Film *film);

        //Позиция Выделения текста
        TiXmlElement *createTextSelection(Film *film);

	AnsiString patch;
        AnsiString patch_bkp;
	TiXmlDocument doc;
        TiXmlElement *sessionElement;

};
#endif