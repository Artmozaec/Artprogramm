#include <ComCtrls.hpp>//Там TTreeView
#include "AbstractTreeUpdater.h"
#include "FilmContainerUtilites.h"

FilmContainer *AbstractTreeUpdater::searchAddFilms(TTreeView *tree, FilmContainer *filmContainer){
        FilmContainer *resultContainer = new FilmContainer();
        FilmIterator *filmIterator = filmContainer->getIterator();

        while (filmIterator->nextFilm()){
                //Если текущего фильма нет в дереве
                if (!filmInTreeExist(tree, filmIterator->getFilm())){
                        //Добавляем его в результирующий контейнер
                        resultContainer->addFilm(filmIterator->getFilm());
                }
        }

        return resultContainer;
}

void AbstractTreeUpdater::selectFilmInTree(TTreeView *tree, Film *select){
        if ((tree == NULL) || (select == NULL)) return;
        for(int ch=0; ch<tree->Items->Count; ch++){
                if (tree->Items->Item[ch]->Data == select){
                        tree->Selected = tree->Items->Item[ch];
                }
        }
}

FilmContainer *AbstractTreeUpdater::searchDeletedFilms(TTreeView *tree, FilmContainer *filmContainer){
        FilmContainer *resultContainer = new FilmContainer();

        for (int ch=0; ch<tree->Items->Count; ch++){
                if((tree->Items->Item[ch]->Data != NULL) &&
                  (!existFilm(((Film *)tree->Items->Item[ch]->Data), filmContainer))){//Если фильма не существует в контейнере
                        resultContainer->addFilm((Film *)tree->Items->Item[ch]->Data);
                }
        }
        return resultContainer;
}





bool AbstractTreeUpdater::filmInTreeExist(TTreeView *tree, Film *film){
        for (int ch=0; ch<tree->Items->Count; ch++){
                if (tree->Items->Item[ch]->Data == film) return true;
        }

        return false;
}

////////////////////////////ПОИСК В ДЕРЕВЕ///////////////////////
TTreeNode *AbstractTreeUpdater::searchRootNode(TTreeView *tree, AnsiString nodeString){
        for (int ch=0; ch<tree->Items->Count; ch++){
                if((tree->Items->Item[ch]->Data == NULL) && //Проверка на корневоcть узла - канал
                   (tree->Items->Item[ch]->Text == nodeString))
                {
                        return tree->Items->Item[ch];
                }
        }
        return NULL;
}


TTreeNode *AbstractTreeUpdater::searchFilmNode(TTreeView *tree, Film *film){
        for (int ch=0; ch<tree->Items->Count; ch++){
              if((Film *)tree->Items->Item[ch]->Data == film) return tree->Items->Item[ch];
        }
        return NULL;
}

//Обновляет все названия фильмов
void AbstractTreeUpdater::filmNodeNamesUpdate(TTreeView *tree){
      for (int ch=0; ch<tree->Items->Count; ch++){
              if(tree->Items->Item[ch]->Data != NULL){
                        tree->Items->Item[ch]->Text = ((Film *)tree->Items->Item[ch]->Data)->getBaseFilmName();
              }
      }
}





// Удаляет пустые ошибочные узлы
void AbstractTreeUpdater::deleteEmptyErrorRoots(TTreeView *tree){
      for (int ch=0; ch<tree->Items->Count; ch++){
                if ((isErrorNode(tree->Items->Item[ch])) && //Если ветка ошибочная
                   (tree->Items->Item[ch]->Count == 0)){//и пустая
                        tree->Items->Delete(tree->Items->Item[ch]);
                }
      }
}