#ifndef ShareFoldersManagerH
#define ShareFoldersManagerH
#include <vcl.h>
#include "FilmContainer.h"
#include "Film.h"


class ShareFoldersManager{
public:
	ShareFoldersManager(AnsiString inStorePatch, AnsiString inShareFolderPatch);
	
	//��������� ������� ���������� ����������� ������ � �������� �����������
	void saveSession(FilmContainer *filmContainer);
private:

	AnsiString shareFolderPatch;

	AnsiString storePatch;

	//�������� ����������� �������������� ���� ������
	TStringList *weekDayFolders;
	
	//����������� ����� ������������� � film � ����� ������
	void copyContentImageToShare(Film *film);
	
	//��������� ���� � �����, ����� ����� ��� ������
	AnsiString generateSharePatch(Film *film);
	
	//��������� ������ ����� ��� ������ �� ��������� �������
	AnsiString generateFileName(Film *film);

        //������� ���������� �������
        void clearShareDirectories();
};

#endif