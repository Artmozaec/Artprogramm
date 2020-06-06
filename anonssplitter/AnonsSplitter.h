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

	//����� �������� ������ channelText,
	void splitChannel(AnsiString *channelText, AnsiString channelName);

	//� ������ ������ �������� ���������� ���������� ��������� ����� ������ � ������
	TextSelection getErrorSelectionInText();

	//�� �� � �������? �������� ���������� �������, ����� �
	bool isOk();


private:
        AnsiString *channelText;
        AnsiString channelName;

        FilmContainer *filmContainer;
	WeekTextMap *weekTextMap;
	FilmsMap *filmsMap;
	TextSelection errSelection;
	bool parseError;

        //��������� ��� ������ ������ � ���������
        void loadFilmsToContainer();

        Film *createFilm();
};
#endif