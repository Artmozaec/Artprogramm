#include <Film.h>


Film::Film(int inWeekDay, AnsiString inChannel){

        filmImages = new TStringList();


	weekDay = new WeekDay(inWeekDay);
	channel = inChannel;

	filmNames = new TStringList();
	directors = new TStringList();
        actors = new TStringList();

        textSelection.begin=0;
        textSelection.length=0;

        showTime = new ShowTime(0, 0);

        filmType = FEATURE;
}


///////////////���� ������///////////////
WeekDay Film::getWeekDay(){
	return *weekDay;
}

void Film::setWeekDay(int newWeekDay){
	weekDay = new WeekDay(newWeekDay);
}

void Film::setWeekDay(WeekDay newWeekDay){
        //weekDay = &newWeekDay;
        weekDay = new WeekDay(newWeekDay.getDayInt());
}


////////////////�����////////////////////
AnsiString Film::getChannel(){
	return channel;
}

void Film::setChannel(AnsiString inChannel){
	channel = inChannel;
}

///////////////��������� ������//////////
TStringList *Film::getFilmNames(){
        return filmNames;
}


void Film::setFilmNames(TStringList *inNames){
        //�������� inNames
        if (inNames == NULL) return;

        filmNames->Clear();
        filmNames->AddStrings(inNames);
}

AnsiString Film::getBaseFilmName(){
        if (filmNames->Count>0){
                return filmNames->Strings[0];
        }

        return *new AnsiString("!!!�������� ���!!!");
}


void Film::setBaseFilmName(AnsiString baseName){
        //���� baseName � ������
        int pos = filmNames->IndexOf(baseName);
        //�� �������, �������
        if (pos == -1) return;

        AnsiString tmp = filmNames->Strings[pos];

        filmNames->Delete(pos);

        filmNames->Insert(0, tmp);

}


/////////////�����Ѩ��//////////////////
TStringList *Film::getDirectors(){
       return directors;
}

void Film::setDirectors(TStringList *inDirectors){
        if (inDirectors == NULL) return;

        directors->Clear();
        directors->AddStrings(inDirectors);
}



////////////��Ҩ��//////////////////////
TStringList *Film::getActors(){
        return actors;
}

void Film::setActors(TStringList *inActors){
        if (inActors == NULL) return;

        actors->Clear();
        actors->AddStrings(inActors);
}




//////////���///////////////////////
AnsiString Film::getYear(){
        return filmYear;
}

void Film::setYear(AnsiString inYear){
        filmYear = inYear;
}





////////����������� ������/////////
TStringList *Film::getImageNames(){
        return filmImages;
}

void Film::setImageNames(TStringList *inImages){
        filmImages = inImages;
}

AnsiString Film::getBaseImageName(){
        if (filmImages->Count>0){
                return filmImages->Strings[0];
        }

        return *new AnsiString();
}

void Film::setBaseImageName(AnsiString baseName){
        //���� baseName � ������
        int pos = filmImages->IndexOf(baseName);
        //�� �������, �������
        if (pos == -1) return;

        AnsiString tmp = filmImages->Strings[pos];

        filmImages->Delete(pos);

        filmImages->Insert(0, tmp);
}

bool Film::imageExist(){
	if (filmImages->Count>0) return true;
        return false;
}

////////��������� � ������/////////
TextSelection Film::getSelection(){
        return textSelection;
}

void Film::setSelection(TextSelection newSelection){
        textSelection = newSelection;
}


/////////////////////����� ������//////////////
void Film::setShowTime(ShowTime inShowTime){
	showTime = new ShowTime(inShowTime.getHour(), inShowTime.getMinute());
}


ShowTime Film::getShowTime(){
	return *showTime;
}



////////////////////��� ������/////////////////
FilmType Film::getType(){
	return filmType;
}

void Film::setFilmType(FilmType inType){
	filmType = inType;
}

AnsiString Film::getTypeString(){
	switch(filmType){
        	case FEATURE: return *new AnsiString("��������������");
                case SERIAL: return *new AnsiString("������");
		case MULITIPLICATION: return *new AnsiString("����������");
                case SINCE: return *new AnsiString("������-����������");
                default: return *new AnsiString("����������� ���!!!!");
        }
}

