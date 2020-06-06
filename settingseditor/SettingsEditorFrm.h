//---------------------------------------------------------------------------

#ifndef SettingsEditorFrmH
#define SettingsEditorFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SettingsManager.h"

//---------------------------------------------------------------------------
class TSettingsEditor : public TForm
{
__published:	// IDE-managed Components
	TEdit *workFolderPatchEdit;
	TEdit *baseImagePatchEdit;
	TEdit *anonsTextPatchEdit;
	TEdit *shareFolderPatchEdit;
	TEdit *sessionFolderPatchEdit;

	TLabel *workFolderPatchLabel;
	TLabel *baseImagePatchLabel;
	TLabel *anonsTextPatchLabel;
	TLabel *shareFolderPatchLabel;
	TLabel *sessionBasePatchLabel;
	TButton *saveButton;
	TButton *workFolderPatchButton;
	TButton *baseImagePatchButton;
	TButton *anonsTextPatchButton;
	TButton *shareFolderPatchButton;
	TButton *sessionFolderPatchButton;
	void __fastcall workFolderPatchButtonClick(TObject *Sender);
	void __fastcall baseImagePatchButtonClick(TObject *Sender);
	void __fastcall anonsTextPatchButtonClick(TObject *Sender);
	void __fastcall shareFolderPatchButtonClick(TObject *Sender);
	void __fastcall sessionFolderPatchButtonClick(TObject *Sender);
	void __fastcall saveButtonClick(TObject *Sender);
public:		// User declarations
	__fastcall TSettingsEditor(TComponent* Owner);
	void setSettingsManager(SettingsManager *inSettingsManager);
	
private:	// User declarations
	SettingsManager *settingsManager;
	void saveSettings();

        AnsiString showFolderSelector(AnsiString captionText);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingsEditor *SettingsEditor;
//---------------------------------------------------------------------------
#endif
