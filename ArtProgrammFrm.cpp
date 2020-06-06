//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ArtProgrammFrm.h"
#include "TextSelection.cpp"
#include "ImageSelectorFrm.h"
#include "SelectedInTree.cpp"
#include "AnonsSplitter.h"
#include "HistoryForm.h"
#include "SettingsEditorFrm.h"
#include "FilmContainerUtilites.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AnonsTree"
#pragma link "ChannelTxtEditorFrm"
#pragma link "FilmEditorFrm"
#pragma link "FilmsInWeekDaysFrm"
#pragma resource "*.dfm"
TArtProgramm *ArtProgramm;

//---------------------------------------------------------------------------
__fastcall TArtProgramm::TArtProgramm(TComponent* Owner)
        : TForm(Owner)
{

	settingsManager = new SettingsManager(ExtractFilePath(Application->ExeName));

	filmContainer = new FilmContainer();

	sessionManager = new SessionManager();
        sessionManager->setSessionStoryPatch(settingsManager->getSessionFolderPatch());
        sessionManager->loadLastSession(filmContainer);


	channelFilesAndNames = new ChannelFilesAndNames();

	imageManager = new ImageManager(filmContainer);
	imageManager->setImageStoragePatch(settingsManager->getBaseImageFolderPatch());
        imageManager->setShareFolderPatch(settingsManager->getShareFolderPatch());
	imageManager->setWorkDirectoryPatch(settingsManager->getWorkFolderPatch());

	filmEditor->setImageManager(imageManager);
	filmsInWeekDaysFrame->setFilmContainer(filmContainer);
	filmsInWeekDaysFrame->refresh();

	//������ ������������ �������
	fileAnonsObserver = new FileAnonsObserver(false, this);
        fileAnonsObserver->setAnonsTextPatch(settingsManager->getAnonsTextFolderPatch());

        anonsTree->setChannelsAndNames(channelFilesAndNames);

	//��������� �������
	anonsTree->setFilmContainer(filmContainer);

	channelTextEditor->changeFilmEditor(filmEditor);

        replaceAnonsTextChecker = new ReplaceAnonsTextChecker(sessionManager);

	//���� �������������� �������� �� ������ ������, �������� ���� ��������� ��������
	if (!settingsManager->isOk()) settingsButtonClick(this);
}

void TArtProgramm::newChannelDetected(AnsiString fileName){




        //��������� ����� �� ������ � ������� �������
        if (!replaceAnonsTextChecker->checkText(fileAnonsObserver->getChannelText(fileName), fileName)){
        	ShowMessage("!!!!!!!!������ ������ ������!!!!!!!!!!");

                //ShellExecute(Handle, "open", "c:\\windows\\notepad.exe", (settingsManager->getAnonsTextFolderPatch() + fileName).c_str(), NULL, SW_SHOWNORMAL);
        } else {
                channelFilesAndNames->addChannelFileName(fileName);
	        anonsTree->refresh();

        	Application->Restore();
	  	Application->RestoreTopMosts();
  		Application->MainForm->Show();

	        ShowMessage("�������� �����! >> "+fileName);
        }

        //this->SetFocus();
        //this->BringToFront();

        //BringWindowToTop(this->Handle);
        //ShowWindow(this->Handle, SW_RESTORE);
        //SetActiveWindow(this->Handle);

}

void TArtProgramm::deleteChannelDetected(AnsiString fileName){

        channelFilesAndNames->deleteChannelFileName(fileName);
        anonsTree->refresh();

        Application->Restore();
  	Application->RestoreTopMosts();
  	Application->MainForm->Show();

        ShowMessage("����� �����! >> "+fileName);
        //this->SetFocus();
        //this->BringToFront();
        //ShowWindow(this->Handle, SW_RESTORE);
        //BringWindowToTop(this->Handle);
        //SetActiveWindow(this->Handle);
}


void TArtProgramm::showChannelText(AnsiString fileName, TextSelection selection){
        TStringList *text = NULL;

        //���� � ��������� ���� ���������, ����� �� ��������� ����� ���������
        if (channelTextEditor->isChanged()){
        	//������ ����� ��� �������, ������� ����� ����������� ��� ���������� ������������
                AnsiString oldChannel = anonsTree->getSelectedChannel();
                AnsiString oldFile = channelFilesAndNames->getFileName(oldChannel);
		sessionManager->saveChannelText(oldFile, channelTextEditor->getText());
        }

        text = sessionManager->getChannelText(fileName);
        if (text == NULL){
		text = fileAnonsObserver->getChannelText(fileName);
	        if (text == NULL){
        		ShowMessage("�����������! �� �������������� ����� ���... >>"+fileName);
                        return;
	        }else{
                	//��������� ���� ����� � �������� ������
			sessionManager->saveChannelText(fileName, new AnsiString(text->GetText()));
                }
        }

	channelTextEditor->showText(text, selection);
}

bool TArtProgramm::showFilm(Film *film){
        //����������� ���������� �������� ��������� � ������������� �����
        //������� ���� �� ���������
        if (!filmEditor->canCloseFilm()) return false;

        filmEditor->showFilm(film);
        showChannelText(channelFilesAndNames->getFileName(film->getChannel()), film->getSelection());
        return true;
}

bool TArtProgramm::showTextChannel(AnsiString channelName){
        //����������� ���������� �������� ��������� � ������������� �����
        //������� ���� �� ���������
        if (!filmEditor->canCloseFilm()) return false;

        AnsiString fileName = channelFilesAndNames->getFileName(channelName);
        if (fileName == NULL){
                ShowMessage("����� ������ �����!!!!" + channelName);
                return false;
        }

        //AnsiString *pth = new AnsiString(fileAnonsObserver->getAnonsTextFolderPatch()+fileName);

        TextSelection selection;
        selection.begin = 0;
        selection.length = 0;
        //channelTextEditor->showFile(*pth, selection);

        showChannelText(fileName, selection);

        filmEditor->clean();
        return true;
}



TStringList *TArtProgramm::getCurrentChannelsList(){
        return channelFilesAndNames->getChannelList();
}

void TArtProgramm::refresh(){
     anonsTree->refresh();
     filmsInWeekDaysFrame->refresh();
}



Film *TArtProgramm::newFilmCreator(){
        AnsiString channelName = anonsTree->getSelectedChannel();

        if (channelName.IsEmpty()){
                 channelName = *new AnsiString(ChannelFilesAndNames::EMPTY_CHANNEL);
        }
        Film *newFilm = new Film(
                -1,//���� ������ �� ��������, ���-�� ����������� �������!
                channelName
        );

        return newFilm;
}

//��������� �� ������
void TArtProgramm::saveSession(){
	//��������� �� ������ ������
	sessionManager->saveCurrentSession(filmContainer);
}

//������, ��������� � ��������� � ���������� ����� �����
void TArtProgramm::addNewFilm(){
        //�������� � ������������� �������� ������
        //������� ���� �� ���������
        if (!filmEditor->canCloseFilm()) return;

        //������ ����� �����
        Film *newFilm = newFilmCreator();

        //��������� ����� � ���������
        filmContainer->addFilm(newFilm);

        //���������� ����� � ���������
        filmEditor->showFilm(newFilm);

        //��������� ������
        anonsTree->refresh();

        //������������� � ������ ��������� �� ������ ��� ��������� ������
        anonsTree->selectFilmInTree(newFilm);
}




//---------------------------------------------------------------------------
void __fastcall TArtProgramm::ANewFilmExecute(TObject *Sender)
{
        addNewFilm();
}
//---------------------------------------------------------------------------

//������� ����� �� ���������� �������
void TArtProgramm::clearSelectedChannel(){
	if (MessageDlg("������� ���������� ������ ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel,  0) == mrNo) return;

	AnsiString channelName = anonsTree->getSelectedChannel();

        FilmIterator *channelIterator = filmContainer->getIteratorOfChannel(channelName);

	Film *film;
	while(channelIterator->nextFilm()){
		film = channelIterator->getFilm();

                //������� ����� �� ����������
                filmContainer->deleteFilm(film);
        }

        anonsTree->refresh();
        refresh();
}


//������� ��������� � ������ �����
void TArtProgramm::deleteSelectedFilm(){
        Film *selectedFilm = anonsTree->getSelectedFilm();

        if (selectedFilm == NULL) return;

        filmContainer->deleteFilm(selectedFilm);
        anonsTree->refresh();
        refresh();
}



void __fastcall TArtProgramm::ADeleteExecute(TObject *Sender)
{
        //���� ������� �����
        if (anonsTree->whatIsSelected() == SELECTED_FILM){
                deleteSelectedFilm();
        } else if (anonsTree->whatIsSelected() == SELECTED_CHANNEL){
	        clearSelectedChannel();
        }
		
		//��������� ������
		saveSession();
}
//---------------------------------------------------------------------------



AnsiString TArtProgramm::showFreeFileSelector(){
        //�������� ������ ������ ��� Day
        TStringList *dayList = imageManager->getWorkFolderContent();

        //������� ���� ������ �� ��� ������ ������� ��� �������� � ��������
        for (int ch=0; ch<dayList->Count; ch++){
                //���� ������ ����� ���������� ������� ������ � ������ �����
                if (getFilmToImageFile(dayList->Strings[ch], filmContainer) != NULL){
                        //������� �� �� ������ ������
                        dayList->Delete(ch);
                        ch--;
                }
        }

        TImageSelector *imageSelector;
        Application->CreateForm(__classid(TImageSelector), &imageSelector);
        imageSelector->setImageManager(imageManager);
        imageSelector->showList(dayList);
        imageSelector->ShowModal();
        AnsiString result = imageSelector->getSelectResult();
        delete(imageSelector);
        return result;
}

//---------------------------------------------------------------------------




void __fastcall TArtProgramm::ACloseSessionExecute(TObject *Sender)
{
        imageManager->terminateSession();
}
//---------------------------------------------------------------------------

void __fastcall TArtProgramm::ANewSessionExecute(TObject *Sender)
{
        if (MessageDlg("������ ����� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel,  0) == mrYes){
		imageManager->clearOutFolders();
		sessionManager->createNewSession();

		//������� ���������
		filmContainer->clear();

		refresh();
        }
}
//---------------------------------------------------------------------------

void __fastcall TArtProgramm::ASplitFilmsInCurrentChannelExecute(
      TObject *Sender)
{
	//ShowMessage("������� �����");

        AnonsSplitter *anonsSplitter = new AnonsSplitter(filmContainer);

        anonsSplitter->splitChannel(channelTextEditor->getText(), anonsTree->getSelectedChannel());

	if (!anonsSplitter->isOk()){
		channelTextEditor->setSelection(anonsSplitter->getErrorSelectionInText());
        }
        refresh();
}
//---------------------------------------------------------------------------

void __fastcall TArtProgramm::refreshButtonClick(TObject *Sender)
{
	fileAnonsObserver->refresh();
}
//---------------------------------------------------------------------------

//��������� �������� �� ������ �������
void TArtProgramm::stopTrackingAnonsFolder(){
	speedButtonTracking->Down = false;
        fileAnonsObserver->stopTracking();
}
//---------------------------------------------------------------------------

void __fastcall TArtProgramm::speedButtonTrackingClick(TObject *Sender)
{
	if (speedButtonTracking->Down){
		fileAnonsObserver->startTracking();
        } else {
		fileAnonsObserver->stopTracking();
        }
}
//---------------------------------------------------------------------------


void __fastcall TArtProgramm::historyButtonClick(TObject *Sender)
{
	THistorySelector *histroySelector;
        Application->CreateForm(__classid(THistorySelector), &histroySelector);
        histroySelector->showSessionsList(sessionManager->getSessionList());
        histroySelector->ShowModal();
        AnsiString selectedSession = histroySelector->getSelectResult();
        if (selectedSession.IsEmpty()) return;

        filmContainer->clear();
	sessionManager->loadSession(selectedSession, filmContainer);

        delete(histroySelector);
        refresh();
}
//---------------------------------------------------------------------------

void __fastcall TArtProgramm::settingsButtonClick(TObject *Sender)
{
	//ShowMessage("���������");
        TSettingsEditor *settingsEditor;
	Application->CreateForm(__classid(TSettingsEditor), &settingsEditor);
        settingsEditor->setSettingsManager(settingsManager);
	settingsEditor->ShowModal();


        //������ ���������
        sessionManager->setSessionStoryPatch(settingsManager->getSessionFolderPatch());
	imageManager->setImageStoragePatch(settingsManager->getBaseImageFolderPatch());
	imageManager->setShareFolderPatch(settingsManager->getShareFolderPatch());
	imageManager->setWorkDirectoryPatch(settingsManager->getWorkFolderPatch());
        fileAnonsObserver->setAnonsTextPatch(settingsManager->getAnonsTextFolderPatch());
}
//---------------------------------------------------------------------------

