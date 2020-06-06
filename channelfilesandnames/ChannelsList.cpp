#include "ChannelsList.h"

ChannelsList::ChannelsList(){
	fileNames = new TStringList();
	channelNames = new TStringList();
	
	//��������� �������
	fileNames->Add( *new AnsiString("an_ut2.txt"));
	channelNames->Add( *new AnsiString("1+1"));
	
	fileNames->Add( *new AnsiString("an_trk.txt"));
	channelNames->Add( *new AnsiString("��� �������"));
	
	fileNames->Add( *new AnsiString("an_tonis.txt"));
	channelNames->Add( *new AnsiString("�����"));
	
	fileNames->Add( *new AnsiString("an_stb.txt"));
	channelNames->Add( *new AnsiString("���"));
	
	fileNames->Add( *new AnsiString("an_ntn.txt"));
	channelNames->Add( *new AnsiString("���"));
	
	fileNames->Add( *new AnsiString("an_nk.txt"));
	channelNames->Add( *new AnsiString("����� �����"));
	
	fileNames->Add( *new AnsiString("an_kino.txt"));
	channelNames->Add( *new AnsiString("2+2"));
	
	fileNames->Add( *new AnsiString("an_k1.txt"));
	channelNames->Add( *new AnsiString("K1"));
	
	fileNames->Add( *new AnsiString("an_ictv.txt"));
	channelNames->Add( *new AnsiString("ICTV"));
}

AnsiString ChannelsList::getFileName(AnsiString channel){
	int index = channelNames->IndexOf(channel);
	//���� ������ �� �������
	if (index == -1) return NULL;
	
	return fileNames->Strings[index];
}

AnsiString ChannelsList::getChannelName(AnsiString fileName){
	int index = fileNames->IndexOf(fileName);
	//���� ������ �� �������
	if (index == -1) return NULL;

	return channelNames->Strings[index];
}