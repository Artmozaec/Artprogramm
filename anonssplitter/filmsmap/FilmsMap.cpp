#include "FilmsMap.h"
#include "TimeCategory.h"

FilmsMap::FilmsMap(){
        mapPointer = 0;
        mapLength = 0;
	parseError = false;

        errSelection.begin = 0;
	errSelection.length = 0;
}

void FilmsMap::addFilmToMap(int begin, int length, ShowTime showTime){
        mapLength++;
	filmBegin[mapLength] = begin;
        filmLength[mapLength] = length;
        showTimeArray[mapLength] = new ShowTime(showTime.getHour(), showTime.getMinute());

}

void FilmsMap::createMap(AnsiString *channelText){
	mapLength = 0;
        AnsiString lowCaseText = channelText->LowerCase();
        StringContainer *container = new StringContainer(&lowCaseText);
        ShowTime *currentTime;
        TimeCategory *timeCategory = new TimeCategory();

        //Начальная инициация, ищем первый фильм
	if (!timeCategory->search(container)) return;

        //Начало первого фильма
        int filmBegin = container->getCurrentPosition();

	currentTime = &timeCategory->getTime();

        timeCategory->movePointerFront(container);

        while (timeCategory->search(container)){


		//ShowMessage(timeCategory->getTime().getString());
		//Добавляем фильм на карту
                addFilmToMap(filmBegin, container->getCurrentPosition()-filmBegin, *currentTime);

                filmBegin = container->getCurrentPosition();

                currentTime = &timeCategory->getTime();

                timeCategory->movePointerFront(container);
        }

        //Добавлям последний фильм
	addFilmToMap(filmBegin, channelText->Length()-filmBegin, timeCategory->getTime());
}



//Смещает указатель на следующий фильм
bool FilmsMap::nextFilm(){
	mapPointer++;
        if (mapPointer>mapLength) return false;
        return true;
}


AnsiString FilmsMap::getFilmText(AnsiString *channelText){
	if (!nextFilm()) return NULL;

        return channelText->SubString(filmBegin[mapPointer], filmLength[mapPointer]);
}

bool FilmsMap::isOk(){
	return !parseError;
}


TextSelection FilmsMap::getErrorSelectionInText(){
	return errSelection;
}


ShowTime FilmsMap::getTimeInPosition(int position){
        if (mapLength == 0) return *new ShowTime(0, 0);

	for (int ch=1; ch<=mapLength; ch++){
        	if (position<filmBegin[ch]){
                	if (ch == 1) return *new ShowTime(0, 0);

                        return *showTimeArray[ch-1];
                }
        }

        return *showTimeArray[mapLength];
}
