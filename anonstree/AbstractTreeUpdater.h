#ifndef AbstractTreeUpdaterH
#define AbstractTreeUpdaterH
#include "FilmContainer.h"
#include "FilmIterator.h"
#include "WeekDay.h"
#include "ChannelFilesAndNames.h"

class AbstractTreeUpdater{
public:
	virtual void updateTree(TTreeView *tree)=0;
	virtual bool isErrorNode(TTreeNode *node)=0;

        //���������� select � tree � �������� ���
        void selectFilmInTree(TTreeView *tree, Film *select);
protected:
	FilmContainer *searchAddFilms(TTreeView *tree, FilmContainer *filmContainer);
	FilmContainer *searchDeletedFilms(TTreeView *tree, FilmContainer *filmContainer);
	bool filmInTreeExist(TTreeView *tree, Film *film);
	TTreeNode *searchRootNode(TTreeView *tree, AnsiString nodeString);
	TTreeNode *searchFilmNode(TTreeView *tree, Film *film);

        //��������� ����� ��������� � ������-�������� - (�������� ������)
	void filmNodeNamesUpdate(TTreeView *tree);

        //������� ������ �����-������
	void deleteEmptyErrorRoots(TTreeView *tree);
};

#endif