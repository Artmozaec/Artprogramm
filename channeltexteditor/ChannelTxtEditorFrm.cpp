//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ChannelTxtEditorFrm.h"
#include "TextSelection.cpp"
#include "ArtProgrammFrm.h"
#include "YearCategory.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChannelText *ChannelText;
//---------------------------------------------------------------------------
__fastcall TChannelText::TChannelText(TComponent* Owner)
        : TFrame(Owner)
{
        artDirect = (TArtProgramm *)Owner;
        weekTextMap = NULL;
        filmsMap = NULL;
}


void TChannelText::destroyMaps(){
        //Очищаем карту дня недели
        if (weekTextMap != NULL){
		delete(weekTextMap);
		weekTextMap = NULL;
        }

        //Очищаем карту фильмов
        if (filmsMap != NULL){
		delete(filmsMap);
		filmsMap = NULL;
        }

        //Очищаем метки
        currentDayLabel->Caption = "";
        currentTimeLabel->Caption = "";

}

void TChannelText::showText(TStringList *textList, TextSelection selection){
	destroyMaps();

        //Пока текст помещается в channelTextEditor срабатывает onChange!
        //На время убирвем обработчик
        channelTextEditor->OnChange = NULL;

        	channelTextEditor->Lines = textList;
        	setSelection(selection);

        //Восстанавливаем обработчик OnChange
        channelTextEditor->OnChange = channelTextEditorChange;


        //Узнаём на какой строке случилось выделение
        int CaretPos = SendMessage(channelTextEditor->Handle, EM_LINEFROMCHAR, -1, 0);

        //Если эта строка выходит за границы экрана, то при позиционировании она окажется в самом низу редактора
        //Прокручиваем текст на 15 строк вверх что-бы текст фильма был виден полностью
        if (CaretPos>10) SendMessage(channelTextEditor->Handle, EM_LINESCROLL, 0, 15);
	chastity = true;
}

void TChannelText::setSelection(TextSelection selection){
	channelTextEditor->SelStart = selection.begin;
        channelTextEditor->SelLength = selection.length;
}


//---------------------------------------------------------------------------


void __fastcall TChannelText::MTextToFilmNameClick(TObject *Sender)
{
	if (!filmEditor->isActive()){
		artDirect->addNewFilm();

        //Поля имени заполненны
        } else if (filmEditor->nameFilmFill()){
                //Даём запрос на создание нового фильма
                if (MessageDlg("Новый фильм?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,  0) == mrYes){
                        artDirect->addNewFilm();
                }
        }
        filmEditor->addFilmName(channelTextEditor->SelText);

        TextSelection selection;
        selection.begin = channelTextEditor->SelStart;
        selection.length = channelTextEditor->SelLength;
        filmEditor->setSelection(selection);

        //Формируем день недели
        WeekDay day = weekTextMap->weekDayInPosition(channelTextEditor->SelStart);
        filmEditor->changeWeekDay(day.getDayString());

        //Время показа
        filmEditor->setShowTime(filmsMap->getTimeInPosition(channelTextEditor->SelStart));
}
//---------------------------------------------------------------------------

void __fastcall TChannelText::MToDirectorClick(TObject *Sender)
{
        filmEditor->addDirector(channelTextEditor->SelText);
}
//---------------------------------------------------------------------------

void __fastcall TChannelText::MToYearClick(TObject *Sender)
{
        filmEditor->changeYear(channelTextEditor->SelText);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void TChannelText::createFilmMap(){
	if (filmsMap == NULL){
        	filmsMap = new FilmsMap();

                filmsMap->createMap(new AnsiString(channelTextEditor->Text));
                //Если в процессе произошла ошибка
                if (!filmsMap->isOk()){
			TextSelection selection = filmsMap->getErrorSelectionInText();
			channelTextEditor->SelStart = selection.begin;
                        channelTextEditor->SelLength = selection.length;
                }
        }
}

void TChannelText::createWeekTextMap(){
	if (weekTextMap == NULL){
        	weekTextMap = new WeekTextMap();
                weekTextMap->createMap(new AnsiString(channelTextEditor->Text));
                //Если в процессе произошла ошибка
                if (!weekTextMap->isOk()){
			TextSelection selection = weekTextMap->getErrorSelectionInText();
			channelTextEditor->SelStart = selection.begin;
                        channelTextEditor->SelLength = selection.length;
                }
        }
}

void TChannelText::dayLabelRefresh(){
	WeekDay day = weekTextMap->weekDayInPosition(channelTextEditor->SelStart);
        currentDayLabel->Caption = "ДЕНЬ НЕДЕЛИ :" + day.getDayString();
}


void TChannelText::timeLabelRefresh(){
        ShowTime time = filmsMap->getTimeInPosition(channelTextEditor->SelStart);
        currentTimeLabel->Caption = "ВРЕМЯ : "+ time.getString();
}



//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TChannelText::channelTextEditorKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
	createFilmMap();
	createWeekTextMap();
	dayLabelRefresh();
        timeLabelRefresh();
}
//---------------------------------------------------------------------------

void __fastcall TChannelText::channelTextEditorClick(TObject *Sender)
{
	createFilmMap();
	createWeekTextMap();
	dayLabelRefresh();
        timeLabelRefresh();
}
//---------------------------------------------------------------------------


bool TChannelText::isYearSelected(){
	YearCategory *yearCategory = new YearCategory();
        //длинна выделенного текста должна быть равна 4 символам, если так то ищем категорию
        if ((channelTextEditor->SelText.Length() == 4) && (yearCategory->contentCategory(channelTextEditor->SelText))) return true;
	return false;
}

void __fastcall TChannelText::channelTextEditorContextPopup(
      TObject *Sender, TPoint &MousePos, bool &Handled)
{
        //Если ничего не выделно, меню не активное
        if (channelTextEditor->SelText.Length() == 0){
        	popupMenu->Items->Items[0]->Enabled = false;
		popupMenu->Items->Items[1]->Enabled = false;
		popupMenu->Items->Items[2]->Enabled = false;
                return;
        }
	if (isYearSelected()){
                popupMenu->Items->Items[0]->Enabled = false;
                popupMenu->Items->Items[1]->Enabled = false;
                popupMenu->Items->Items[2]->Enabled = true;
        } else {
        	popupMenu->Items->Items[0]->Enabled = true;
                popupMenu->Items->Items[1]->Enabled = true;
                popupMenu->Items->Items[2]->Enabled = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TChannelText::channelTextEditorChange(TObject *Sender)
{
	chastity = false;
        destroyMaps();
}
//---------------------------------------------------------------------------



void TChannelText::changeFilmEditor(TFilmEditor *inFilmEditor){
        filmEditor = inFilmEditor;
}

//Были-ли изменения
bool TChannelText::isChanged(){
	return !chastity;
}

AnsiString *TChannelText::getText(){
	return new AnsiString(channelTextEditor->Text);
}
