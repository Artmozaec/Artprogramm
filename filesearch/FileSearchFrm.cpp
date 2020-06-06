//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FileSearchFrm.h"
#include "FilesSearcher.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ImageViewer"
#pragma resource "*.dfm"
TFileSearch *FileSearch;
//---------------------------------------------------------------------------
void TFileSearch::changeFilmEditor(TFilmEditor *inFilmEditor){
        filmEditor = inFilmEditor;
}

void TFileSearch::changeImageManager(ImageManager *inImageManager){
        imageManager = inImageManager;
}

__fastcall TFileSearch::TFileSearch(TComponent* Owner)
        : TForm(Owner)
{
        backResultButton->Enabled = false;
        pervisionResult = new TStringList();
}

//---------------------------------------------------------------------------




void __fastcall TFileSearch::resultListBoxClick(TObject *Sender)
{
        
        imageViewerFrame->showImage(imageManager->getPatch(resultListBox->Items->Strings[resultListBox->ItemIndex]));
}
//---------------------------------------------------------------------------



void __fastcall TFileSearch::assignButtonClick(TObject *Sender)
{
        filmEditor->addFilmImage(resultListBox->Items->Strings[resultListBox->ItemIndex]);
        this->Close();
}
//---------------------------------------------------------------------------


void __fastcall TFileSearch::FormShow(TObject *Sender)
{
        //assignButton->Enabled = false;
}
//---------------------------------------------------------------------------


void TFileSearch::setPopUpStrings(TStringList *popUpList){
        pastePopUp->Items->Clear();
        for (int ch=0; ch<popUpList->Count; ch++){
                TMenuItem *item = new TMenuItem(this);

                item->Caption = popUpList->Strings[ch];
                item->OnClick = myPopUpItemClick;
                pastePopUp->Items->Add(item);
        }
}

void __fastcall TFileSearch::myPopUpItemClick(TObject *Sender){
        queryTextField->Text = ((TMenuItem *)Sender)->Caption;
}


void __fastcall TFileSearch::resultListBoxMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        static int oldIndex = -1;

        //Получаем элемент списка над которым находится курсор
        int index = ((TListBox *)Sender)->ItemAtPos(Point(X, Y), true);

        //Курсор над новым элементом
        if((index > -1) && (index != oldIndex)){
                ((TListBox *)Sender)->Hint = ((TListBox *)Sender)->Items->Strings[index];
                Application->ActivateHint(Mouse->CursorPos);
        } else {
                ((TListBox *)Sender)->Hint = "";
        }
        oldIndex = index;
}
//---------------------------------------------------------------------------

void __fastcall TFileSearch::queryTextFieldKeyPress(TObject *Sender,
      char &Key)
{
        if (Key==VK_RETURN) searchButtonClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFileSearch::resultListBoxDblClick(TObject *Sender)
{
        filmEditor->addFilmImage(resultListBox->Items->Strings[resultListBox->ItemIndex]);
        this->Close();
}
//---------------------------------------------------------------------------


void __fastcall TFileSearch::backResultButtonClick(TObject *Sender)
{
        //Возвращаем предыдущий результат
        resultListBox->Items = pervisionResult;
        backResultButton->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFileSearch::searchButtonClick(TObject *Sender)
{
        //Сохраняем предыдущий результат
        pervisionResult->Clear();
        pervisionResult->AddStrings(resultListBox->Items);
        backResultButton->Enabled = true;

        FilesSearcher *fs = new FilesSearcher(imageManager->getBaseImageContent());
        resultListBox->Items = (TStrings *) fs->Search(queryTextField->Text.LowerCase());

}
//---------------------------------------------------------------------------


void __fastcall TFileSearch::searchInResultButtonClick(TObject *Sender)
{
        //Сохраняем предыдущий результат
        pervisionResult->Clear();
        pervisionResult->AddStrings(resultListBox->Items);
        backResultButton->Enabled = true;

        FilesSearcher *fs = new FilesSearcher((TStringList *)resultListBox->Items);
        resultListBox->Items = (TStrings *) fs->Search(queryTextField->Text.LowerCase());
}


void TFileSearch::introduce(AnsiString searchString){
	if (searchString == NULL) return;
        queryTextField->Text = searchString;
        //searchButtonClick(searchButton);
}
//---------------------------------------------------------------------------

