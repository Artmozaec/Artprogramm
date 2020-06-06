#ifndef ChannelListH
#define ChannelListH
#include <vcl.h>
class ChannelsList{
public:
	ChannelsList();
	
	//Возвращает имя файла по имени канала
	AnsiString getFileName(AnsiString channel);

	//возвращает название канала по имени файла
	AnsiString getChannelName(AnsiString fileName);
private:
	TStringList *fileNames;
	TStringList *channelNames;
};

#endif