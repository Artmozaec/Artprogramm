#include "SessionSaver.h"
#include "TextSelection.cpp"
#include <stdio.h>
#include "ShowTime.h"
#include "FilmType.cpp"

SessionSaver::SessionSaver(AnsiString inPatch){
	//���� � ��������� �����
	patch = inPatch+XML_SESSION_FILE_NAME;
        //���� � �����
        patch_bkp = inPatch+XML_SESSION_BKP_FILE_NAME;

        //������ ���������
        TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "windows-1251", "" );
	doc.LinkEndChild(decl);

        sessionElement = new TiXmlElement(XML_SESSION);
        doc.LinkEndChild(sessionElement);
}

//����� ������
TiXmlElement *SessionSaver::createFilmNames(Film *film){
        TiXmlElement *namesElement = new TiXmlElement(XML_NAMES);
        TStringList *names = film->getFilmNames();
        for(int ch=0; ch<names->Count; ch++){
                TiXmlElement *nameElement = new TiXmlElement(XML_NAME);
                nameElement->LinkEndChild(new TiXmlText(names->Strings[ch].c_str()));
                namesElement->LinkEndChild(nameElement);
        }
        return namesElement;
}

//���������
TiXmlElement *SessionSaver::createFilmDirectors(Film *film){
        TiXmlElement *directorsElement = new TiXmlElement(XML_DIRECTORS);
        TStringList *directors = film->getDirectors();
        for(int ch=0; ch<directors->Count; ch++){
                TiXmlElement *directorElement = new TiXmlElement(XML_DIRECTOR);
                directorElement->LinkEndChild(new TiXmlText(directors->Strings[ch].c_str()));
                directorsElement->LinkEndChild(directorElement);
        }
        return directorsElement;
}

//����� ����������� � ������
TiXmlElement *SessionSaver::createImages(Film *film){
        TiXmlElement *imagesElement = new TiXmlElement(XML_IMAGES);
        TStringList *imageNames = film->getImageNames();
        for(int ch=0; ch<imageNames->Count; ch++){
                TiXmlElement *imageElement = new TiXmlElement(XML_IMAGE);
                imageElement->LinkEndChild(new TiXmlText(imageNames->Strings[ch].c_str()));
                imagesElement->LinkEndChild(imageElement);
        }
        return imagesElement;
}

//������� ��������� ������
TiXmlElement *SessionSaver::createTextSelection(Film *film){
	TiXmlElement *selectionElement = new TiXmlElement(XML_SELECTION);

        TiXmlElement *selectionBeginElement = new TiXmlElement(XML_SELECTION_BEGIN);
        selectionBeginElement->LinkEndChild(new TiXmlText(IntToStr(film->getSelection().begin).c_str()));

        TiXmlElement *selectionLengthElement = new TiXmlElement(XML_SELECTION_LENGTH);
        selectionLengthElement->LinkEndChild(new TiXmlText(IntToStr(film->getSelection().length).c_str()));

        selectionElement->LinkEndChild(selectionBeginElement);
        selectionElement->LinkEndChild(selectionLengthElement);

        return selectionElement;
}


void SessionSaver::addFilm(Film *film){
	TiXmlElement *filmElement = new TiXmlElement(XML_FILM);

        //��������� ������ � ������
	TiXmlElement *channelElement = new TiXmlElement(XML_CHANNEL);
        channelElement->LinkEndChild(new TiXmlText(film->getChannel().c_str()));
        filmElement->LinkEndChild(channelElement);

        //���� ������
        TiXmlElement *weekDayElement = new TiXmlElement(XML_WEEK_DAY);
        weekDayElement->LinkEndChild(new TiXmlText(film->getWeekDay().getDayString().c_str()));
        filmElement->LinkEndChild(weekDayElement);


        //���
        TiXmlElement *yearElement = new TiXmlElement(XML_YEAR);
        yearElement->LinkEndChild(new TiXmlText(film->getYear().c_str()));
        filmElement->LinkEndChild(yearElement);

        //����� ������
        TiXmlElement *showTimeElement = new TiXmlElement(XML_SHOW_TIME);
        showTimeElement->LinkEndChild(new TiXmlText(film->getShowTime().getString().c_str()));
        filmElement->LinkEndChild(showTimeElement);

        //��� ������
	TiXmlElement *filmTypeElement = new TiXmlElement(XML_FILM_TYPE);
        AnsiString *typeStr = new AnsiString(film->getType());
        //ShowMessage(*typeStr);
	filmTypeElement->LinkEndChild(new TiXmlText(typeStr->c_str()));
        filmElement->LinkEndChild(filmTypeElement);

        //����� ������
        filmElement->LinkEndChild(createFilmNames(film));
        //��������
        filmElement->LinkEndChild(createFilmDirectors(film));
        //��������� �����������
        filmElement->LinkEndChild(createImages(film));
        //��������� ������
        filmElement->LinkEndChild(createTextSelection(film));

	sessionElement->LinkEndChild(filmElement);
}


void SessionSaver::saveFile(){
        //������� ������ �����
        DeleteFile(patch_bkp);

        //��������������� �������� ���� � �����
        rename(patch.c_str(), patch_bkp.c_str());

	//��������� ����� �������� ����
	doc.SaveFile(patch.c_str());
}

