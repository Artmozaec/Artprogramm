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
                if (tree->Items->Item[ch]->Data!=NULL){//Не корневой узел
                        //Получаем родительский узел канала
                        TTreeNode *rootNode = tree->Items->Item[ch]->Parent;
                        Film *film = (Film *)tree->Items->Item[ch]->Data;

                        //Если день недели фильма не совпадает с текстом родительского узла
                        if (rootNode->Text != film->getWeekDay().getDayString()) resultContainer->addFilm(film);
                }
        }
        return resultContainer;
}


bool WeekDayTreeUpdater::checkRootNodesCorrect(TTreeView *tree){
	WeekDay *weekDay = new WeekDay(1);

	for (int ch=0; ch<tree->Items->Count; ch++){
		if (tree->Items->Item[ch]->Data == NULL){//Признак корневого узла
			if (tree->Items->Item[ch]->Text != weekDay->getDayString()) return false;

                        //Если мы прошли все дни недели то всё соответствует
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
                        //Создаём канал-ошибку
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

        //Если будет пересещение филма из дня в день, то выделение на переносимом фильме исчезнет
        //По этому, сохраняем его заранее, а потом вернем выделение
        if (tree->Selected != NULL) selectFilm = (Film *)tree->Selected->Data;

        //Фильмы в которых поменяли день недели с начала удаляются
        deletedFilms->addFilmContainer(weekDayChangedFilms);

        deleteFilmsToTree(tree, deletedFilms);

        FilmContainer *addedFilms = searchAddFilms(tree, filmContainer);
        addFilmsToTree(tree, addedFilms);

        selectFilmInTree(tree, selectFilm);
        //Обновить названия фильмов
        filmNodeNamesUpdate(tree);
}

void WeekDayTreeUpdater::updateTree(TTreeView *tree){
	//Проверяем соответствуют-ли корневые узлы дням недели
	//Если нет
	if (!checkRootNodesCorrect(tree)){
                updateWeekDayNodes(tree);
	}

        updateFilmNodes(tree);

        //Удаляем пустые ошибочные ветви
        deleteEmptyErrorRoots(tree);
}


