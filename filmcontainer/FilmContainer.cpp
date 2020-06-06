#include "FilmContainer.h"

FilmContainer::FilmContainer(){
	//“екуща€ длинна
	currentLength = 0;
}

bool FilmContainer::nextFilm(int pos){
	if ((pos+1)>currentLength) return false;
	return true;
}

bool FilmContainer::expandLength(){
	currentLength++;
	if (currentLength>=MAX_LENGTH){
		currentLength--;
		return false;
	}

	return true;
}



void FilmContainer::deleteFilm(Film *film){
        int ch;
        for(ch=1; ch<currentLength; ch++){
            if (films[ch] == film) break;
        }

        //если фильм в контейнере не найден
	if (ch == currentLength) return;

        currentLength--;

        for(;ch<=currentLength;ch++){
               films[ch] = films[ch+1];
        }
}

void FilmContainer::addFilm(Film *film){
	if (!expandLength()){
		ShowMessage(" онтейнер кончилс€! ‘ильм не добавлен!");
                return;
        }
	films[currentLength] = film;
}

Film* FilmContainer::getFilm(int pos){
	return films[pos];
}


FilmIterator* FilmContainer::getIterator(){
        return new FilmIterator(this);
}

FilmContainer* FilmContainer::createFilmContainerOfChannel(AnsiString channelName){
	//—оздать итератор
	FilmIterator *iterator = getIterator();

	//создать FilmContainer
	FilmContainer *filmContainer = new FilmContainer();

	while (iterator->nextFilm()){
		//≈сли канал родительского фильма соответствует каналу в параметре

		if (((Film *)iterator->getFilm())->getChannel() == channelName){

			//ƒобавл€ем этот фильм в возвращаемый контейнер
			filmContainer->addFilm(iterator->getFilm());
		}
	}

	return filmContainer;
}

FilmIterator* FilmContainer::getIteratorOfChannel(AnsiString channelName){
        FilmContainer *container = createFilmContainerOfChannel(channelName);
	return container->getIterator();
}








FilmContainer* FilmContainer::createFilmContainerOfWeekDay(WeekDay weekDay){
	//—оздать итератор
	FilmIterator *iterator = getIterator();

	//создать FilmContainer
	FilmContainer *filmContainer = new FilmContainer();

	while (iterator->nextFilm()){
		//≈сли день недели родительского фильма соответствует weekDay
		if (iterator->getFilm()->getWeekDay().equals(weekDay)){
			//ƒобавл€ем этот фильм в возвращаемый контейнер
			filmContainer->addFilm(iterator->getFilm());
		}


	}

	return filmContainer;

}


int FilmContainer::size(){
        return currentLength;
}

FilmIterator* FilmContainer::getIteratorOfWeekDay(WeekDay weekDay){
        FilmContainer *container = createFilmContainerOfWeekDay(weekDay);
	return container->getIterator();
}

void FilmContainer::addFilmContainer(FilmContainer *inFilmContainer){
        FilmIterator *iterator = inFilmContainer->getIterator();
        while(iterator->nextFilm()){
                addFilm(iterator->getFilm());
        }
}




void FilmContainer::clear(){
	currentLength = 0;
}
