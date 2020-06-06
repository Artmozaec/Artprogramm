//---------------------------------------------------------------------------

#ifndef ImageSelectorFrmH
#define ImageSelectorFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ImageViewer.h"
#include "ImageManager.h"
#include "FilmContainer.h"

//---------------------------------------------------------------------------
class TImageSelector : public TForm
{
__published:	// IDE-managed Components
        TListBox *imageFilesBox;
        TImageViewerFrame *imageViewerFrame;
        void __fastcall imageFilesBoxClick(TObject *Sender);
        void __fastcall imageFilesBoxDblClick(TObject *Sender);

public:		// User declarations
        __fastcall TImageSelector(TComponent* Owner);

        void setImageManager(ImageManager *inImageManager);
        void showList(TStringList *imagesList);

        //Возврат выбранного результата
        AnsiString getSelectResult();

private:	// User declarations
        ImageManager *imageManager;

        AnsiString *selectResult;
};
//---------------------------------------------------------------------------
extern PACKAGE TImageSelector *ImageSelector;
//---------------------------------------------------------------------------
#endif
