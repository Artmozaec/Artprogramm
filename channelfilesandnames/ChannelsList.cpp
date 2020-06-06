#include "ChannelsList.h"

ChannelsList::ChannelsList(){
	fileNames = new TStringList();
	channelNames = new TStringList();
	
	//Заполняем таблицу
	fileNames->Add( *new AnsiString("an_ut2.txt"));
	channelNames->Add( *new AnsiString("1+1"));
	
	fileNames->Add( *new AnsiString("an_trk.txt"));
	channelNames->Add( *new AnsiString("ТРК Украина"));
	
	fileNames->Add( *new AnsiString("an_tonis.txt"));
	channelNames->Add( *new AnsiString("ТОНИС"));
	
	fileNames->Add( *new AnsiString("an_stb.txt"));
	channelNames->Add( *new AnsiString("СТБ"));
	
	fileNames->Add( *new AnsiString("an_ntn.txt"));
	channelNames->Add( *new AnsiString("НТН"));
	
	fileNames->Add( *new AnsiString("an_nk.txt"));
	channelNames->Add( *new AnsiString("Новый канал"));
	
	fileNames->Add( *new AnsiString("an_kino.txt"));
	channelNames->Add( *new AnsiString("2+2"));
	
	fileNames->Add( *new AnsiString("an_k1.txt"));
	channelNames->Add( *new AnsiString("K1"));
	
	fileNames->Add( *new AnsiString("an_ictv.txt"));
	channelNames->Add( *new AnsiString("ICTV"));
}

AnsiString ChannelsList::getFileName(AnsiString channel){
	int index = channelNames->IndexOf(channel);
	//Если ничего не найдено
	if (index == -1) return NULL;
	
	return fileNames->Strings[index];
}

AnsiString ChannelsList::getChannelName(AnsiString fileName){
	int index = fileNames->IndexOf(fileName);
	//Если ничего не найдено
	if (index == -1) return NULL;

	return channelNames->Strings[index];
}