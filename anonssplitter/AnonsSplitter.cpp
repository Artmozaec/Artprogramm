#include "AnonsSplitter.h"
#include "WeekDay.h"
#include "StringContainer.h"
#include "FilmNameCategory.h"
#include "YearCategory.h"
#include "DirectorCategory.h"
#include "TextSelection.cpp"
#include "FilmContainerUtilites.h"
#include "ShowTime.h"

AnonsSplitter::AnonsSplitter(FilmContainer *inFilmContainer){
        filmContainer = inFilmContainer;

	weekTextMap = new WeekTextMap();
	filmsMap = new FilmsMap();

	//Ошибки пока нет
	parseError = false;

	//Начальноая позиция ошибочного выделения
	errSelection.begin = 0;
	errSelection.length = 0;
}

void AnonsSplitter::splitChannel(AnsiString *inChannelText, AnsiString inChannelName){
        channelText = inChannelText;
        channelName = inChannelName;

	//Заполняем карту каналов
	weekTextMap->createMap(channelText);
	//Проверяем состояние ошибки
	if (!weekTextMap->isOk()){
		parseError = true;
		errSelection = weekTextMap->getErrorSelectionInText();
		return;
	}

	//Заполняем карту фильмов
	filmsMap->createMap(channelText);
	//Проверяем состояние ошибки
	if (!filmsMap->isOk()){
		parseError = true;
		errSelection = filmsMap->getErrorSelectionInText();
		return;
	}

        //Заполняем контейнер фильмами
        loadFilmsToContainer();

}

Film *AnonsSplitter::createFilm(){
	AnsiString filmText = filmsMap->getFilmText(channelText);
	//Фильмов не осталось, сигнализируем
        if (filmText == NULL) return NULL;

        //смещение относительно основного текста фильма
        int beginInChannelText = channelText->Pos(filmText);
        WeekDay weekDay = weekTextMap->weekDayInPosition(beginInChannelText);

        ShowTime *showTime = &filmsMap->getTimeInPosition(beginInChannelText+1);

        //ShowMessage(filmText);
        //ShowMessage(weekDay.getDayString());

        StringContainer *filmTextContainer = new StringContainer(new AnsiString(filmText.LowerCase()));

        //Имя фильма

        FilmNameCategory *filmNameCategory = new FilmNameCategory();
        filmNameCategory->search(filmTextContainer);

        TextSelection textSelection;
        textSelection.begin = filmTextContainer->getCurrentPosition()+beginInChannelText-1;
        textSelection.length = filmNameCategory->getCategoryString().Length();

        TStringList *filmNames = new TStringList();


        filmNames->Add(filmNameCategory->getCategoryString());

        //Год

	YearCategory *yearCategory = new YearCategory();
        yearCategory->search(filmTextContainer);
        AnsiString year = yearCategory->getCategoryString();


        //Режиссёр
        filmTextContainer->goToStartPosition();
        DirectorCategory *directorCategory = new DirectorCategory();
        directorCategory->search(filmTextContainer);

        TStringList *directors = directorCategory->getCategoryList();

        //ShowMessage(filmNames->Strings[0]);
        //ShowMessage(director);
        //ShowMessage(year);
        Film *film = new Film(weekDay.getDayInt(), channelName);

        film->setWeekDay(weekDay.getDayInt());
        film->setFilmNames(filmNames);
        film->setDirectors(directors);
        film->setYear(year);
        film->setSelection(textSelection);
        film->setShowTime(*showTime);
        return film;
}

void AnonsSplitter::loadFilmsToContainer(){
	Film *film;
	while(true){
		film = createFilm();
                if (film == NULL) return;
                //Проверяем, нет-ли фиьма с таким-же названием?
                if (searchFilmName(filmContainer, film->getBaseFilmName()) != NULL){
                	//Если вернуло не NULL значит фильм с таким названием есть
                        int result;
                        result = MessageDlg("Фильм с названием -" + film->getBaseFilmName()+  "  уже есть, всё равно добавить?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel,  0);
			if (result == mrNo) continue;
			if (result == mrCancel) return;
                }


                filmContainer->addFilm(film);
        }
}

bool AnonsSplitter::isOk(){
	return !parseError;
}


TextSelection AnonsSplitter::getErrorSelectionInText(){
	return errSelection;
}
