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
        //Обновляем корневые узлы
        updateChannelNodes(tree);

        //Обновляем листья - фильмы
        updateFilmNodes(tree);

        //Удаляем пустые ошибочные ветви
        deleteEmptyErrorRoots(tree);
}





void ChannelTreeUpdater::addFilmsToTree(TTreeView *tree, FilmContainer *addFilms){
        FilmIterator *filmIterator = addFilms->getIterator();
        TTreeNode *channelNode;
        while(filmIterator->nextFilm()){
                AnsiString channelName = filmIterator->getFilm()->getChannel();
                AnsiString filmName = filmIterator->getFilm()->getBaseFilmName();
                channelNode = searchRootNode(tree, channelName);
                //Если канал отсутствует
                if (channelNode == NULL){
                        //Создаём канал-ошибку
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
                if (tree->Items->Item[ch]->Data!=NULL){//Не корневой узел
                        //Получаем родительский узел канала
                        TTreeNode *rootNode = tree->Items->Item[ch]->Parent;
                        Film *film = (Film *)tree->Items->Item[ch]->Data;

                        //Если канал фильма не совпадает с текстом родительского узла
                        if (rootNode->Text != film->getChannel()) resultContainer->addFilm(film);
                }
        }
        return resultContainer;
}

void ChannelTreeUpdater::updateFilmNodes(TTreeView *tree){
        FilmContainer *channelChangedFilms = getChangeChannelFilms(tree);

        FilmContainer *deletedFilms = searchDeletedFilms(tree, filmContainer);
        Film *selectFilm;

        //Если будет пересещение филма из канала в канал, то выделение на переносимом фильме исчезнет
        //По этому, сохраняем его заранее, а потом вернем выделение
        if (tree->Selected != NULL) selectFilm = (Film *)tree->Selected->Data;

        //Фильмы в которых поменяли канал с начала удаляются
        deletedFilms->addFilmContainer(channelChangedFilms);
        deleteFilmsToTree(tree, deletedFilms);

        FilmContainer *addedFilms = searchAddFilms(tree, filmContainer);
        addFilmsToTree(tree, addedFilms);

        selectFilmInTree(tree, selectFilm);
        //Обновить названия фильмов
        filmNodeNamesUpdate(tree);
}


bool ChannelTreeUpdater::channelNameInTreeExist(TTreeView *tree, AnsiString channelName){
        for(int ch=0; ch<tree->Items->Count; ch++){

                if((tree->Items->Item[ch]->Data == NULL) && //Проверка на корневоcть узла - канал
                   (tree->Items->Item[ch]->Text == channelName)){
                        return true;
                }
        }
        return false;
}

void ChannelTreeUpdater::updateChannelNodes(TTreeView *tree){
        //Получаем текущий список каналов
        TStringList *channelList = channelFilesAndNames->getChannelList();
        //Ищем добавленные файлы анонсов
        for (int ch=0; ch<channelList->Count; ch++){
                //Если название канала нет в дереве, значит добавляем его
                if (!channelNameInTreeExist(tree, channelList->Strings[ch])){
                      tree->Items->Add(NULL, channelList->Strings[ch]);
                }
        }

        //Ищем удалённые каналы
        for (int ch=0; ch<tree->Items->Count; ch++){
                //Если в дереве есть такой канал которого нет в списке текущих каналов - УДОЛИТЬ НАХ!
                if (tree->Items->Item[ch]->Data == NULL){ //Корневой узел - NULL объект
                    //ShowMessage(tree->Items->Item[ch]->Text);
                    if (channelList->IndexOf(tree->Items->Item[ch]->Text) == -1)
                {
                        //Если корневой узел, не ошибочный!
                        if (!isErrorNode(tree->Items->Item[ch])){
                                tree->Items->Delete(tree->Items->Item[ch]);
                        }
                }
                }
        }

}


