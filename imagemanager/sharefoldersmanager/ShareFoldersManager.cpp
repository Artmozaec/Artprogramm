#include "ShareFoldersManager.h"

#include "FilmIterator.h"
#include "WeekDay.h"
#include "FileOperations.cpp"
#include "StringsUtilites.h"
//#include <SysUtils.hpp>
#include <stdio.h>
ShareFoldersManager::ShareFoldersManager(AnsiString inStorePatch, AnsiString inShareFolderPatch){

	shareFolderPatch = inShareFolderPatch;
        storePatch = inStorePatch;

	weekDayFolders = new TStringList();
	weekDayFolders->Add(*new AnsiString("anons01\\"));
	weekDayFolders->Add(*new AnsiString("anons02\\"));
	weekDayFolders->Add(*new AnsiString("anons03\\"));
	weekDayFolders->Add(*new AnsiString("anons04\\"));
	weekDayFolders->Add(*new AnsiString("anons05\\"));
	weekDayFolders->Add(*new AnsiString("anons06\\"));
	weekDayFolders->Add(*new AnsiString("anons07\\"));
}

//��������� ���� � �����, ����� ����� ��� ������
AnsiString ShareFoldersManager::generateSharePatch(Film *film){
	WeekDay weekDay = film->getWeekDay();
	return shareFolderPatch+weekDayFolders->Strings[weekDay.getDayInt()-1];
}

//��������� ������ ����� ��� ������ �� ��������� �������
AnsiString ShareFoldersManager::generateFileName(Film *film){

        AnsiString *name = new AnsiString(film->getBaseFilmName());
        //ShowMessage(*name);
        clearFileSystemServiceSymbol(name);
        //ShowMessage(*name);
	return *name+".tif";
}


void ShareFoldersManager::copyContentImageToShare(Film *film){
	AnsiString workPatch = storePatch+film->getBaseImageName()+".tif";
        //ShowMessage(workPatch);
	AnsiString sharePatch = generateSharePatch(film)+generateFileName(film);
        //ShowMessage(sharePatch);
        //��������� ������� ������ � �����
        if ((workPatch.IsEmpty())||(!FileExists(workPatch))){
        	ShowMessage("!!!!!������ ����������!!!!!!!");
                ShowMessage("�� ������ ���� >>>> "+workPatch);
                return;
        }

        if (!DirectoryExists(generateSharePatch(film))){
	        ShowMessage("!!!!!������ ����������!!!!!!!");
		ShowMessage("����������� ����� ������ >>>> "+sharePatch);
                return;

        }

	CopyFile(workPatch.c_str(), sharePatch.c_str(), false);

}

//������� ���������� �������
void ShareFoldersManager::clearShareDirectories(){
	TStringList *files = new TStringList();
	for (int day=0; day<=6; day++){
		AnsiString *patch =new AnsiString(shareFolderPatch+weekDayFolders->Strings[day]);
		getDirectoryContent(*patch, files);
		deleteFiles(*patch, files);

                //�������� ������
		files->Clear();
	}
}


//��������� ������� ���������� ����������� ������ � �������� �����������
void ShareFoldersManager::saveSession(FilmContainer *filmContainer){
        //������� ���������� ����
	clearShareDirectories();

	FilmIterator *iterator = filmContainer->getIterator();
	Film *film;
	while (iterator->nextFilm()){
		film = iterator->getFilm();
		//���� � ������ ���� ����������� �������� ��� � ����� ������
		if (film->imageExist()){
			copyContentImageToShare(film);
		}

	}
}