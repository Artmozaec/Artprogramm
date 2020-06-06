//---------------------------------------------------------------------------


#pragma hdrstop

#include "StringsUtilites.h"
#include "FilmEditorFrm.h"
#include "ArtProgrammFrm.h"
#include "StringEditorFrm.h"
#include "FilmType.cpp"
//#include "FileOperations.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ImageViewer"
#pragma resource "*.dfm"
TFilmEditor *FilmEditor;

//---------------------------------------------------------------------------
__fastcall TFilmEditor::TFilmEditor(TComponent* Owner)
        : TFrame(Owner)
{
        chastityRecovery();

        artDirect = (TArtProgramm *)Owner;
        
        weekDayBox->Items = WeekDay::getDayList();
        //Убираем пустой день недели
        weekDayBox->Items->Delete(0);


        disable();
}
//---------------------------------------------------------------------------

//Отобразить информацию фильма на фрейме
void TFilmEditor::showFilm(Film *inFilm){
        //Вытираем всё, и форму поиска
        clean();

        film = inFilm;

        weekDayBox->Text = film->getWeekDay().getDayString();
        channelBox->Text = film->getChannel();
        actors->Items = film->getActors();
        directors->Items = film->getDirectors();

        //Инициализируем названия
        filmNames->Items = film->getFilmNames();

        //Инициализируем изображения
        imageFileBox->Items = film->getImageNames();
        imageFileBox->Text = film->getBaseImageName();
        showImage(imageFileBox->Text);

        year->Text = film->getYear();

        TimeLabel->Caption = film->getShowTime().getString();

        filmTypeBox->ItemIndex = film->getType();

        textSelection = film->getSelection();


        //Установка активности кнопок
        setEnableRenameImageFileButton();
        setEnableAssignExternalImageButton();

        //Активируем основную форму
        enable();

        //Данные не тронуты
        chastityRecovery();
}

void TFilmEditor::clean(){
        actors->Clear();
        directors->Clear();
        filmNames->Clear();

        year->Clear();

        filmText->Clear();

        imageFileBox->Clear();

        imageViewerFrame->clear();

        TimeLabel->Caption = "00:00";

        disable();

        chastityRecovery();

        //Вытираем форму поиска от предыдущих результатов, удаляя её
        if (fileSearchFrm != NULL){
                delete(fileSearchFrm);
                fileSearchFrm = NULL;
        }

}


void TFilmEditor::enable(){
        active = true;
        saveChangeButton->Enabled = true;
        fileSearchButton->Enabled = true;

        actors->Enabled = true;
        directors->Enabled = true;
        filmNames->Enabled = true;

        year->Enabled = true;

        NamesLabel->Enabled = true;
        ActorsLabel->Enabled = true;
        YearLabel->Enabled = true;
        DirectorsLabel->Enabled = true;

        filmText->Enabled = true;

        dayAndChannelPanel->Enabled = true;
        fileImagesPanel->Enabled = true;

        weekDayBox->Enabled = true;
        channelBox->Enabled = true;
        imageFileBox->Enabled = true;

        TimeLabel->Enabled = true;

}

void TFilmEditor::disable(){
        active = false;
        saveChangeButton->Enabled = false;
        fileSearchButton->Enabled = false;
        renameImageFileButton->Enabled = false;
        assignExternalImageButton->Enabled = false;


        actors->Enabled = false;
        directors->Enabled = false;
        filmNames->Enabled = false;

        year->Enabled = false;

        NamesLabel->Enabled = false;
        ActorsLabel->Enabled = false;
        YearLabel->Enabled = false;
        DirectorsLabel->Enabled = false;

        filmText->Enabled = false;

        dayAndChannelPanel->Enabled = false;
        fileImagesPanel->Enabled = false;

        weekDayBox->Enabled = false;
        channelBox->Enabled = false;
        imageFileBox->Enabled = false;

        TimeLabel->Enabled = false;

}
//////////////////////////////////////////////////////////////////////////////


//Отобразить изображение
void TFilmEditor::showImage(AnsiString name){
        if ((name == NULL) || (name.IsEmpty())) return;

        AnsiString patch = imageManager->getPatch(name);
        imageViewerFrame->showImage(patch);
}


void TFilmEditor::showStringEditor(AnsiString *str){
        //Создаём её
        TStringEditor *stringEditor;

        Application->CreateForm(__classid(TStringEditor), &stringEditor);
        stringEditor->showText(str);
        stringEditor->ShowModal();

        delete(stringEditor);

}

void TFilmEditor::pasteTextToCliboard(AnsiString text){
        TClipboard *clipboard = Clipboard();
        clipboard->Clear();
        clipboard->SetTextBuf(text.c_str());
}


//////////////////////РЕДАКЦИЯ ИЗВНЕ//////////////////////
void TFilmEditor::addFilmName(AnsiString inName){
        if (!active) return;
        trimString(&inName);
        filmNames->Items->Add(inName);

        //Произошли изменения
        chastityDestroy();
        setEnableRenameImageFileButton();

        //Тут-же заносим это имя в буффер обмена, искать на сайтох что-бы
        pasteTextToCliboard(inName);
}


void TFilmEditor::addDirector(AnsiString inDirector){
        if (!active) return;
        trimString(&inDirector);
        directors->Items->Add(inDirector);

        //Произошли изменения
        chastityDestroy();

        setEnableRenameImageFileButton();
}

void TFilmEditor::addActor(AnsiString inActor){
        if (!active) return;
        trimString(&inActor);
        actors->Items->Add(inActor);

        //Произошли изменения
        chastityDestroy();
}

void TFilmEditor::changeYear(AnsiString inYear){
        if (!active) return;
	trimString(&inYear);
        year->Text = inYear;

        //Произошли изменения
        chastityDestroy();

        setEnableRenameImageFileButton();
}

void TFilmEditor::changeWeekDay(AnsiString weekDayString){
        if (!active) return;

	trimString(&weekDayString);

        WeekDay *newDay = new WeekDay(weekDayString.LowerCase());
        weekDayBox->Text = newDay->getDayString();

        //Установка активности выбора внешнего файла!
        setEnableAssignExternalImageButton();

        //Произошли изменения
        chastityDestroy();
}

void TFilmEditor::setShowTime(ShowTime showTime){
        if (!active) return;

        TimeLabel->Caption = showTime.getString();

	//Произошли изменения
	chastityDestroy();
}


void TFilmEditor::setSelection(TextSelection inTextSelection){
      textSelection = inTextSelection;

}

void TFilmEditor::addFilmImage(AnsiString imFilmImage){
        //проверяем нет ли такого имени в списке
        if (imageFileBox->Items->IndexOf(imFilmImage) != -1){
                ShowMessage("Такой файл уже есть!");
                return;
        }

        //Вставить в начало списка
        imageFileBox->Items->Insert(0, imFilmImage);
        imageFileBox->Text = imFilmImage;
        showImage(imFilmImage);

        //Произошли изменения
        chastityDestroy();

        setEnableRenameImageFileButton();
}
//---------------------------------------------------------------------------

bool TFilmEditor::canCloseFilm(){
        //Если изменения были тогда предупреждаем о необходимости их сохранения
     if (!chastity) {
        int answer = MessageDlg("Сохранить изменения ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel,  0);
        if (answer == mrYes){
               saveChanges();
               return true;
        }

        if (answer == mrNo){
               return true;
        }

        if (answer == mrCancel){
               return false;
        }

     }
     return true;
}

void TFilmEditor::chastityRecovery(){
        saveChangeButton->Enabled = false;
        chastity = true;
}

void TFilmEditor::chastityDestroy(){
        saveChangeButton->Enabled = true;
        chastity = false;
}

void __fastcall TFilmEditor::change(TObject *Sender)
{
        chastityDestroy();
}
//---------------------------------------------------------------------------


void TFilmEditor::saveChanges(){
        film->setFilmNames((TStringList *)filmNames->Items);
        film->setDirectors((TStringList *)directors->Items);
        film->setActors((TStringList *)actors->Items);

        TStringList *images = new TStringList();

        images->AddStrings(imageFileBox->Items);
        film->setImageNames(images);
        film->setBaseImageName(imageFileBox->Text);

        film->setChannel(channelBox->Text);


        WeekDay *day = new WeekDay(weekDayBox->Text);
        film->setWeekDay(*day);

        film->setSelection(textSelection);

        film->setShowTime( *new ShowTime(TimeLabel->Caption));

        film->setYear(year->Text);
        film->setFilmType((FilmType)filmTypeBox->ItemIndex);
        //Обновить главное окно
        artDirect->refresh();

        //сохранить сессию
        artDirect->saveSession();
}


//---------------------------------------------------------------------------
////////////////ОБРАБОТЧИКИ ПУНКТОВ КОНТЕКСТНОГО МЕНЮ//////////////////
void __fastcall TFilmEditor::MPasteInBufferClick(TObject *Sender)
{

        //Достаём TPopupMenu в котором содержится PopupComponent
        //который указывает на TListBox в котором был вызов контекстного меню
        //У TListBox есть свойство Name которое указывает на название
        //Пиздец как удобно
        TComponent *menu =  ((TMenuItem *)Sender)->GetParentComponent();

        AnsiString boxName =  ((TPopupMenu *)menu)->PopupComponent->Name;

        if (boxName == filmNames->Name){
                addFilmName(Clipboard()->AsText);
        } else if (boxName == directors->Name){
                addDirector(Clipboard()->AsText);
        } else if (boxName == actors->Name){
                addActor(Clipboard()->AsText);
        }
}


//---------------------------------------------------------------------------

//Пункт меню удалить занчение
void __fastcall TFilmEditor::MDeleteClick(TObject *Sender)
{
        TComponent *menu =  ((TMenuItem *)Sender)->GetParentComponent();

        AnsiString boxName =  ((TPopupMenu *)menu)->PopupComponent->Name;

        if (boxName == filmNames->Name){
                filmNames->Items->Delete(filmNames->ItemIndex);
        } else if (boxName == directors->Name){
                directors->Items->Delete(directors->ItemIndex);
        } else if (boxName == actors->Name){
                actors->Items->Delete(actors->ItemIndex);
        }

        chastityDestroy();
}
//---------------------------------------------------------------------------


//Пункт меню - сделать основным
void __fastcall TFilmEditor::MChangeToBasedClick(TObject *Sender)
{
        TComponent *menu =  ((TMenuItem *)Sender)->GetParentComponent();

        AnsiString boxName =  ((TPopupMenu *)menu)->PopupComponent->Name;

        if (boxName == filmNames->Name){
                AnsiString str = filmNames->Items->Strings[filmNames->ItemIndex];
                filmNames->Items->Delete(filmNames->ItemIndex);
                filmNames->Items->Insert(0, str);
        } else if (boxName == directors->Name){
                AnsiString str = directors->Items->Strings[directors->ItemIndex];
                directors->Items->Delete(directors->ItemIndex);
                directors->Items->Insert(0, str);
        } else if (boxName == actors->Name){

        }

        chastityDestroy();
}

////////////////////////////////////////////////////////////////////////////////




void __fastcall TFilmEditor::channelBoxClick(TObject *Sender)
{
        channelBox->Items = artDirect->getCurrentChannelsList();
}

void __fastcall TFilmEditor::imageFileBoxChange(TObject *Sender)
{
        showImage(imageFileBox->Text);

        //Произошли изменения
        chastityDestroy();
}

void __fastcall TFilmEditor::changeWeekDayBox(TObject *Sender){
        setEnableAssignExternalImageButton();
        change(Sender);

        //Снмаем активность с этого компонента, передаём её форме
        this->SetFocus();
}

//---------------------------------------------------------------------------
///////////////////////ОБРАБОТКА КНОПОК///////////////////////////////////////

void __fastcall TFilmEditor::assignExternalImageButtonClick(
      TObject *Sender)
{
        AnsiString result = artDirect->showFreeFileSelector();
        if (result.IsEmpty()) return;
        addFilmImage(result);
}

void __fastcall TFilmEditor::renameImageFileButtonClick(TObject *Sender)
{
        AnsiString newName = createFileNameString();
        imageManager->renameFile(imageFileBox->Text, newName);
        imageFileBox->Items->Delete(imageFileBox->Items->IndexOf(imageFileBox->Text));
        addFilmImage(newName);

        //И сохраняем всё нафиг
        saveChanges();

        chastityRecovery();
}

void __fastcall TFilmEditor::fileSearchButtonClick(TObject *Sender)
{
        if (fileSearchFrm == NULL){//Если форма поиска ещё не создана
                //Создаём её
                Application->CreateForm(__classid(TFileSearch), &fileSearchFrm);
                fileSearchFrm->changeFilmEditor(this);

                //Передавать нужно сам менеджер! А не какой-то там сраный путь
                fileSearchFrm->changeImageManager(imageManager);

                //Предварительный поиск, при открытии мы увидим результат
                //Если имя заполнено
                if (filmNames->Items->Count>0){
                	fileSearchFrm->introduce(filmNames->Items->Strings[0]);
                }
        }
        fileSearchFrm->setPopUpStrings(createFieldsList());
        fileSearchFrm->ShowModal();
}


void __fastcall TFilmEditor::saveChangeButtonClick(TObject *Sender)
{
        //Проверяем необходимые условия для сохранения
        if (!allDataCorrect()) return;
        chastityRecovery();
        saveChanges();
}

////////////////////////////////////////////////////////////////////////////////


void TFilmEditor::setImageManager(ImageManager *inImageManager){
        imageManager = inImageManager;
}


bool TFilmEditor::allDataCorrect(){
        //День недели
        if (weekDayBox->Text == WeekDay::EMPTY_WEEK_DAY){
                ShowMessage("Некорректный день недели");
                return false;
        }
        return true;
}

bool TFilmEditor::allBasedFieldFill(){
        if ((filmNames->Items->Count > 0) &&
           (imageFileBox->Items->Count > 0) &&
           (directors->Items->Count > 0) &&
           (year->Text.Length() > 3)) return true;
        return false;
}


TStringList *TFilmEditor::createFieldsList(){
        TStringList *list = new TStringList();
        list->AddStrings(filmNames->Items);
        list->AddStrings(directors->Items);
        return list;
}

//Проверка повтора имени в базе изображений и в текущем списке
bool TFilmEditor::nameIsRepeat(AnsiString name){
        //Проверяем уникальность имени, если нет уникальности добавляем индекм
        //Уникальность в базе изображений
        TStringList *storeContent = imageManager->getBaseImageContent();
        if (storeContent->IndexOf(name) != -1) return true;
	if (imageFileBox->Items->IndexOf(name) != -1) return true;
        return false;
}


AnsiString TFilmEditor::createFileNameString(){
        AnsiString fileName = *new AnsiString();

        //Собираем названия
        fileName += filmNames->Items->Strings[0];

        for (int ch=1; ch<filmNames->Items->Count; ch++){
                fileName += " ("+filmNames->Items->Strings[ch]+") ";
        }

        //год
        fileName += " "+year->Text+" ";

        //Собирем режиссёров
        fileName += directors->Items->Strings[0];

        for (int ch=1; ch<directors->Items->Count; ch++){
                fileName += " ("+directors->Items->Strings[ch]+") ";
        }

        fileName = fileName.LowerCase();

        //Убираем неправильные символы
        clearFileSystemServiceSymbol(&fileName);


        //Если фильм встречается в базе изображений или в текущем списке
        if (nameIsRepeat(fileName)){
        	int index = 1;

	        while (nameIsRepeat(fileName + *new AnsiString(" ("+IntToStr(index)+")"))){
        	        index++;
	        }

        	fileName+=*new AnsiString(" ("+IntToStr(index)+")");
        }

        return fileName;
}





void TFilmEditor::setEnableRenameImageFileButton(){
        if (allBasedFieldFill()){
              renameImageFileButton->Enabled = true;
        } else {
              renameImageFileButton->Enabled = false;
        }
}

void TFilmEditor::setEnableAssignExternalImageButton(){
        //Если текущий изменённый день не пустой, тогда кнопка выбора активная
        if (weekDayBox->Text != WeekDay::EMPTY_WEEK_DAY){
                assignExternalImageButton->Enabled = true;
        } else {
                assignExternalImageButton->Enabled = false;
        }
}
void __fastcall TFilmEditor::fieldDblClick(TObject *Sender)
{
        AnsiString *str = new AnsiString (((TListBox *)Sender)->Items->Strings[((TListBox *)Sender)->ItemIndex]);
        showStringEditor(str);
        ((TListBox *)Sender)->Items->Strings[((TListBox *)Sender)->ItemIndex] = *str;
}
//---------------------------------------------------------------------------

void __fastcall TFilmEditor::ListPopUpMenuCreator(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
        //Если выбран какой-то элемент
        if (((TListBox *)Sender)->ItemIndex != -1){
                //Удалить и Основной - активные
                listEditPopup->Items->Items[0]->Enabled = true;
                listEditPopup->Items->Items[1]->Enabled = true;
        } else {
                listEditPopup->Items->Items[0]->Enabled = false;
                listEditPopup->Items->Items[1]->Enabled = false;
        }

        //Меню вставить активно в зависимости от того что содержится в буфере
        if(Clipboard()->HasFormat(CF_TEXT)){
                listEditPopup->Items->Items[2]->Enabled = true;
        } else {
                listEditPopup->Items->Items[2]->Enabled = false;
        }

}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TFilmEditor::listHint(TObject *Sender, TShiftState Shift,
      int X, int Y)
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



void __fastcall TFilmEditor::KeyDownListBox(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        AnsiString className = ((TListBox *)Sender)->Name;
        if (Key==VK_DELETE){
                if (className == filmNames->Name){
                        filmNames->Items->Delete(filmNames->ItemIndex);
                        chastityDestroy();
                } else if (className == directors->Name){
                        directors->Items->Delete(directors->ItemIndex);
			chastityDestroy();
                } else if (className == actors->Name){
                        actors->Items->Delete(actors->ItemIndex);
			chastityDestroy();
                }
        }
}


bool TFilmEditor::nameFilmFill(){
        if (filmNames->Count>0) return true;
        return false;
}


bool TFilmEditor::isActive(){
	return active;
}
//---------------------------------------------------------------------------

void __fastcall TFilmEditor::fieldToClboard(TObject *Sender)
{
        AnsiString boxName =  ((TListBox*)Sender)->Name;

        if (boxName == filmNames->Name){
                pasteTextToCliboard(filmNames->Items->Strings[filmNames->ItemIndex]);
        } else if (boxName == directors->Name){
                pasteTextToCliboard(directors->Items->Strings[directors->ItemIndex]);
        } else if (boxName == actors->Name){
                pasteTextToCliboard(actors->Items->Strings[actors->ItemIndex]);
        }
}
//---------------------------------------------------------------------------


