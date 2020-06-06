#ifndef SessionLoaderH
#define SessionLoaderH
#include "Film.h"
#include "tinyxml.h"
#include <vcl.h>
#include "XMLElements.cpp"
#include "TextSelection.cpp"
#include "ShowTime.h"
#include "FilmType.cpp"

class TiXlElement;
class SessionLoader{
public:
	SessionLoader(AnsiString inPatch);
	Film *getFilm();

private:
	AnsiString patch;
	TiXmlElement *currentFilmElement;

	//Создать список названий фильма
	TStringList *createNamesList(TiXmlElement *namesElement);

	//Создать список режиссеров
	TStringList *createDirectorsList(TiXmlElement *directorsElement);

	//Создать список связанных с фильмом изображений
	TStringList *createImageList(TiXmlElement *imagesElement);

	//Создать объект выделения
	TextSelection createTextSelection(TiXmlElement *selectionElement);

	//Создаёт и проверяет и возвращает xml документ
	TiXmlElement *sessionOpen(AnsiString patch);

};

#endif