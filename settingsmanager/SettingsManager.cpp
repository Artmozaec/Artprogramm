#include "SettingsManager.h"
#include "tinyxml.h"
#include "XMLElementsSettings.cpp"


SettingsManager::SettingsManager(AnsiString inSettingsPatch){
	//������������� (��������� ������ �������)
	TiXmlBase::SetCondenseWhiteSpace(false);
        
	settingsPatch = *new AnsiString(inSettingsPatch+"settings.xml");
	//������ ���� ���
	errorKey = false;
	
	//�������������
	workFolderPatch = *new AnsiString();
	baseImageFolderPatch = *new AnsiString();
	anonsTextFolderPatch = *new AnsiString();
	sessionFolderPatch = *new AnsiString();
	shareFolderPatch = *new AnsiString();
	
	//�������� ������ ���������
	loadSettings();
	
}


////////////////���� � ������� ����������
AnsiString SettingsManager::getWorkFolderPatch(){
	return workFolderPatch;
}


void SettingsManager::setWorkFolderPatch(AnsiString newWorkFolderPatch){
	workFolderPatch = newWorkFolderPatch;
}
	
////////////////���� � ���� �����������
AnsiString SettingsManager::getBaseImageFolderPatch(){
	return baseImageFolderPatch;
}

void SettingsManager::setBaseImageFolderPatch(AnsiString newBaseImageFolderPatch){
	baseImageFolderPatch = newBaseImageFolderPatch;
}
	
////////////////���� � ���������� ������
AnsiString SettingsManager::getShareFolderPatch(){
	return shareFolderPatch;
}

void SettingsManager::setShareFolderPatch(AnsiString newShareFolderPatch){
	shareFolderPatch = newShareFolderPatch; 
}
	
////////////////���� � ���������� �������
AnsiString SettingsManager::getAnonsTextFolderPatch(){
	return anonsTextFolderPatch;
}

void SettingsManager::setAnonsTextFolderPatch(AnsiString newAnonsTextFolderPatch){
	anonsTextFolderPatch = newAnonsTextFolderPatch;
}
	
///////////////���� � ���� ������
AnsiString SettingsManager::getSessionFolderPatch(){
	return sessionFolderPatch;
}


void SettingsManager::setSessionFolderPatch(AnsiString newSessionFolderPatch){
	sessionFolderPatch = newSessionFolderPatch;
}

//��������� ���������
void SettingsManager::loadSettings(){
	TiXmlDocument *settingsDoc = new TiXmlDocument(settingsPatch.c_str());

	if(!settingsDoc ->LoadFile()){
		ShowMessage("��������� �� ��������������!");
		ShowMessage(settingsDoc ->ErrorDesc());
		errorKey = true;
                return;
	}
	
	//��������������� ���� � ������� �����
	TiXmlElement *workPatchElement = settingsDoc->FirstChildElement(XML_WORK_PATCH);
	if(workPatchElement==NULL){
		ShowMessage("������ ����� ��������! ��� ���� � ������� �����");
                errorKey = true;
	} else {
		workFolderPatch = workPatchElement->GetText();
        }

	//��������������� ���� � ���� �����������
	TiXmlElement *baseImagePatchElement = settingsDoc->FirstChildElement(XML_BASE_IMAGE_PATCH);
	if(baseImagePatchElement==NULL){
		ShowMessage("������ ����� ��������! ��� ���� � ���� �����������");
                errorKey = true;
	} else {
		baseImageFolderPatch = baseImagePatchElement->GetText();
        }

	//��������������� ���� � ���������� �������
	TiXmlElement *anonsTextPatchElement = settingsDoc->FirstChildElement(XML_ANONS_TEXT_PATCH);
	if(anonsTextPatchElement==NULL){
		ShowMessage("������ ����� ��������! ��� ���� � ����� � �������� �������");
                errorKey = true;
	} else {
		anonsTextFolderPatch = anonsTextPatchElement->GetText();
        }

	//��������������� ���� � ���� ������
	TiXmlElement *sessionFolderPatchElement = settingsDoc->FirstChildElement(XML_SESSION_PATCH);
	if(sessionFolderPatchElement==NULL){
		ShowMessage("������ ����� ��������! ��� ���� � ����� ������");
                errorKey = true;
	} else {
		sessionFolderPatch = sessionFolderPatchElement->GetText();
        }

	//��������������� ���� � �������� ����������� ������
	TiXmlElement *shareFolderPatchElement = settingsDoc->FirstChildElement(XML_SHARE_PATCH);
	if(shareFolderPatchElement==NULL){
		ShowMessage("������ ����� ��������! ��� ���� � ����");
                errorKey = true;
	} else {
		shareFolderPatch = shareFolderPatchElement->GetText();
        }
	//��������� ��������������� ������, ���� ������ = 0 ��� ������

        if (workFolderPatch.IsEmpty()){
        	ShowMessage("������� ������ ���� � ������� �����");
                errorKey = true;
        }

	if (baseImageFolderPatch.IsEmpty()){
        	ShowMessage("������� ������ ���� � ���� �����������");
                errorKey = true;
        }

	if (anonsTextFolderPatch.IsEmpty()){
        	ShowMessage("������� ������ ���� � ����� � �������� �������");
                errorKey = true;
        }


        if (sessionFolderPatch.IsEmpty()){
        	ShowMessage("������� ������ ���� � ����� ������");
                errorKey = true;
        }

	if (shareFolderPatch.IsEmpty()){
        	ShowMessage("������� ������ ���� � ����");
                errorKey = true;
        }
}


//��������� ���������
void SettingsManager::saveSettings(){
	TiXmlDocument doc;
	//������ ���������
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "windows-1251", "" );
	doc.LinkEndChild(decl);

	//��������� ���� � ������� �����
	TiXmlElement *workPatchElement = new TiXmlElement(XML_WORK_PATCH);
	workPatchElement->LinkEndChild(new TiXmlText(workFolderPatch.c_str()));
	doc.LinkEndChild(workPatchElement);

	//��������� ���� � ���� �����������
	TiXmlElement *baseImagePatchElement = new TiXmlElement(XML_BASE_IMAGE_PATCH);
	baseImagePatchElement->LinkEndChild(new TiXmlText(baseImageFolderPatch.c_str()));
	doc.LinkEndChild(baseImagePatchElement);
	
	
	//��������� ���� � ���������� �������
	TiXmlElement *anonsTextPatchElement = new TiXmlElement(XML_ANONS_TEXT_PATCH);
	anonsTextPatchElement->LinkEndChild(new TiXmlText(anonsTextFolderPatch.c_str()));
	doc.LinkEndChild(anonsTextPatchElement);
	
	
	
	//��������� ���� � ���� ������
	TiXmlElement *sessionFolderPatchElement = new TiXmlElement(XML_SESSION_PATCH);
	sessionFolderPatchElement->LinkEndChild(new TiXmlText(sessionFolderPatch.c_str()));
	doc.LinkEndChild(sessionFolderPatchElement);
	
	
	
	//��������� ���� � �������� ����������� ������
	TiXmlElement *shareFolderPatchElement = new TiXmlElement(XML_SHARE_PATCH);
	shareFolderPatchElement->LinkEndChild(new TiXmlText(shareFolderPatch.c_str()));
	doc.LinkEndChild(shareFolderPatchElement);
	
	//��������� ����
	doc.SaveFile(settingsPatch.c_str());
}
	
//��-�� � �������?
bool SettingsManager::isOk(){
	return !errorKey;
}