//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StringEditorFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TStringEditor *StringEditor;
//---------------------------------------------------------------------------
__fastcall TStringEditor::TStringEditor(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void TStringEditor::showText(AnsiString *editString){
        originalText = editString;
        editMemo->Text = *editString;
}


void __fastcall TStringEditor::saveButtonClick(TObject *Sender)
{
        *originalText = editMemo->Text;
        this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TStringEditor::editMemoKeyPress(TObject *Sender, char &Key)
{
	if (Key==VK_RETURN) saveButtonClick(Sender);
}
//---------------------------------------------------------------------------

