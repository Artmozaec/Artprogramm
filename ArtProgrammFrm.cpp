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

	//Создаём обозреватель каналов
	fileAnonsObserver = new FileAnonsObserver(false, this);
        fileAnonsObserver->setAnonsTextPatch(settingsManager->getAnonsTextFolderPatch());

        anonsTree->setChannelsAndNames(channelFilesAndNames);

	//Контейнер фильмов
	anonsTree->setFilmContainer(filmContainer);

	channelTextEditor->changeFilmEditor(filmEditor);

        replaceAnonsTextChecker = new ReplaceAnonsTextChecker(sessionManager);

	//Если восстановление настроек не прошло гладко, вызываем окно редактора настроек
	if (!settingsManager->isOk()) settingsButtonClick(this);
}

void TArtProgramm::newChannelDetected(AnsiString fileName){




        //Проверяем канал на повтор с прошлым текстом
        if (!replaceAnonsTextChecker->checkText(fileAnonsObserver->getChannelText(fileName), fileName)){
        	ShowMessage("!!!!!!!!ПОВТОР ТЕКСТА АНОНСА!!!!!!!!!!");

                //ShellExecute(Handle, "open", "c:\\windows\\notepad.exe", (settingsManager->getAnonsTextFolderPatch() + fileName).c_str(), NULL, SW_SHOWNORMAL);
        } else {
                channelFilesAndNames->addChannelFileName(fileName);
	        anonsTree->refresh();

        	Application->Restore();
	  	Application->RestoreTopMosts();
  		Application->MainForm->Show();

	        ShowMessage("Добавлен канал! >> "+fileName);
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

        ShowMessage("Удалён канал! >> "+fileName);
        //this->SetFocus();
        //this->BringToFront();
        //ShowWindow(this->Handle, SW_RESTORE);
        //BringWindowToTop(this->Handle);
        //SetActiveWindow(this->Handle);
}


void TArtProgramm::showChannelText(AnsiString fileName, TextSelection selection){
        TStringList *text = NULL;

        //Если в редакторе были изменения, текст из редактора нужно сохранить
        if (channelTextEditor->isChanged()){
        	//Старый канал ещё выделен, поэтому имеем возможность эту информацию использовать
                AnsiString oldChannel = anonsTree->getSelectedChannel();
                AnsiString oldFile = channelFilesAndNames->getFileName(oldChannel);
		sessionManager->saveChannelText(oldFile, channelTextEditor->getText());
        }

        text = sessionManager->getChannelText(fileName);
        if (text == NULL){
		text = fileAnonsObserver->getChannelText(fileName);
	        if (text == NULL){
        		ShowMessage("Удивительно! Но запрашиваемого файла нет... >>"+fileName);
                        return;
	        }else{
                	//Сохраняем этот текст в менеджер сессии
			sessionManager->saveChannelText(fileName, new AnsiString(text->GetText()));
                }
        }

	channelTextEditor->showText(text, selection);
}

bool TArtProgramm::showFilm(Film *film){
        //Запрашиваем сохранение внесённых изменений в редактируемый фильм
        //Выходим если не разрешено
        if (!filmEditor->canCloseFilm()) return false;

        filmEditor->showFilm(film);
        showChannelText(channelFilesAndNames->getFileName(film->getChannel()), film->getSelection());
        return true;
}

bool TArtProgramm::showTextChannel(AnsiString channelName){
        //Запрашиваем сохранение внесённых изменений в редактируемый фильм
        //Выходим если не разрешено
        if (!filmEditor->canCloseFilm()) return false;

        AnsiString fileName = channelFilesAndNames->getFileName(channelName);
        if (fileName == NULL){
                ShowMessage("НЕЕЕТ ТАКОГО ФАЙЛА!!!!" + channelName);
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
                -1,//День недели не определён, что-бы обезопасить локацию!
                channelName
        );

        return newFilm;
}

//Сохраняет всё дерево
void TArtProgramm::saveSession(){
	//Сохраняем всё дерево сессии
	sessionManager->saveCurrentSession(filmContainer);
}

//создаёт, добавляет в контейнер и отображает новый фильм
void TArtProgramm::addNewFilm(){
        //Сообщаем о необходимости закрытия фильма
        //Выходим если не разрешено
        if (!filmEditor->canCloseFilm()) return;

        //Создаём новый фильм
        Film *newFilm = newFilmCreator();

        //Добавляем фильм в контейнер
        filmContainer->addFilm(newFilm);

        //Отображаем фильм в редакторе
        filmEditor->showFilm(newFilm);

        //Обновляем дерево
        anonsTree->refresh();

        //Устанавливаем в дереве выделение на только что созданном фильме
        anonsTree->selectFilmInTree(newFilm);
}




//---------------------------------------------------------------------------
void __fastcall TArtProgramm::ANewFilmExecute(TObject *Sender)
{
        addNewFilm();
}
//---------------------------------------------------------------------------

//Очищает канал от сохранённых фильмов
void TArtProgramm::clearSelectedChannel(){
	if (MessageDlg("УДАЛИТЬ СОДЕРЖИМОЕ КАНАЛА ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel,  0) == mrNo) return;

	AnsiString channelName = anonsTree->getSelectedChannel();

        FilmIterator *channelIterator = filmContainer->getIteratorOfChannel(channelName);

	Film *film;
	while(channelIterator->nextFilm()){
		film = channelIterator->getFilm();

                //Удаляем фильм из контейнера
                filmContainer->deleteFilm(film);
        }

        anonsTree->refresh();
        refresh();
}


//Удаляет выбранный в дереве фильм
void TArtProgramm::deleteSelectedFilm(){
        Film *selectedFilm = anonsTree->getSelectedFilm();

        if (selectedFilm == NULL) return;

        filmContainer->deleteFilm(selectedFilm);
        anonsTree->refresh();
        refresh();
}



void __fastcall TArtProgramm::ADeleteExecute(TObject *Sender)
{
        //Если выделен фильм
        if (anonsTree->whatIsSelected() == SELECTED_FILM){
                deleteSelectedFilm();
        } else if (anonsTree->whatIsSelected() == SELECTED_CHANNEL){
	        clearSelectedChannel();
        }
		
		//Сохраняем сессию
		saveSession();
}
//---------------------------------------------------------------------------



AnsiString TArtProgramm::showFreeFileSelector(){
        //Получаем список файлов дня Day
        TStringList *dayList = imageManager->getWorkFolderContent();

        //Очищаем этот список от тех файлов которые уже связанны с фильмами
        for (int ch=0; ch<dayList->Count; ch++){
                //Если найден фильм содержащий текущую строку с именем файла
                if (getFilmToImageFile(dayList->Strings[ch], filmContainer) != NULL){
                        //Удаляем ее из списка файлов
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
        if (MessageDlg("Начать новую сессию?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel,  0) == mrYes){
		imageManager->clearOutFolders();
		sessionManager->createNewSession();

		//Очищаем контейнер
		filmContainer->clear();

		refresh();
        }
}
//---------------------------------------------------------------------------

void __fastcall TArtProgramm::ASplitFilmsInCurrentChannelExecute(
      TObject *Sender)
{
	//ShowMessage("Разбить канал");

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

//Остановка слежения за папкой анонсов
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
	//ShowMessage("Настройки");
        TSettingsEditor *settingsEditor;
	Application->CreateForm(__classid(TSettingsEditor), &settingsEditor);
        settingsEditor->setSettingsManager(settingsManager);
	settingsEditor->ShowModal();


        //Меняем настройки
        sessionManager->setSessionStoryPatch(settingsManager->getSessionFolderPatch());
	imageManager->setImageStoragePatch(settingsManager->getBaseImageFolderPatch());
	imageManager->setShareFolderPatch(settingsManager->getShareFolderPatch());
	imageManager->setWorkDirectoryPatch(settingsManager->getWorkFolderPatch());
        fileAnonsObserver->setAnonsTextPatch(settingsManager->getAnonsTextFolderPatch());
}
//---------------------------------------------------------------------------

