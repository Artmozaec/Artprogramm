#ifndef SessionManagerH
#define SessionManagerH
#include "FilmContainer.h"
#include <vcl.h>

class SessionManager{
public:
	SessionManager();
	
	//��������� ��������� ������
	void loadLastSession(FilmContainer *container);

	//��������� ������
	void loadSession(AnsiString sessionName, FilmContainer *container);

	//������� ����� ������
	void createNewSession();
	
	//���� ������ ������
	TStringList *getSessionList();
		
	//��������� ������� ������
	void saveCurrentSession(FilmContainer *container);

        ///////����� ������� ������///////////////

        //���������� ������ �� ����� ����������� �� �����
        //���� ����� ���, ���������� NULL
        TStringList *getChannelText(AnsiString fileName);

        //���������� ����� ������ fileName, ���������� ������
        TStringList *getChannelTextPervisionSession(AnsiString fileName);

        void saveChannelText(AnsiString fileName, AnsiString *channelText);
	
	void setSessionStoryPatch(AnsiString inSessionStoryPatch);
	
private:

	
	//���� � ��������� ������
	AnsiString sessionStoryPatch;

	//���� � ������� ����������
	AnsiString currentSessionDirectory;

	AnsiString generateSessionName();
};

#endif