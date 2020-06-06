#include "WeekDayTreeUpdater.h"

WeekDayTreeUpdater::WeekDayTreeUpdater(FilmContainer *inFilmContainer){
	filmContainer = inFilmContainer;
}

bool WeekDayTreeUpdater::isErrorNode(TTreeNode *node){
        if ((node->Data == NULL) && (node->Text == WeekDay::EMPTY_WEEK_DAY)) return true;
        return false;
}

FilmContainer *WeekDayTreeUpdater::getChangeWeekDayFilms(TTreeView *tree){
        FilmContainer *resultContainer = new FilmContainer();

        for (int ch=0; ch<tree->Items->Count; ch++){
                if (tree->Items->Item[ch]->Data!=NULL){//�� �������� ����
                        //�������� ������������ ���� ������
                        TTreeNode *rootNode = tree->Items->Item[ch]->Parent;
                        Film *film = (Film *)tree->Items->Item[ch]->Data;

                        //���� ���� ������ ������ �� ��������� � ������� ������������� ����
                        if (rootNode->Text != film->getWeekDay().getDayString()) resultContainer->addFilm(film);
                }
        }
        return resultContainer;
}


bool WeekDayTreeUpdater::checkRootNodesCorrect(TTreeView *tree){
	WeekDay *weekDay = new WeekDay(1);

	for (int ch=0; ch<tree->Items->Count; ch++){
		if (tree->Items->Item[ch]->Data == NULL){//������� ��������� ����
			if (tree->Items->Item[ch]->Text != weekDay->getDayString()) return false;

                        //���� �� ������ ��� ��� ������ �� �� �������������
			if (!weekDay->nextDay()) return true;
		}
	}
	return false;
}

void WeekDayTreeUpdater::updateWeekDayNodes(TTreeView *tree){
       WeekDay *weekDay = new WeekDay(1);
       tree->Items->Clear();
       do{
                tree->Items->Add(NULL, weekDay->getDayString());
       }while(weekDay->nextDay());
}





void WeekDayTreeUpdater::addFilmsToTree(TTreeView *tree, FilmContainer *addFilms){
        FilmIterator *filmIterator = addFilms->getIterator();
        TTreeNode *weekDayNode;
        while(filmIterator->nextFilm()){
                WeekDay weekDay = filmIterator->getFilm()->getWeekDay();
                 AnsiString filmName = filmIterator->getFilm()->getBaseFilmName();
                weekDayNode = searchRootNode(tree, weekDay.getDayString());
                if (weekDayNode == NULL){
                        //������ �����-������
                        weekDayNode = tree->Items->Add(NULL, *new AnsiString(WeekDay::EMPTY_WEEK_DAY));

                }


                tree->Items->AddChildObject(weekDayNode, filmName, filmIterator->getFilm());
        }
}


void WeekDayTreeUpdater::deleteFilmsToTree(TTreeView *tree, FilmContainer *addFilms){
        FilmIterator *filmIterator = addFilms->getIterator();
        TTreeNode *deleteNode;

        while (filmIterator->nextFilm()){

                deleteNode = searchFilmNode(tree, filmIterator->getFilm());
                tree->Items->Delete(deleteNode);

        }
}



void WeekDayTreeUpdater::updateFilmNodes(TTreeView *tree){
        FilmContainer *weekDayChangedFilms = getChangeWeekDayFilms(tree);

        FilmContainer *deletedFilms = searchDeletedFilms(tree, filmContainer);
        Film *selectFilm;

        //���� ����� ����������� ����� �� ��� � ����, �� ��������� �� ����������� ������ ��������
        //�� �����, ��������� ��� �������, � ����� ������ ���������
        if (tree->Selected != NULL) selectFilm = (Film *)tree->Selected->Data;

        //������ � ������� �������� ���� ������ � ������ ���������
        deletedFilms->addFilmContainer(weekDayChangedFilms);

        deleteFilmsToTree(tree, deletedFilms);

        FilmContainer *addedFilms = searchAddFilms(tree, filmContainer);
        addFilmsToTree(tree, addedFilms);

        selectFilmInTree(tree, selectFilm);
        //�������� �������� �������
        filmNodeNamesUpdate(tree);
}

void WeekDayTreeUpdater::updateTree(TTreeView *tree){
	//��������� �������������-�� �������� ���� ���� ������
	//���� ���
	if (!checkRootNodesCorrect(tree)){
                updateWeekDayNodes(tree);
	}

        updateFilmNodes(tree);

        //������� ������ ��������� �����
        deleteEmptyErrorRoots(tree);
}


