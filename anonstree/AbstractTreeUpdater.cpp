#include <ComCtrls.hpp>//��� TTreeView
#include "AbstractTreeUpdater.h"
#include "FilmContainerUtilites.h"

FilmContainer *AbstractTreeUpdater::searchAddFilms(TTreeView *tree, FilmContainer *filmContainer){
        FilmContainer *resultContainer = new FilmContainer();
        FilmIterator *filmIterator = filmContainer->getIterator();

        while (filmIterator->nextFilm()){
                //���� �������� ������ ��� � ������
                if (!filmInTreeExist(tree, filmIterator->getFilm())){
                        //��������� ��� � �������������� ���������
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
                  (!existFilm(((Film *)tree->Items->Item[ch]->Data), filmContainer))){//���� ������ �� ���������� � ����������
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

////////////////////////////����� � ������///////////////////////
TTreeNode *AbstractTreeUpdater::searchRootNode(TTreeView *tree, AnsiString nodeString){
        for (int ch=0; ch<tree->Items->Count; ch++){
                if((tree->Items->Item[ch]->Data == NULL) && //�������� �� �������c�� ���� - �����
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

//��������� ��� �������� �������
void AbstractTreeUpdater::filmNodeNamesUpdate(TTreeView *tree){
      for (int ch=0; ch<tree->Items->Count; ch++){
              if(tree->Items->Item[ch]->Data != NULL){
                        tree->Items->Item[ch]->Text = ((Film *)tree->Items->Item[ch]->Data)->getBaseFilmName();
              }
      }
}





// ������� ������ ��������� ����
void AbstractTreeUpdater::deleteEmptyErrorRoots(TTreeView *tree){
      for (int ch=0; ch<tree->Items->Count; ch++){
                if ((isErrorNode(tree->Items->Item[ch])) && //���� ����� ���������
                   (tree->Items->Item[ch]->Count == 0)){//� ������
                        tree->Items->Delete(tree->Items->Item[ch]);
                }
      }
}