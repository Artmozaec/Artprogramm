#include "ChannelTreeUpdater.h"

ChannelTreeUpdater::ChannelTreeUpdater(FilmContainer *inFilmContainer, ChannelFilesAndNames *inChannelFilesAndNames){
	filmContainer = inFilmContainer;
	channelFilesAndNames = inChannelFilesAndNames;
}

bool ChannelTreeUpdater::isErrorNode(TTreeNode *node){
        TStringList *channelList = channelFilesAndNames->getChannelList();
        if ((node->Data == NULL) && (channelList->IndexOf(node->Text) == -1)) return true;
        return false;
}

void ChannelTreeUpdater::updateTree(TTreeView *tree){
        //��������� �������� ����
        updateChannelNodes(tree);

        //��������� ������ - ������
        updateFilmNodes(tree);

        //������� ������ ��������� �����
        deleteEmptyErrorRoots(tree);
}





void ChannelTreeUpdater::addFilmsToTree(TTreeView *tree, FilmContainer *addFilms){
        FilmIterator *filmIterator = addFilms->getIterator();
        TTreeNode *channelNode;
        while(filmIterator->nextFilm()){
                AnsiString channelName = filmIterator->getFilm()->getChannel();
                AnsiString filmName = filmIterator->getFilm()->getBaseFilmName();
                channelNode = searchRootNode(tree, channelName);
                //���� ����� �����������
                if (channelNode == NULL){
                        //������ �����-������
                        channelNode = tree->Items->Add(NULL, channelName);

                }
                tree->Items->AddChildObject(channelNode, filmName, filmIterator->getFilm());
        }
}


void ChannelTreeUpdater::deleteFilmsToTree(TTreeView *tree, FilmContainer *addFilms){
        FilmIterator *filmIterator = addFilms->getIterator();
        TTreeNode *deleteNode;

        while (filmIterator->nextFilm()){

                deleteNode = searchFilmNode(tree, filmIterator->getFilm());
                tree->Items->Delete(deleteNode);

        }
}


FilmContainer *ChannelTreeUpdater::getChangeChannelFilms(TTreeView *tree){
        FilmContainer *resultContainer = new FilmContainer();

        for (int ch=0; ch<tree->Items->Count; ch++){
                if (tree->Items->Item[ch]->Data!=NULL){//�� �������� ����
                        //�������� ������������ ���� ������
                        TTreeNode *rootNode = tree->Items->Item[ch]->Parent;
                        Film *film = (Film *)tree->Items->Item[ch]->Data;

                        //���� ����� ������ �� ��������� � ������� ������������� ����
                        if (rootNode->Text != film->getChannel()) resultContainer->addFilm(film);
                }
        }
        return resultContainer;
}

void ChannelTreeUpdater::updateFilmNodes(TTreeView *tree){
        FilmContainer *channelChangedFilms = getChangeChannelFilms(tree);

        FilmContainer *deletedFilms = searchDeletedFilms(tree, filmContainer);
        Film *selectFilm;

        //���� ����� ����������� ����� �� ������ � �����, �� ��������� �� ����������� ������ ��������
        //�� �����, ��������� ��� �������, � ����� ������ ���������
        if (tree->Selected != NULL) selectFilm = (Film *)tree->Selected->Data;

        //������ � ������� �������� ����� � ������ ���������
        deletedFilms->addFilmContainer(channelChangedFilms);
        deleteFilmsToTree(tree, deletedFilms);

        FilmContainer *addedFilms = searchAddFilms(tree, filmContainer);
        addFilmsToTree(tree, addedFilms);

        selectFilmInTree(tree, selectFilm);
        //�������� �������� �������
        filmNodeNamesUpdate(tree);
}


bool ChannelTreeUpdater::channelNameInTreeExist(TTreeView *tree, AnsiString channelName){
        for(int ch=0; ch<tree->Items->Count; ch++){

                if((tree->Items->Item[ch]->Data == NULL) && //�������� �� �������c�� ���� - �����
                   (tree->Items->Item[ch]->Text == channelName)){
                        return true;
                }
        }
        return false;
}

void ChannelTreeUpdater::updateChannelNodes(TTreeView *tree){
        //�������� ������� ������ �������
        TStringList *channelList = channelFilesAndNames->getChannelList();
        //���� ����������� ����� �������
        for (int ch=0; ch<channelList->Count; ch++){
                //���� �������� ������ ��� � ������, ������ ��������� ���
                if (!channelNameInTreeExist(tree, channelList->Strings[ch])){
                      tree->Items->Add(NULL, channelList->Strings[ch]);
                }
        }

        //���� �������� ������
        for (int ch=0; ch<tree->Items->Count; ch++){
                //���� � ������ ���� ����� ����� �������� ��� � ������ ������� ������� - ������� ���!
                if (tree->Items->Item[ch]->Data == NULL){ //�������� ���� - NULL ������
                    //ShowMessage(tree->Items->Item[ch]->Text);
                    if (channelList->IndexOf(tree->Items->Item[ch]->Text) == -1)
                {
                        //���� �������� ����, �� ���������!
                        if (!isErrorNode(tree->Items->Item[ch])){
                                tree->Items->Delete(tree->Items->Item[ch]);
                        }
                }
                }
        }

}


