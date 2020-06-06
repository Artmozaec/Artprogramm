#include "FilmContainerUtilites.h"
#include "FilmIterator.h"

Film *searchFilmName(FilmContainer *container,  AnsiString fileName){
        if ((container == NULL) && (fileName == NULL)) return NULL;
	FilmIterator *iterator = container->getIterator();
        Film *film;

        while(iterator->nextFilm()){
		film = iterator->getFilm();
                if (film->getBaseFilmName() == fileName) return film;
        }

        return NULL;
}

Film *getFilmToImageFile(AnsiString imageFileName, FilmContainer *container){
        //Создать итератор
	FilmIterator *iterator = container->getIterator();
        TStringList *filmImages;

        while(iterator->nextFilm()){
                filmImages = iterator->getFilm()->getImageNames();
                if (filmImages->IndexOf(imageFileName) != -1){
                        return iterator->getFilm();
                }
        }

        return NULL;
}


int getFilmsInDay(WeekDay weekDay, FilmContainer *container){
	FilmIterator *iterator = container->getIteratorOfWeekDay(weekDay);
	int sum=0;
	while(iterator->nextFilm()){
		sum++;
	}
	return sum;
}

int getImagesInDay(WeekDay weekDay, FilmContainer *container){
FilmIterator *iterator = container->getIteratorOfWeekDay(weekDay);
	int sum=0;
	Film *film;
	while(iterator->nextFilm()){
		film = iterator->getFilm();
		if(film->imageExist()) sum++;
	}
	return sum;
}

bool existFilm(Film *film, FilmContainer *container){
        FilmIterator *iterator = container->getIterator();
	while(iterator->nextFilm()){
        	if (iterator->getFilm() == film) return true;
        }
        return false;
}
