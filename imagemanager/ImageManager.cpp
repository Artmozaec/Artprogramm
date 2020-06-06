#include "ImageManager.h"
#include "FileOperations.cpp"
#include <SysUtils.hpp>
//#include "ShellAPI.h"
#include <stdio.h>
#include "ShareFoldersManager.h"
#include "FilmIterator.h"
#include "StringsUtilites.h"
#include "FileReaderWriter.h"

ImageManager::ImageManager(FilmContainer *inFilmContainer){
	filmContainer = inFilmContainer;

	imageStoragePatch = *new AnsiString();
	workDirectoryPatch = *new AnsiString();
    shareFolderPatch = *new AnsiString();

    imageBaseContent = new TStringList();
}

//����� ������� ����������
TStringList *ImageManager::getWorkFolderContent(){
	TStringList *content = new TStringList();

        //�������� ������ ������ ������� �����
	getDirectoryContent(workDirectoryPatch, content);

	//�������� ����������
        clearExtension(content);

        //� ������ �������
        listToLowerCase(content);

        return content;
}

//���������� ���� �����������
TStringList *ImageManager::getBaseImageContent(){
     return imageBaseContent;
}




void ImageManager::listToLowerCase(TStringList *inList){
        for(int ch=0; ch<inList->Count; ch++){
            inList->Strings[ch] = inList->Strings[ch].LowerCase();
        }
}


void ImageManager::clearExtension(TStringList *inList){
        for (int ch=0; ch<inList->Count; ch++){
                //���� ��� ����� ��� ����������
                inList->Strings[ch] = getWithoutExtension(inList->Strings[ch]);
        }
}



//���������� ��� ����� name ��� ����������
AnsiString ImageManager::getWithoutExtension(AnsiString name){
     //������� ������� ������ ���������� �����
     int pos = name.Pos(ExtractFileExt(name));

     //������� ��� �� ���� �������
     name.SetLength(pos-1);

     return name;
}


AnsiString ImageManager::getExtension(AnsiString patch, AnsiString file){
        //���� ���� - ���� �����������, ��� ������ tif
        if (patch == imageStoragePatch) return *new AnsiString(".tif");

        //�������� ������ ������ �� ���� patch
        TStringList *fileList = new TStringList();
        getDirectoryContent(patch, fileList);
        //� ������ �������!
        listToLowerCase(fileList);


        //������� ���������� � ����� � ������� ������
        for (int ch=0; ch<fileList->Count; ch++){
                if (fileList->Strings[ch].Pos(file) != 0){
                        return ExtractFileExt(fileList->Strings[ch]);
                }
        }

        return *new AnsiString();
}


AnsiString ImageManager::getPatch(AnsiString fileName){
        if (fileName.IsEmpty()) return *new AnsiString();

        //� ������ ���������� � ����� ����� ����� ������� ����
        AnsiString patch = searchFileInDirectories(fileName);

        //���� �� ������ �� �����,
        if (patch.IsEmpty()){
                return patch;
        }

	//������� ���������� �����
        AnsiString ext = getExtension(patch, fileName);

        return patch+fileName+ext;
}

void ImageManager::renameFile(AnsiString oldName, AnsiString newName){
        AnsiString oldNameDirectory = searchFileInDirectories(oldName);
        AnsiString oldNameExtension = getExtension(oldNameDirectory, oldName);

        if (oldNameDirectory.IsEmpty()){
                ShowMessage("���� "+oldName+" �����������!");
                return;
        }

        rename(
                new AnsiString (oldNameDirectory+oldName+oldNameExtension)->c_str(),
                new AnsiString (oldNameDirectory+newName+oldNameExtension)->c_str()
        );
}

AnsiString ImageManager::searchFileInDirectories(AnsiString fileName){
        //� ������ ���� ����� � ������ ������
        TStringList *dirList = getWorkFolderContent();

	if (dirList->IndexOf(fileName) != -1) return workDirectoryPatch;

        //���� � ���� �����������
        //� ���� ����� ������ ������ .tif �������
	if (FileExists(imageStoragePatch+fileName+".tif")) return imageStoragePatch;

        //������ �� �������, ������ ������ �������� ���� ����������� ����
        return *new AnsiString();
}


////////////////////////////������//////////////////////////////////////////////
//��������� ������ ����� � ����������� *.tif
bool ImageManager::fileIsCorrect(AnsiString name){
        if (ExtractFileExt(name) == ".tif") return true;
        return false;
}

//��������� ������ ������ folderContent �� ������� ������ �� tif - �������������� �������
bool ImageManager::checkNotCorrectFilms(TStringList *folderContent){
        for (int fileCh=0; fileCh<folderContent->Count; fileCh++){
                if (!fileIsCorrect(folderContent->Strings[fileCh])){
                      return false;
                }
        }
        return true;
}

//��������� ���������� �������� ����������
bool ImageManager::DirectoryContentIsOk(){
        TStringList *files = new TStringList();

	getDirectoryContent(workDirectoryPatch, files);
        if (!checkNotCorrectFilms(files)){
        	ShowMessage("������������ ������ ��������� �����!!!");
                return false;
        }

        return true;
}

//����������� ����������� ���������� ������ � ��������� ������
void ImageManager::saveDirectoryContentInStore(){
        TStringList *files = new TStringList();

        //���� ������ ������ ������� �����
        getDirectoryContent(workDirectoryPatch, files);

        //�������� ������ ������ � ���������
        copyFiles(workDirectoryPatch, imageStoragePatch, files);
}


//� ������������ � ����� ������(��� �� ��������������), �������� ����� � ���� ������� ����� � ���� ����������� � ������ ������ � ��� �����
//��� ��������� ����� ���� ����������� ����� � ��������� ��� � ����
void ImageManager::createBadTypesFilmLabels(){
	FilmIterator *iterator = filmContainer->getIterator();
        Film *film;
        AnsiString patch;
        AnsiString filmName;
        AnsiString filmDirector;
        while(iterator->nextFilm()){
                film = iterator->getFilm();
                //���� ��� ������ - �� ��������������
                if (film->getType() != FEATURE){
                	filmName = film->getBaseFilmName();

			filmDirector = film->getDirectors()->Strings[0];
	                //������� ��� �� ��������� ������ ��������
        	        clearFileSystemServiceSymbol(&filmName);

                	patch = imageStoragePatch+"("+film->getTypeString()+")"+filmName+" "+film->getYear()+" ("+filmDirector+").tif";

                	//ShowMessage(patch);
                	//������ ������ ���� � ������

                	FileReaderWriter *fileReaderWriter = new FileReaderWriter();
			fileReaderWriter->saveTextToFile(patch, new AnsiString(" "));
                }
        }
}

void ImageManager::terminateSession(){


        //��������� ��� �������� ����������
        //���� � ���������� ������, �� �������
        if (!DirectoryContentIsOk()) return;

        //�������� ���������� ���������� ������ � ��������� ������
        saveDirectoryContentInStore();

	//������ ����� ������ �����, ������, �������� ���-�� � ����... �� �����
        createBadTypesFilmLabels();

        //�������� ���������� �������� ���������� � ���������� �������
	ShareFoldersManager *shareFoldersManager = new ShareFoldersManager(imageStoragePatch, shareFolderPatch);
        shareFoldersManager->saveSession(filmContainer);

}


//������� �������� ����������
void ImageManager::clearOutFolders(){
	TStringList *workContent = new TStringList();

        getDirectoryContent(workDirectoryPatch, workContent);

        //��������� ������������-�� ��������� ����� � ���������?
        for(int ch=0; ch<workContent->Count; ch++){
        	//����-�� ������� ���� � ���������?
		if (!FileExists(imageStoragePatch+workContent->Strings[ch])){
                	ShowMessage("���� ("+workContent->Strings[ch]+")  � ��������� �����������!");
                        return;
                }
        }
	deleteFiles(workDirectoryPatch, workContent);
}

//////////////������������� �����///////////////
void ImageManager::setImageStoragePatch(AnsiString inImageStoragePatch){
	imageStoragePatch = inImageStoragePatch;

        //��������� ����� ���������
        getDirectoryContent(imageStoragePatch, imageBaseContent);

        //������� ����������
        clearExtension(imageBaseContent);

        //� ������ �������!
        listToLowerCase(imageBaseContent);
}

void ImageManager::setWorkDirectoryPatch(AnsiString inWorkDirectoryPatch){
	workDirectoryPatch = inWorkDirectoryPatch;
}

void ImageManager::setShareFolderPatch(AnsiString inShareFolderPatch){
	shareFolderPatch = inShareFolderPatch;
}
