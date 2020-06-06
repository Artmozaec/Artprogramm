//---------------------------------------------------------------------------

#ifndef StringEditorFrmH
#define StringEditorFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TStringEditor : public TForm
{
__published:	// IDE-managed Components
        TMemo *editMemo;
        TButton *saveButton;
        void __fastcall saveButtonClick(TObject *Sender);
	void __fastcall editMemoKeyPress(TObject *Sender, char &Key);
public:		// User declarations
        __fastcall TStringEditor(TComponent* Owner);
        void showText(AnsiString *editString);

private:	// User declarations
        AnsiString *originalText;


};
//---------------------------------------------------------------------------
extern PACKAGE TStringEditor *StringEditor;
//---------------------------------------------------------------------------
#endif
