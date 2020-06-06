#ifndef WeekDayTreeUpdaterH
#define WeekDayTreeUpdaterH
#include "FilmContainer.h"
#include "FilmIterator.h"
#include <ComCtrls.hpp>//��� TTreeView
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

        //���� ������ ���� ������ ������� �� ��������� � ������ � ������� ��� ���������
        FilmContainer *getChangeWeekDayFilms(TTreeView *tree);

	FilmContainer *filmContainer;

        void WeekDayTreeUpdater::addFilmsToTree(TTreeView *tree, FilmContainer *addFilms);
        void WeekDayTreeUpdater::deleteFilmsToTree(TTreeView *tree, FilmContainer *addFilms);

};
#endif