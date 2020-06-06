#include "SettingsManager.h"
#include "tinyxml.h"
#include "XMLElementsSettings.cpp"


SettingsManager::SettingsManager(AnsiString inSettingsPatch){
	//Устанавливаем (оставлять повтор пробела)
	TiXmlBase::SetCondenseWhiteSpace(false);
        
	settingsPatch = *new AnsiString(inSettingsPatch+"settings.xml");
	//ошибки пока нет
	errorKey = false;
	
	//инициализация
	workFolderPatch = *new AnsiString();
	baseImageFolderPatch = *new AnsiString();
	anonsTextFolderPatch = *new AnsiString();
	sessionFolderPatch = *new AnsiString();
	shareFolderPatch = *new AnsiString();
	
	//Пытаемся читать настройки
	loadSettings();
	
}


////////////////Путь к рабочей директории
AnsiString SettingsManager::getWorkFolderPatch(){
	return workFolderPatch;
}


void SettingsManager::setWorkFolderPatch(AnsiString newWorkFolderPatch){
	workFolderPatch = newWorkFolderPatch;
}
	
////////////////Путь к базе изображений
AnsiString SettingsManager::getBaseImageFolderPatch(){
	return baseImageFolderPatch;
}

void SettingsManager::setBaseImageFolderPatch(AnsiString newBaseImageFolderPatch){
	baseImageFolderPatch = newBaseImageFolderPatch;
}
	
////////////////Путь к директории вёрстки
AnsiString SettingsManager::getShareFolderPatch(){
	return shareFolderPatch;
}

void SettingsManager::setShareFolderPatch(AnsiString newShareFolderPatch){
	shareFolderPatch = newShareFolderPatch; 
}
	
////////////////Путь к директории анонсов
AnsiString SettingsManager::getAnonsTextFolderPatch(){
	return anonsTextFolderPatch;
}

void SettingsManager::setAnonsTextFolderPatch(AnsiString newAnonsTextFolderPatch){
	anonsTextFolderPatch = newAnonsTextFolderPatch;
}
	
///////////////Путь к базе сессий
AnsiString SettingsManager::getSessionFolderPatch(){
	return sessionFolderPatch;
}


void SettingsManager::setSessionFolderPatch(AnsiString newSessionFolderPatch){
	sessionFolderPatch = newSessionFolderPatch;
}

//Загрузить настройки
void SettingsManager::loadSettings(){
	TiXmlDocument *settingsDoc = new TiXmlDocument(settingsPatch.c_str());

	if(!settingsDoc ->LoadFile()){
		ShowMessage("Настройки не восстановленны!");
		ShowMessage(settingsDoc ->ErrorDesc());
		errorKey = true;
                return;
	}
	
	//Восстанавливаем путь к рабочей папке
	TiXmlElement *workPatchElement = settingsDoc->FirstChildElement(XML_WORK_PATCH);
	if(workPatchElement==NULL){
		ShowMessage("Ошибка файла настроек! нет пути к рабочей папке");
                errorKey = true;
	} else {
		workFolderPatch = workPatchElement->GetText();
        }

	//Восстанавливаем путь к базе изображений
	TiXmlElement *baseImagePatchElement = settingsDoc->FirstChildElement(XML_BASE_IMAGE_PATCH);
	if(baseImagePatchElement==NULL){
		ShowMessage("Ошибка файла настроек! нет пути к базе изображений");
                errorKey = true;
	} else {
		baseImageFolderPatch = baseImagePatchElement->GetText();
        }

	//Восстанавливаем путь к директории анонсов
	TiXmlElement *anonsTextPatchElement = settingsDoc->FirstChildElement(XML_ANONS_TEXT_PATCH);
	if(anonsTextPatchElement==NULL){
		ShowMessage("Ошибка файла настроек! нет пути к папке с текстами анонсов");
                errorKey = true;
	} else {
		anonsTextFolderPatch = anonsTextPatchElement->GetText();
        }

	//Восстанавливаем путь к базе сессий
	TiXmlElement *sessionFolderPatchElement = settingsDoc->FirstChildElement(XML_SESSION_PATCH);
	if(sessionFolderPatchElement==NULL){
		ShowMessage("Ошибка файла настроек! нет пути к папке сессий");
                errorKey = true;
	} else {
		sessionFolderPatch = sessionFolderPatchElement->GetText();
        }

	//Восстанавливаем путь к выходным директориям вёрстки
	TiXmlElement *shareFolderPatchElement = settingsDoc->FirstChildElement(XML_SHARE_PATCH);
	if(shareFolderPatchElement==NULL){
		ShowMessage("Ошибка файла настроек! нет пути к шаре");
                errorKey = true;
	} else {
		shareFolderPatch = shareFolderPatchElement->GetText();
        }
	//Проверяем восстановленные строки, если размер = 0 это ошибка

        if (workFolderPatch.IsEmpty()){
        	ShowMessage("Нулевой размер пути к рабочей папке");
                errorKey = true;
        }

	if (baseImageFolderPatch.IsEmpty()){
        	ShowMessage("Нулевой размер пути к базе изображений");
                errorKey = true;
        }

	if (anonsTextFolderPatch.IsEmpty()){
        	ShowMessage("Нулевой размер пути к папке с текстами анонсов");
                errorKey = true;
        }


        if (sessionFolderPatch.IsEmpty()){
        	ShowMessage("Нулевой размер пути к папке сессий");
                errorKey = true;
        }

	if (shareFolderPatch.IsEmpty()){
        	ShowMessage("Нулевой размер пути к шаре");
                errorKey = true;
        }
}


//Сохранить настройки
void SettingsManager::saveSettings(){
	TiXmlDocument doc;
	//Создаём заголовок
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "windows-1251", "" );
	doc.LinkEndChild(decl);

	//Добавляем путь к рабочей папке
	TiXmlElement *workPatchElement = new TiXmlElement(XML_WORK_PATCH);
	workPatchElement->LinkEndChild(new TiXmlText(workFolderPatch.c_str()));
	doc.LinkEndChild(workPatchElement);

	//Добавляем путь к базе изображений
	TiXmlElement *baseImagePatchElement = new TiXmlElement(XML_BASE_IMAGE_PATCH);
	baseImagePatchElement->LinkEndChild(new TiXmlText(baseImageFolderPatch.c_str()));
	doc.LinkEndChild(baseImagePatchElement);
	
	
	//Добавляем путь к директории анонсов
	TiXmlElement *anonsTextPatchElement = new TiXmlElement(XML_ANONS_TEXT_PATCH);
	anonsTextPatchElement->LinkEndChild(new TiXmlText(anonsTextFolderPatch.c_str()));
	doc.LinkEndChild(anonsTextPatchElement);
	
	
	
	//Добавляем путь к базе сессий
	TiXmlElement *sessionFolderPatchElement = new TiXmlElement(XML_SESSION_PATCH);
	sessionFolderPatchElement->LinkEndChild(new TiXmlText(sessionFolderPatch.c_str()));
	doc.LinkEndChild(sessionFolderPatchElement);
	
	
	
	//Добавляем путь к выходным директориям вёрстки
	TiXmlElement *shareFolderPatchElement = new TiXmlElement(XML_SHARE_PATCH);
	shareFolderPatchElement->LinkEndChild(new TiXmlText(shareFolderPatch.c_str()));
	doc.LinkEndChild(shareFolderPatchElement);
	
	//Сохраняем файл
	doc.SaveFile(settingsPatch.c_str());
}
	
//всё-ли в порядке?
bool SettingsManager::isOk(){
	return !errorKey;
}