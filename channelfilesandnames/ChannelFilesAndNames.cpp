#include "ChannelFilesAndNames.h"

const char *ChannelFilesAndNames::EMPTY_CHANNEL = "!!! ÎØÈÁÊÀ ÊÀÍÀËÀ !!!";


ChannelFilesAndNames::ChannelFilesAndNames(){
	channelsList = new ChannelsList();
	currentChannelsList = new TStringList();
        //currentChannelsList->Add(EMPTY_CHANNEL);
}

void ChannelFilesAndNames::addChannelFileName(AnsiString fileName){
	AnsiString channelName = channelsList->getChannelName(fileName);
	if (channelName == NULL) return;
	currentChannelsList->Add(channelName);
}

void ChannelFilesAndNames::deleteChannelFileName(AnsiString fileName){
        int pos = currentChannelsList->IndexOf(channelsList->getChannelName(fileName));
        if (pos == -1) return;
        currentChannelsList->Delete(pos);
}

AnsiString ChannelFilesAndNames::getFileName(AnsiString channelName){
        return channelsList->getFileName(channelName);
}

TStringList *ChannelFilesAndNames::getChannelList(){
	return currentChannelsList;
}