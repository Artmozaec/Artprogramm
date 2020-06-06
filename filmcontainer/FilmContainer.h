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

        //Добавляет все элементы из inFilmContainer в сюда
        void addFilmContainer(FilmContainer *inFilmContainer);

	void deleteFilm(Film *film);

        //Размер
        int size();

	bool nextFilm(int);
	Film *getFilm(int);
	
        //bool existFilm(Film *film);
	///////////ИТЕРАТОРЫ
	//Обычный
	FilmIterator *getIterator();

	//Выборка по каналу
	FilmIterator *getIteratorOfChannel(AnsiString channelName);

	//Выборка по дню недели
	FilmIterator *getIteratorOfWeekDay(WeekDay weekDay);

        //Очищает контейнер
        void clear();
private:
	static const int MAX_LENGTH = 300;
	Film *films[MAX_LENGTH];
	//текущая длинна контейнера,
	int currentLength;

	//Расширение границы - размера
	bool expandLength();

	//Создаёт контейнер и заполняет его фильмами у которых канал - channelName
	FilmContainer* createFilmContainerOfChannel(AnsiString channelName);

	//Создаёт контейнер и заполняет его фильмами у которых день недели - weekDay
	FilmContainer* createFilmContainerOfWeekDay(WeekDay weekDay);
};
#endif