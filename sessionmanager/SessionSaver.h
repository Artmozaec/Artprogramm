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
	//��������� �������
        //����� ������
        TiXmlElement *createFilmNames(Film *film);

        //���������
        TiXmlElement *createFilmDirectors(Film *film);

        //����� ����������� � ������
        TiXmlElement *createImages(Film *film);

        //������� ��������� ������
        TiXmlElement *createTextSelection(Film *film);

	AnsiString patch;
        AnsiString patch_bkp;
	TiXmlDocument doc;
        TiXmlElement *sessionElement;

};
#endif