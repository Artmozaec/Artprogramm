#ifndef SettingsManagerH
#define SettingsManagerH


#include <vcl.h>

class SettingsManager{
public:
	SettingsManager(AnsiString inSettingsPatch);
	
	////////////////Путь к рабочей директории
	AnsiString getWorkFolderPatch();
	void setWorkFolderPatch(AnsiString newWorkFolderPatch);
	
	////////////////Путь к базе изображений
	AnsiString getBaseImageFolderPatch();
	void setBaseImageFolderPatch(AnsiString newBaseImageFolderPatch);
	
	////////////////Путь к директории вёрстки
	AnsiString getShareFolderPatch();
	void setShareFolderPatch(AnsiString newShareFolderPatch);
	
	////////////////Путь к директории анонсов
	AnsiString getAnonsTextFolderPatch();
	void setAnonsTextFolderPatch(AnsiString newAnonsTextFolderPatch);
	
	///////////////Путь к базе сессий
	AnsiString getSessionFolderPatch();
	void setSessionFolderPatch(AnsiString newSessionFolderPatch);
	
	//Сохранить настройки
	void saveSettings();
	
	//всё-ли в порядке?
	bool isOk();
	
	
private:
	//Ключ ошибки
	bool errorKey;
	
	AnsiString settingsPatch;
	
	//Путь к рабочей директории
	AnsiString workFolderPatch;
	
	//Путь к базе изображений
	AnsiString baseImageFolderPatch;
	
	//Путь к директории анонсов
	AnsiString anonsTextFolderPatch;
	
	//Путь к базе сессий
	AnsiString sessionFolderPatch;
	
	//Путь к выходным директориям вёрстки
	AnsiString shareFolderPatch;
	
	
	//Загрузить настройки
	void loadSettings();
};


#endif