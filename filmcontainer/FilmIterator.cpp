#include "FilmIterator.h"

FilmIterator::FilmIterator(FilmContainer *inFilmContainer){
	cursor = 0;
	filmContainer = inFilmContainer;
}

bool FilmIterator::nextFilm(){
	if (filmContainer->nextFilm(cursor)){
		cursor++;
                return true;
	}
        return false;
}

Film *FilmIterator::getFilm(){
	return filmContainer->getFilm(cursor);
}

/*
bool FilmIterator::isEnd(){
        return !(filmContainer->nextFilm(cursor));
}
*/
