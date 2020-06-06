#include "SessionManager.h"
#include "SessionSaver.h"
#include "SessionLoader.h"
#include "FilmIterator.h"
#include "FileOperations.cpp"
#include "DateUtils.hpp"
#include "FileReaderWriter.h"

SessionManager::SessionManager(){
	sessionStoryPatch = *new AnsiString();
	currentSessionDirectory = NULL;
}

//��������� ������� ������
void SessionManager::saveCurrentSession(FilmContainer *container){
	SessionSaver *saver = new SessionSaver(sessionStoryPatch+currentSessionDirectory);
        FilmIterator *iterator = container->getIterator();

        while (iterator->nextFilm()){
		saver->addFilm(iterator->getFilm());
        }

        saver->saveFile();
}

//��������� ������
void SessionManager::loadSession(AnsiString sessionName, FilmContainer *container){
	//���������� ������� �������
	currentSessionDirectory = sessionName+"//";	
	SessionLoader *loader = new SessionLoader(sessionStoryPatch+currentSessionDirectory);
	
	while(true){
		Film *film = loader->getFilm();
                if (film != NULL){
					container->addFilm(film);
                } else {
                	break;
                }
        }
}


void SessionManager::loadLastSession(FilmContainer *container){
        TStringList *folderContent = new TStringList();
        getDirectoryContent(sessionStoryPatch, folderContent);

        //���� ����� �����, ������ ����� ������
        if (folderContent->Count == 0){
		createNewSession();
                return;
        }
	loadSession(folderContent->Strings[folderContent->Count-1], container);
}

//������� ����� ������
void SessionManager::createNewSession(){
	//�������� ��� ����� ������
	AnsiString sessionName = generateSessionName();

	//������ ������������� � ����� ������

	CreateDir(sessionStoryPatch+sessionName);

	//������� ������ - ���
	currentSessionDirectory = sessionName+"//";
}


AnsiString SessionManager::generateSessionName(){
	TDateTime currentDate = Date();
        AnsiString format = *new AnsiString("yy_mm_dd");
        AnsiString result = currentDate.FormatString(format);

        TStringList *folderContent = new TStringList();
        getDirectoryContent(sessionStoryPatch, folderContent);
        if (folderContent->IndexOf(result) != -1){
        	int prefix = 0;
        	do{
                	prefix++;
                } while (folderContent->IndexOf(result + "("+IntToStr(prefix)+")") != -1);
                result +="("+IntToStr(prefix)+")";
        }
        return result;
}


        ///////����� ������� ������///////////////

TStringList *SessionManager::getChannelText(AnsiString fileName){
	TStringList *textList;
	FileReaderWriter *reader = new FileReaderWriter();

        textList = reader->readWinText(sessionStoryPatch+currentSessionDirectory+fileName);

        return textList;
}

//���������� ����� ������ fileName, ���������� ������
TStringList *SessionManager::getChannelTextPervisionSession(AnsiString fileName){
     	TStringList *textList;
        TStringList *sessionList = getSessionList();

        //���� ������ ����, ����� ������
        if (sessionList->Count<2) return new TStringList();

        AnsiString pervisionSessionPatch = sessionList->Strings[sessionList->Count-2]+"\\";
	FileReaderWriter *reader = new FileReaderWriter();

        textList = reader->readWinText(sessionStoryPatch+pervisionSessionPatch+fileName);

        return textList;
}

void SessionManager::saveChannelText(AnsiString fileName, AnsiString *channelText){
	FileReaderWriter *writer = new FileReaderWriter();

        writer->saveTextToFile(sessionStoryPatch+currentSessionDirectory+fileName, channelText);
}

//���� ������ ������
TStringList *SessionManager::getSessionList(){
        TStringList *folderContent = new TStringList();
        getDirectoryContent(sessionStoryPatch, folderContent);
        return folderContent;
}

void SessionManager::setSessionStoryPatch(AnsiString inSessionStoryPatch){
	sessionStoryPatch = inSessionStoryPatch;
}
	