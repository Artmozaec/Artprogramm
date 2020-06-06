#ifndef SessionManagerH
#define SessionManagerH
#include "FilmContainer.h"
#include <vcl.h>

class SessionManager{
public:
	SessionManager();
	
	//Загрузить последнюю сессию
	void loadLastSession(FilmContainer *container);

	//Загрузить сессию
	void loadSession(AnsiString sessionName, FilmContainer *container);

	//Создать новую сессию
	void createNewSession();
	
	//Дать список сессий
	TStringList *getSessionList();
		
	//Сохранить текущую сессию
	void saveCurrentSession(FilmContainer *container);

        ///////ТЕКСТ КАНАЛОВ СЕССИИ///////////////

        //возвращает ссылку на текст прочитанный из файла
        //Если файла нет, возвращает NULL
        TStringList *getChannelText(AnsiString fileName);

        //Возвращает текст канала fileName, предыдущей сессии
        TStringList *getChannelTextPervisionSession(AnsiString fileName);

        void saveChannelText(AnsiString fileName, AnsiString *channelText);
	
	void setSessionStoryPatch(AnsiString inSessionStoryPatch);
	
private:

	
	//Путь к хранилищу сессий
	AnsiString sessionStoryPatch;

	//Путь к текущей директории
	AnsiString currentSessionDirectory;

	AnsiString generateSessionName();
};

#endif