#ifndef FilmIteratorH
#define FilmIteratorH
#include <vcl.h>
#include "Film.h"
#include "FilmContainer.h"

class FilmContainer;
class FilmIterator{
public:
	FilmIterator(FilmContainer *inFilmContainer);
	bool nextFilm();

        //Это не конец случайно?
        //bool isEnd();

	Film *getFilm();
	void reset();
private:
	int cursor;
	
	FilmContainer *filmContainer;
};

#endif