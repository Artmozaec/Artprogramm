//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HistoryForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THistorySelector *HistorySelector;
//---------------------------------------------------------------------------
__fastcall THistorySelector::THistorySelector(TComponent* Owner)
	: TForm(Owner)
{
	result = *new AnsiString();
}
//---------------------------------------------------------------------------
void THistorySelector::showSessionsList(TStringList *sessions){
	sessionsBox->Items = sessions;
}


AnsiString THistorySelector::getSelectResult(){
	return result;

}

//---------------------------------------------------------------------------

void __fastcall THistorySelector::sessionsBoxDblClick(TObject *Sender)
{
	 result = sessionsBox->Items->Strings[sessionsBox->ItemIndex];
         this->Close();  
}
//---------------------------------------------------------------------------

