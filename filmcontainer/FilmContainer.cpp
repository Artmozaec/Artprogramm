#include "FilmContainer.h"

FilmContainer::FilmContainer(){
	//������� ������
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

        //���� ����� � ���������� �� ������
	if (ch == currentLength) return;

        currentLength--;

        for(;ch<=currentLength;ch++){
               films[ch] = films[ch+1];
        }
}

void FilmContainer::addFilm(Film *film){
	if (!expandLength()){
		ShowMessage("��������� ��������! ����� �� ��������!");
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
	//������� ��������
	FilmIterator *iterator = getIterator();

	//������� FilmContainer
	FilmContainer *filmContainer = new FilmContainer();

	while (iterator->nextFilm()){
		//���� ����� ������������� ������ ������������� ������ � ���������

		if (((Film *)iterator->getFilm())->getChannel() == channelName){

			//��������� ���� ����� � ������������ ���������
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
	//������� ��������
	FilmIterator *iterator = getIterator();

	//������� FilmContainer
	FilmContainer *filmContainer = new FilmContainer();

	while (iterator->nextFilm()){
		//���� ���� ������ ������������� ������ ������������� weekDay
		if (iterator->getFilm()->getWeekDay().equals(weekDay)){
			//��������� ���� ����� � ������������ ���������
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
