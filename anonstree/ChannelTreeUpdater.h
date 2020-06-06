#ifndef ChannelTreeUpdaterH
#define ChannelTreeUpdaterH
#include "FilmContainer.h"
#include "FilmIterator.h"
#include "ChannelFilesAndNames.h"
#include <ComCtrls.hpp>//“ам TTreeView
#include "AbstractTreeUpdater.h"


class ChannelTreeUpdater : public AbstractTreeUpdater{
public:
	ChannelTreeUpdater(FilmContainer *inFilmContainer, ChannelFilesAndNames *inChannelFilesAndNames);
	
	//ќбновл€ет содержимое tree в соответствии с изменени€ми 
	//файлов каналов (Channels) и контейнера фильмов (FilmContainer)
	virtual void updateTree(TTreeView *tree);
	
	virtual bool isErrorNode(TTreeNode *node);
private:
	FilmContainer *filmContainer;
	ChannelFilesAndNames *channelFilesAndNames;

        //»щет фильмы канал которых не совпадает с фетвью в которой они наход€тс€
        FilmContainer *getChangeChannelFilms(TTreeView *tree);

	void updateChannelNodes(TTreeView *tree);
	void updateFilmNodes(TTreeView *tree);

        //ѕоиск в корневых узлах tree узла с текстом - channelName
        bool channelNameInTreeExist(TTreeView *tree, AnsiString channelName);

        void addFilmsToTree(TTreeView *tree, FilmContainer *addFilms);
        void deleteFilmsToTree(TTreeView *tree, FilmContainer *addFilms);


};

#endif