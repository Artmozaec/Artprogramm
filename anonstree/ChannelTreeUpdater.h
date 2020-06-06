#ifndef ChannelTreeUpdaterH
#define ChannelTreeUpdaterH
#include "FilmContainer.h"
#include "FilmIterator.h"
#include "ChannelFilesAndNames.h"
#include <ComCtrls.hpp>//��� TTreeView
#include "AbstractTreeUpdater.h"


class ChannelTreeUpdater : public AbstractTreeUpdater{
public:
	ChannelTreeUpdater(FilmContainer *inFilmContainer, ChannelFilesAndNames *inChannelFilesAndNames);
	
	//��������� ���������� tree � ������������ � ����������� 
	//������ ������� (Channels) � ���������� ������� (FilmContainer)
	virtual void updateTree(TTreeView *tree);
	
	virtual bool isErrorNode(TTreeNode *node);
private:
	FilmContainer *filmContainer;
	ChannelFilesAndNames *channelFilesAndNames;

        //���� ������ ����� ������� �� ��������� � ������ � ������� ��� ���������
        FilmContainer *getChangeChannelFilms(TTreeView *tree);

	void updateChannelNodes(TTreeView *tree);
	void updateFilmNodes(TTreeView *tree);

        //����� � �������� ����� tree ���� � ������� - channelName
        bool channelNameInTreeExist(TTreeView *tree, AnsiString channelName);

        void addFilmsToTree(TTreeView *tree, FilmContainer *addFilms);
        void deleteFilmsToTree(TTreeView *tree, FilmContainer *addFilms);


};

#endif