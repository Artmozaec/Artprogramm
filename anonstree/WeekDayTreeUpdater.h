#ifndef WeekDayTreeUpdaterH
#define WeekDayTreeUpdaterH
#include "FilmContainer.h"
#include "FilmIterator.h"
#include <ComCtrls.hpp>//“ам TTreeView
#include "WeekDay.h"
#include "AbstractTreeUpdater.h"

class WeekDayTreeUpdater : public AbstractTreeUpdater{
public:
	WeekDayTreeUpdater(FilmContainer *inFilmContainer);
        virtual void updateTree(TTreeView *tree);
        virtual bool isErrorNode(TTreeNode *node);
private:
	void updateWeekDayNodes(TTreeView *tree);
	void updateFilmNodes(TTreeView *tree);
	bool checkRootNodesCorrect(TTreeView *tree);

        //»щет фильмы день недели которых не совпадает с фетвью в которой они наход€тс€
        FilmContainer *getChangeWeekDayFilms(TTreeView *tree);

	FilmContainer *filmContainer;

        void WeekDayTreeUpdater::addFilmsToTree(TTreeView *tree, FilmContainer *addFilms);
        void WeekDayTreeUpdater::deleteFilmsToTree(TTreeView *tree, FilmContainer *addFilms);

};
#endif