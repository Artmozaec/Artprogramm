#ifndef SettingsManagerH
#define SettingsManagerH


#include <vcl.h>

class SettingsManager{
public:
	SettingsManager(AnsiString inSettingsPatch);
	
	////////////////���� � ������� ����������
	AnsiString getWorkFolderPatch();
	void setWorkFolderPatch(AnsiString newWorkFolderPatch);
	
	////////////////���� � ���� �����������
	AnsiString getBaseImageFolderPatch();
	void setBaseImageFolderPatch(AnsiString newBaseImageFolderPatch);
	
	////////////////���� � ���������� ������
	AnsiString getShareFolderPatch();
	void setShareFolderPatch(AnsiString newShareFolderPatch);
	
	////////////////���� � ���������� �������
	AnsiString getAnonsTextFolderPatch();
	void setAnonsTextFolderPatch(AnsiString newAnonsTextFolderPatch);
	
	///////////////���� � ���� ������
	AnsiString getSessionFolderPatch();
	void setSessionFolderPatch(AnsiString newSessionFolderPatch);
	
	//��������� ���������
	void saveSettings();
	
	//��-�� � �������?
	bool isOk();
	
	
private:
	//���� ������
	bool errorKey;
	
	AnsiString settingsPatch;
	
	//���� � ������� ����������
	AnsiString workFolderPatch;
	
	//���� � ���� �����������
	AnsiString baseImageFolderPatch;
	
	//���� � ���������� �������
	AnsiString anonsTextFolderPatch;
	
	//���� � ���� ������
	AnsiString sessionFolderPatch;
	
	//���� � �������� ����������� ������
	AnsiString shareFolderPatch;
	
	
	//��������� ���������
	void loadSettings();
};


#endif