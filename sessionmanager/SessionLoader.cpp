#include "SessionLoader.h"
#include "WeekDay.h"
#include "FilmType.cpp"
#include "ShowTime.h"

SessionLoader::SessionLoader(AnsiString inPatch){
	//������������� (��������� ������ �������)
	TiXmlBase::SetCondenseWhiteSpace(false);

	patch = inPatch+XML_SESSION_FILE_NAME;
	currentFilmElement = NULL;

	//�������� ������� �������� ���� ������
	currentFilmElement = sessionOpen(patch);
	if (currentFilmElement == NULL){
		//�������� ���� ��������, �������� ������� �����
		patch = inPatch+XML_SESSION_BKP_FILE_NAME;
		currentFilmElement = sessionOpen(patch);
	}

	if (currentFilmElement == NULL){
		//����������� ��������, �������� ���� ��������, ����� ���������!
		ShowMessage("�� ������� ��������� ��������� ������...");
	}
}

TiXmlElement *SessionLoader::sessionOpen(AnsiString patch){
	TiXmlDocument *returnDoc = new TiXmlDocument(patch.c_str());

	if(!returnDoc->LoadFile()){
		ShowMessage("�������� ��� �������� ������ - "+patch);
		ShowMessage(returnDoc->ErrorDesc());
		return NULL;
	}

    return returnDoc->FirstChildElement(XML_SESSION)->FirstChildElement(XML_FILM);
}


//������� ������ �������� ������
TStringList *SessionLoader::createNamesList(TiXmlElement *namesElement){
        TStringList *names = new TStringList();
        if (namesElement == NULL){
        	ShowMessage("������ �������������� ������! ������������ ��� ���");
                return names;
        }
	TiXmlElement *nameElement = namesElement->FirstChildElement(XML_NAME);

        while(nameElement!=NULL){
        	//ShowMessage(nameElement->GetText());
	        names->Add(*new AnsiString(nameElement->GetText()));
		nameElement = nameElement->NextSiblingElement(XML_NAME);
        }
        return names;
}

//������� ������ ����������
TStringList *SessionLoader::createDirectorsList(TiXmlElement *directorsElement){
        TStringList *directors = new TStringList();
        if (directorsElement == NULL){
        	ShowMessage("������ �������������� ������! ������������ ��� ����������");
                return directors;
        }

	TiXmlElement *directorElement = directorsElement->FirstChildElement(XML_DIRECTOR);

        while(directorElement!=NULL){
                //ShowMessage(directorElement->GetText());
	        directors->Add(*new AnsiString(directorElement->GetText()));
		directorElement = directorElement->NextSiblingElement(XML_DIRECTOR);
        }
        return directors;
}

//������� ������ ��������� � ������� �����������
TStringList *SessionLoader::createImageList(TiXmlElement *imagesElement){
        TStringList *images = new TStringList();
        if (imagesElement == NULL){
        	ShowMessage("������ �������������� ������! ������������ ��� �����������");
                return images;
        }

	TiXmlElement *imageElement = imagesElement->FirstChildElement();

        while(imageElement!=NULL){
	        images->Add(*new AnsiString(imageElement->GetText()));
		imageElement = imageElement->NextSiblingElement(XML_IMAGE);
        }
        return images;
}

//������� ������ ���������
TextSelection SessionLoader::createTextSelection(TiXmlElement *selectionElement){
        int begin = 0;
        int length = 0;
        TextSelection textSelection;
        textSelection.begin = begin;
	textSelection.length = length;

        if (selectionElement == NULL){
        	ShowMessage("������ �������������� ������! ������������ ��� ��������� ������");
                return textSelection;
        }

	TiXmlElement *selectionBeginElement = selectionElement->FirstChildElement(XML_SELECTION_BEGIN);
        try{
	        begin = StrToInt(selectionBeginElement->GetText());
        }catch(...){
        	ShowMessage("��� �������������� ������ ������ ��������� ������!");
                begin = 0;
        }


        TiXmlElement *selectionLengthElement = selectionElement->FirstChildElement(XML_SELECTION_LENGTH);
        try{
        	length = StrToInt(selectionLengthElement->GetText());
        }catch(...){
        	ShowMessage("��� �������������� ������ ������ ��������� ������!");
                length = 0;
        }


        textSelection.begin = begin;
	textSelection.length = length;

        return textSelection;
}

Film *SessionLoader::getFilm(){
	if (currentFilmElement == NULL) return NULL;


        //��������� �����
        TiXmlElement *channelElement = currentFilmElement->FirstChildElement(XML_CHANNEL);
        AnsiString channel;
	if (channelElement != NULL){
        	channel = channelElement->GetText();
	} else {
        	ShowMessage("������ �������������� ������! � ������ ����������� �����");
        }


        //��������� ���� ������
	AnsiString weekDay;
        TiXmlElement *weekDayElement = currentFilmElement->FirstChildElement(XML_WEEK_DAY);
        if (weekDayElement != NULL){
        	weekDay = weekDayElement->GetText();
        } else {
			ShowMessage("������ �������������� ������! � ������ ����������� ���� ������");
        }


        //��������� ���
        AnsiString year;
        TiXmlElement *yearElement = currentFilmElement->FirstChildElement(XML_YEAR);
        if (yearElement != NULL){
        	year = yearElement->GetText();
        } else {
			ShowMessage("������ �������������� ������! ����������� ��� ����");
        }

        //��������� ����� ������
        AnsiString showTime = *new AnsiString("12:00");
	TiXmlElement *showTimeElement = currentFilmElement->FirstChildElement(XML_SHOW_TIME);
        if (showTimeElement != NULL){
        	showTime = showTimeElement->GetText();
        } else {
			ShowMessage("������ �������������� ������! ����������� ��� ������� ������");
        }

        //��������� ��� ������
        FilmType filmType = FEATURE;
	TiXmlElement *filmTypeElement = currentFilmElement->FirstChildElement(XML_FILM_TYPE);
        if (showTimeElement != NULL){
        	filmType = (FilmType)StrToInt(filmTypeElement->GetText());
        } else {
			ShowMessage("������ �������������� ������! ����������� ��� ���� ������");
        }

        TStringList *names = createNamesList(currentFilmElement->FirstChildElement(XML_NAMES));

        TStringList *directors = createDirectorsList(currentFilmElement->FirstChildElement(XML_DIRECTORS));

        TStringList *images = createImageList(currentFilmElement->FirstChildElement(XML_IMAGES));

        TextSelection textSelection = createTextSelection(currentFilmElement->FirstChildElement(XML_SELECTION));

        Film *film = new Film(
                new WeekDay(weekDay)->getDayInt(),
                channel
        );

        film->setDirectors(directors);
        film->setFilmNames(names);
        film->setImageNames(images);
        film->setSelection(textSelection);
        film->setYear(year);
        film->setShowTime( *new ShowTime(showTime));
        film->setFilmType(filmType);

        //���� ��������� ������� ����-�� ������
        currentFilmElement = currentFilmElement->NextSiblingElement(XML_FILM);

        return film;
}

