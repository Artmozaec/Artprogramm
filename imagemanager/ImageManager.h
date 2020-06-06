#ifndef OutDirectoryManagerH
#define OutDirectoryManagerH
#include <vcl.h>
#include "WeekDay.h"
#include "FilmContainer.h"

class ImageManager{
public:
	ImageManager(FilmContainer *inFilmContainer);

        //���������� ������ ���� � �����
        //���� � �������� �����������, ����� � ��������� �����������
        //���� �� ���� �� ���������, �� ����� ���������� NULL
        AnsiString getPatch(AnsiString fileName);

        //���������� ������ ������ � ����� ���� �����������(��� ���������)
        TStringList *getBaseImageContent();

        //����� ������� ����������
        TStringList *getWorkFolderContent();

        //��������������� ���� � ������ oldName
        void renameFile(AnsiString oldName, AnsiString newName);


        //////////////////////������////////////////////////////
        //���������� ������, ����������� ������
        void terminateSession();

        //������� �������� ����������
        void clearOutFolders();
		
		
        //////////////������������� �����///////////////
        void setImageStoragePatch(AnsiString inImageStoragePatch);

        void setWorkDirectoryPatch(AnsiString inWorkDirectoryPatch);

        void setShareFolderPatch(AnsiString inShareFolderPatch);
private:
	//���� � �������� � ����������
	AnsiString imageStoragePatch;

	//������� �������
	AnsiString workDirectoryPatch;

	//������� �� ����
	AnsiString shareFolderPatch;


	//������ ������ � ���������� - ��������� �����������, (��� ����������)
	TStringList *imageBaseContent;

	//���������
	FilmContainer *filmContainer;

	//���� ���� fileName � �������� ����������� � � ����
	//���������� ���� � ����� � ������ ��������� ������� ����,
	//���� �� ������� ���������� NULL
	AnsiString searchFileInDirectories(AnsiString fileName);

	//���������� ���� � ������� ���������� ����� inList - ��� ����������
	void clearExtension(TStringList *inList);
	AnsiString getWithoutExtension(AnsiString name);
	AnsiString getExtension(AnsiString patch, AnsiString file);

	void listToLowerCase(TStringList *inList);

	///////////////////////������///////////////////////////////////////////
	//� ������������ � ����� ������(��� �� ��������������), �������� ����� � ���� ������� ����� � ���� ����������� � ������ ������ � ��� �����
	//��� ��������� ����� ���� ����������� ����� � ��������� ��� � ����
	void createBadTypesFilmLabels();

	//��������� ������ ������ folderContent �� ������� ������ jpg - �������������� �������
	bool checkNotCorrectFilms(TStringList *folderContent);

	//��������� �� name �� ������� ���������� Tif
	bool fileIsCorrect(AnsiString name);

	//��������� ���������� �������� ����������
	bool DirectoryContentIsOk();

	//����������� ����������� ���������� ������ � ��������� ������
	void saveDirectoryContentInStore();

};

#endif