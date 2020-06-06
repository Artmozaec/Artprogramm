//---------------------------------------------------------------------------


#pragma hdrstop


#include "AnonsTree.h"
#include "FilmType.cpp"
#include "TreeColors.cpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "FileAnonsObserver.h"
#include "AnonsTreeMode.cpp"
#include "ArtProgrammFrm.h"


TAnonsTree *AnonsTree;
//---------------------------------------------------------------------------
__fastcall TAnonsTree::TAnonsTree(TComponent* Owner)
        : TFrame(Owner)
{
        artDirect = (TArtProgramm *)Owner;
}


AbstractTreeUpdater *TAnonsTree::createCurrentUpdater(){
   if (viewModeGroup->ItemIndex == CHANNEL){
        return (AbstractTreeUpdater *)new ChannelTreeUpdater(filmContainer, channelFilesAndNames);
   }
   if (viewModeGroup->ItemIndex == WEEK_DAY){
        return (AbstractTreeUpdater *)new WeekDayTreeUpdater(filmContainer);
   }
}


void TAnonsTree::refresh(){
        if (currentUpdater == NULL){
                currentUpdater = createCurrentUpdater();
        }
        currentUpdater->updateTree(anonsesTree);
        updateIcon();
        anonsesTree->Repaint();
}

void TAnonsTree::updateIcon(){
	for(int ch=0; ch<anonsesTree->Items->Count; ch++){

        	if(anonsesTree->Items->Item[ch]->Data == NULL){
			anonsesTree->Items->Item[ch]->ImageIndex = 1;
                        anonsesTree->Items->Item[ch]->SelectedIndex = 1;
		} else {
                        if(((Film *)anonsesTree->Items->Item[ch]->Data)->getType() == SERIAL){
                        	anonsesTree->Items->Item[ch]->ImageIndex = 2;
                                anonsesTree->Items->Item[ch]->SelectedIndex = 2;
                	} else if(((Film *)anonsesTree->Items->Item[ch]->Data)->getType() == MULITIPLICATION){
                        	anonsesTree->Items->Item[ch]->ImageIndex = 3;
                                anonsesTree->Items->Item[ch]->SelectedIndex = 3;
			} else if(((Film *)anonsesTree->Items->Item[ch]->Data)->getType() == SINCE){
                        	anonsesTree->Items->Item[ch]->ImageIndex = 4;
                                anonsesTree->Items->Item[ch]->SelectedIndex = 4;
                        } else if(((Film *)anonsesTree->Items->Item[ch]->Data)->imageExist()){
	                        anonsesTree->Items->Item[ch]->ImageIndex = 0;
                                anonsesTree->Items->Item[ch]->SelectedIndex = 0;
                        } else {
	                        anonsesTree->Items->Item[ch]->ImageIndex = 1;
                                anonsesTree->Items->Item[ch]->SelectedIndex = 1;
                        }
                }
        }
}

void TAnonsTree::setChannelsAndNames(ChannelFilesAndNames *inChannelFilesAndNames){
        channelFilesAndNames = inChannelFilesAndNames;
}

AnsiString TAnonsTree::getSelectedChannel(){
        //Если ничего не выбранно возвращаем пустой AnsiString
        if (anonsesTree->Selected == NULL) return *new AnsiString();


        //Если выбран корневой узел
        if (anonsesTree->Selected->Data == NULL){
                return anonsesTree->Selected->Text;
        } else {
                return ((Film *)anonsesTree->Selected->Data)->getChannel();
        }
}


WeekDay TAnonsTree::getSelectedWeekDay(){
        //Если ничего не выбранно возвращаем "не день недели"
        if (anonsesTree->Selected == NULL) return *new WeekDay(0);

        //Если выбран фильм
        if (anonsesTree->Selected->Data != NULL){
                return ((Film *)anonsesTree->Selected->Data)->getWeekDay();
        }

        //Если режим дня недели, мы прошли пердыдущую ветвь, значит мы в корне,
        //значит можно использовать текст дня недели
        if (viewModeGroup->ItemIndex == WEEK_DAY){
                return *new WeekDay(anonsesTree->Selected->Text);
        }

        return *new WeekDay(0);
}


void TAnonsTree::setFilmContainer(FilmContainer *inFilmContainer){
        filmContainer = inFilmContainer;
}




//---------------------------------------------------------------------------
//-------------------------------------------------------------------------




Film * TAnonsTree::getSelectedFilm(){
        return (Film *)anonsesTree->Selected->Data;
}


void TAnonsTree::selectFilmInTree(Film *select){
        anonsesTree->OnChanging = NULL;
        currentUpdater->selectFilmInTree(anonsesTree, select);
        anonsesTree->OnChanging = anonsesTreeChanging;
}

//---------------------------------------------------------------------------

void __fastcall TAnonsTree::viewModeGroupClick(TObject *Sender)
{
      Film *selectFilm;
      if (anonsesTree->Selected != NULL){
                selectFilm = (Film *)anonsesTree->Selected->Data;
      }

      //Выключаем обработчик событий дерева, что бы он не вызывал события при Clear()
      anonsesTree->OnChanging = NULL;
      anonsesTree->Items->Clear();

      delete currentUpdater;
      currentUpdater = NULL;

      refresh();

      //Включаем обработчик назад, о-ооо спасибо http://delphimaster.net/ - это гениально!
      anonsesTree->OnChanging = anonsesTreeChanging;

      if (selectFilm != NULL){
                selectFilmInTree(selectFilm);
      }

}
//---------------------------------------------------------------------------



TColor TAnonsTree::getColorFromWeekDay(Film *film){
	if (film == NULL) return clBlack;
	WeekDay weekDay = film->getWeekDay();
	switch(weekDay.getDayInt()){
		case 1: return (TColor)TREE_RED;
		case 2: return (TColor)TREE_ORANGE;
		case 3: return (TColor)TREE_YELLOW;
		case 4: return (TColor)TREE_GREEN;
		case 5: return (TColor)TREE_BLUE;
		case 6: return (TColor)TREE_CYAN;
		case 7: return (TColor)TREE_PURPLE;

	}
        return clBlack;
}


TColor TAnonsTree::getColorFromChannel(Film *film){
	return clBlack;
}

void __fastcall TAnonsTree::anonsesTreeAdvancedCustomDrawItem(
      TCustomTreeView *Sender, TTreeNode *Node, TCustomDrawState State,
      TCustomDrawStage Stage, bool &PaintImages, bool &DefaultDraw)
{
        //Если узел выделен, надпись находится на фиолетовом фоне, и его нифига не видно
        if (anonsesTree->Selected == Node){
		Sender->Canvas->Font->Color = clWhite;
                return;
        }
        if (currentUpdater->isErrorNode(Node)){
                Sender->Canvas->Font->Color = clRed;
        } else {
				//Если режим дней недели
				if (viewModeGroup->ItemIndex == WEEK_DAY){
					Sender->Canvas->Font->Color = getColorFromChannel((Film *)Node->Data);
				} else {//режим каналов
					Sender->Canvas->Font->Color = getColorFromWeekDay((Film *)Node->Data);
				}
		}
}
//---------------------------------------------------------------------------
void __fastcall TAnonsTree::anonsesTreeChanging(TObject *Sender,
      TTreeNode *Node, bool &AllowChange)
{
        //Иногда бывает и тааак
        if (Node == NULL){
                AllowChange = false;
                return;
        }

        /*
        //Не даёт выделить ошибочную ветвь
        if (currentUpdater->isErrorNode(Node)){
                AllowChange = false;
                return;
        }
        */

        //В режиме дня недели не позволяем выделять корневые узлы
        if ((viewModeGroup->ItemIndex == WEEK_DAY) && (Node->Data == NULL)){
                AllowChange = false;
                return;
        }

        if (Node->Data == NULL){
                if (!artDirect->showTextChannel(Node->Text)){
                        //Если был отказ, запрещаем перенос выделения
                        AllowChange = false;
                }
        } else {
                if (!artDirect->showFilm((Film *)Node->Data)){
                        //Если был отказ, запрещаем перенос выделения
                        AllowChange = false;
                }
        }
        


}


SelectedInTree TAnonsTree::whatIsSelected(){
         //Ничего не выбранно
	 if (anonsesTree->Selected == NULL) return SELECTED_NONE;

         //Если имеется связанный объект, значит - это фильм
         if (anonsesTree->Selected->Data != NULL) return SELECTED_FILM;

         //Если мы прошли предыдущую ветку, значит выделены либо каналы либо дни недели
         //Это лего узнать по текущему режиму
         if (viewModeGroup->ItemIndex == WEEK_DAY) return SELECTED_WEEK_DAY;
         if (viewModeGroup->ItemIndex == CHANNEL) return SELECTED_CHANNEL;

         return SELECTED_NONE;
}
