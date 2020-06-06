#ifndef FilmContainerH
#define FilmContainerH
#include <vcl.h>
#include "Film.h"
#include "FilmIterator.h"

class FilmIterator;
class FilmContainer{
public:
	FilmContainer();
	
	void addFilm(Film *film);

        //��������� ��� �������� �� inFilmContainer � ����
        void addFilmContainer(FilmContainer *inFilmContainer);

	void deleteFilm(Film *film);

        //������
        int size();

	bool nextFilm(int);
	Film *getFilm(int);
	
        //bool existFilm(Film *film);
	///////////���������
	//�������
	FilmIterator *getIterator();

	//������� �� ������
	FilmIterator *getIteratorOfChannel(AnsiString channelName);

	//������� �� ��� ������
	FilmIterator *getIteratorOfWeekDay(WeekDay weekDay);

        //������� ���������
        void clear();
private:
	static const int MAX_LENGTH = 300;
	Film *films[MAX_LENGTH];
	//������� ������ ����������,
	int currentLength;

	//���������� ������� - �������
	bool expandLength();

	//������ ��������� � ��������� ��� �������� � ������� ����� - channelName
	FilmContainer* createFilmContainerOfChannel(AnsiString channelName);

	//������ ��������� � ��������� ��� �������� � ������� ���� ������ - weekDay
	FilmContainer* createFilmContainerOfWeekDay(WeekDay weekDay);
};
#endif