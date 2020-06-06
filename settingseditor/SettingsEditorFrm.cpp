//---------------------------------------------------------------------------
#define NO_WIN32_LEAN_AND_MEAN
#include <vcl.h>
#include <shlobj>
#pragma hdrstop

#include "SettingsEditorFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingsEditor *SettingsEditor;
//---------------------------------------------------------------------------
__fastcall TSettingsEditor::TSettingsEditor(TComponent* Owner)
	: TForm(Owner)
{
}


void TSettingsEditor::setSettingsManager(SettingsManager *inSettingsManager){
	settingsManager = inSettingsManager;
	workFolderPatchEdit->Text = settingsManager->getWorkFolderPatch();
	baseImagePatchEdit->Text = settingsManager->getBaseImageFolderPatch();
	anonsTextPatchEdit->Text = settingsManager->getAnonsTextFolderPatch();
	shareFolderPatchEdit->Text = settingsManager->getShareFolderPatch();
	sessionFolderPatchEdit->Text = settingsManager->getSessionFolderPatch();
}


void TSettingsEditor::saveSettings(){
	settingsManager->setWorkFolderPatch(workFolderPatchEdit->Text);
	settingsManager->setBaseImageFolderPatch(baseImagePatchEdit->Text);
	settingsManager->setShareFolderPatch(shareFolderPatchEdit->Text);
	settingsManager->setAnonsTextFolderPatch(anonsTextPatchEdit->Text);
	settingsManager->setSessionFolderPatch(sessionFolderPatchEdit->Text);

	settingsManager->saveSettings();
}

AnsiString TSettingsEditor::showFolderSelector(AnsiString captionText){
	char buf[MAX_PATH];

        BROWSEINFO bi;
        bi.hwndOwner = this->Handle;
        bi.pidlRoot=NULL;
        bi.pszDisplayName=buf;
        bi.lpszTitle=captionText.c_str();
        bi.ulFlags=NULL;
        bi.lpfn=NULL;

        ITEMIDLIST *itls;

        if(( itls = SHBrowseForFolder(&bi)) != NULL){
                SHGetPathFromIDList(itls,buf);
                return *new AnsiString(buf)+"\\";
        }else{
		return *new AnsiString();
        }
}

//---------------------------------------------------------------------------

void __fastcall TSettingsEditor::workFolderPatchButtonClick(
      TObject *Sender)
{
        AnsiString pth = showFolderSelector( *new AnsiString("А ну, быстро выбрал рабочую директорию!"));
	if (!pth.IsEmpty()){
		workFolderPatchEdit->Text = pth;
        }
}
//---------------------------------------------------------------------------

void __fastcall TSettingsEditor::baseImagePatchButtonClick(TObject *Sender)
{
	AnsiString pth = showFolderSelector( *new AnsiString("Ну чё смотришь? Здесь выбирают базу изображений!"));
	if (!pth.IsEmpty()){
		baseImagePatchEdit->Text = pth;
        }
}
//---------------------------------------------------------------------------

void __fastcall TSettingsEditor::anonsTextPatchButtonClick(TObject *Sender)
{
	AnsiString pth = showFolderSelector( *new AnsiString("Можешь здесь выбрать директорию анонсов..."));
	if (!pth.IsEmpty()){
		anonsTextPatchEdit->Text = pth;
        }
}
//---------------------------------------------------------------------------

void __fastcall TSettingsEditor::shareFolderPatchButtonClick(
      TObject *Sender)
{
	AnsiString pth = showFolderSelector(*new AnsiString("А здесь выбирается папка шары, куда скидывается результат работы... Понял?"));
	if (!pth.IsEmpty()){
		shareFolderPatchEdit->Text = pth;
        }
}
//---------------------------------------------------------------------------

void __fastcall TSettingsEditor::sessionFolderPatchButtonClick(
      TObject *Sender)
{
	AnsiString pth = showFolderSelector( *new AnsiString("Хранилище сессий, выбирать можно, здесь"));
	if (!pth.IsEmpty()){
		sessionFolderPatchEdit->Text = pth;
        }
}
//---------------------------------------------------------------------------

void __fastcall TSettingsEditor::saveButtonClick(TObject *Sender)
{
	saveSettings();
}
//---------------------------------------------------------------------------

