//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ImageSelectorFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ImageViewer"
#pragma resource "*.dfm"
TImageSelector *ImageSelector;
//---------------------------------------------------------------------------
__fastcall TImageSelector::TImageSelector(TComponent* Owner)
        : TForm(Owner)
{
        selectResult = NULL;
}
//---------------------------------------------------------------------------

void TImageSelector::showList(TStringList *imagesList){
        imageFilesBox->Items = imagesList;
}


void TImageSelector::setImageManager(ImageManager *inImageManager){
        imageManager = inImageManager;
}


void __fastcall TImageSelector::imageFilesBoxClick(TObject *Sender)
{
        //Отображаем картинку preview
        AnsiString patch = imageManager->getPatch(imageFilesBox->Items->Strings[imageFilesBox->ItemIndex]);
        imageViewerFrame->showImage(patch);
}
//---------------------------------------------------------------------------


AnsiString TImageSelector::getSelectResult(){
        if (selectResult == NULL) return *new AnsiString();
        return *selectResult;
}

void __fastcall TImageSelector::imageFilesBoxDblClick(TObject *Sender)
{
        selectResult = new AnsiString(imageFilesBox->Items->Strings[imageFilesBox->ItemIndex]);
        this->Close();        
}
//---------------------------------------------------------------------------

