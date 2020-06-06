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

	//������ ���� ���
	parseError = false;

	//���������� ������� ���������� ���������
	errSelection.begin = 0;
	errSelection.length = 0;
}

void AnonsSplitter::splitChannel(AnsiString *inChannelText, AnsiString inChannelName){
        channelText = inChannelText;
        channelName = inChannelName;

	//��������� ����� �������
	weekTextMap->createMap(channelText);
	//��������� ��������� ������
	if (!weekTextMap->isOk()){
		parseError = true;
		errSelection = weekTextMap->getErrorSelectionInText();
		return;
	}

	//��������� ����� �������
	filmsMap->createMap(channelText);
	//��������� ��������� ������
	if (!filmsMap->isOk()){
		parseError = true;
		errSelection = filmsMap->getErrorSelectionInText();
		return;
	}

        //��������� ��������� ��������
        loadFilmsToContainer();

}

Film *AnonsSplitter::createFilm(){
	AnsiString filmText = filmsMap->getFilmText(channelText);
	//������� �� ��������, �������������
        if (filmText == NULL) return NULL;

        //�������� ������������ ��������� ������ ������
        int beginInChannelText = channelText->Pos(filmText);
        WeekDay weekDay = weekTextMap->weekDayInPosition(beginInChannelText);

        ShowTime *showTime = &filmsMap->getTimeInPosition(beginInChannelText+1);

        //ShowMessage(filmText);
        //ShowMessage(weekDay.getDayString());

        StringContainer *filmTextContainer = new StringContainer(new AnsiString(filmText.LowerCase()));

        //��� ������

        FilmNameCategory *filmNameCategory = new FilmNameCategory();
        filmNameCategory->search(filmTextContainer);

        TextSelection textSelection;
        textSelection.begin = filmTextContainer->getCurrentPosition()+beginInChannelText-1;
        textSelection.length = filmNameCategory->getCategoryString().Length();

        TStringList *filmNames = new TStringList();


        filmNames->Add(filmNameCategory->getCategoryString());

        //���

	YearCategory *yearCategory = new YearCategory();
        yearCategory->search(filmTextContainer);
        AnsiString year = yearCategory->getCategoryString();


        //�������
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
                //���������, ���-�� ����� � �����-�� ���������?
                if (searchFilmName(filmContainer, film->getBaseFilmName()) != NULL){
                	//���� ������� �� NULL ������ ����� � ����� ��������� ����
                        int result;
                        result = MessageDlg("����� � ��������� -" + film->getBaseFilmName()+  "  ��� ����, �� ����� ��������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel,  0);
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
