//---------------------------------------------------------------------------

#ifndef HistoryFormH
#define HistoryFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class THistorySelector : public TForm
{
__published:	// IDE-managed Components
	TListBox *sessionsBox;
	void __fastcall sessionsBoxDblClick(TObject *Sender);

public:		// User declarations
	__fastcall THistorySelector(TComponent* Owner);
        void showSessionsList(TStringList *sessions);

        AnsiString getSelectResult();

private:	// User declarations
	AnsiString result;
};
//---------------------------------------------------------------------------
extern PACKAGE THistorySelector *HistorySelector;
//---------------------------------------------------------------------------
#endif
