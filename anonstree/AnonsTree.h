//---------------------------------------------------------------------------


#ifndef AnonsTreeH
#define AnonsTreeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//#include "FileAnonsObserver.h"
#include <vcl.h>
#include "FilmContainer.h"
#include "ChannelFilesAndNames.h"
#include "WeekDay.h"
#include "ChannelTreeUpdater.h"
#include "WeekDayTreeUpdater.h"

#include "AnonsTreeMode.cpp"
#include "SelectedInTree.cpp"

#include "AbstractTreeUpdater.h"
#include <ImgList.hpp>

//#include "TestAnonsTree.h"
//#include "ChannelIterator.h"
//---------------------------------------------------------------------------
class TArtProgramm;
class FileAnonsObserver;
class TAnonsTree : public TFrame
{
__published:	// IDE-managed Components
        TTreeView *anonsesTree;
        TRadioGroup *viewModeGroup;
	TImageList *ImageList1;
        void __fastcall viewModeGroupClick(TObject *Sender);
        void __fastcall anonsesTreeAdvancedCustomDrawItem(
          TCustomTreeView *Sender, TTreeNode *Node, TCustomDrawState State,
          TCustomDrawStage Stage, bool &PaintImages, bool &DefaultDraw);
        void __fastcall anonsesTreeChanging(TObject *Sender,
          TTreeNode *Node, bool &AllowChange);

public:		// User declarations
        __fastcall TAnonsTree(TComponent* Owner);


        void setChannelsAndNames(ChannelFilesAndNames *inChannelFilesAndNames);
        void setFilmContainer(FilmContainer *inFilmContainer);

        //Отыскивает select в tree и выделяет его
        void selectFilmInTree(Film *select);

        //Перестройка дерева анонсов
        void refresh();

        AnsiString getSelectedChannel();
        Film *getSelectedFilm();
        WeekDay getSelectedWeekDay();

        //Что выделенно в данный момент в дереве
        SelectedInTree whatIsSelected();

private:	// User declarations

        AbstractTreeUpdater *createCurrentUpdater();

        FilmContainer *filmContainer;
        ChannelFilesAndNames *channelFilesAndNames;

        AbstractTreeUpdater *currentUpdater;

        //Управляющий класс
        TArtProgramm *artDirect;

        void updateIcon();
		//////////////РАБОТА С ЦВЕТОМ//////////////////
		
		TColor getColorFromWeekDay(Film *film);
		TColor getColorFromChannel(Film *film);
		
};
//---------------------------------------------------------------------------
extern PACKAGE TAnonsTree *AnonsTree;
//---------------------------------------------------------------------------
#endif
