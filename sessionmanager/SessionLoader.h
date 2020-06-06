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

	//������� ������ �������� ������
	TStringList *createNamesList(TiXmlElement *namesElement);

	//������� ������ ����������
	TStringList *createDirectorsList(TiXmlElement *directorsElement);

	//������� ������ ��������� � ������� �����������
	TStringList *createImageList(TiXmlElement *imagesElement);

	//������� ������ ���������
	TextSelection createTextSelection(TiXmlElement *selectionElement);

	//������ � ��������� � ���������� xml ��������
	TiXmlElement *sessionOpen(AnsiString patch);

};

#endif