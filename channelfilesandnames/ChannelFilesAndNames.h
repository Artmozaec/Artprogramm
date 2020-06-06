#ifndef ChannelH
#define ChannelH
#include <vcl.h>
#include "ChannelsList.h"

//Содержит текущий набор доступных фалов анонсов
//И таблицу ссответствий названия кана и файла анонса этого канала

class ChannelFilesAndNames{
public:
	ChannelFilesAndNames();
	//Добавляет очередной файл канал в список присутствующих
	void addChannelFileName(AnsiString fileName);

        //Удаляет канал из списка
        void deleteChannelFileName(AnsiString fileName);

	//Возвращает текущий список названий каналов
	TStringList *getChannelList();

	//Возвращает имя файла по имени канала
	AnsiString getFileName(AnsiString channelName);

        static const char *EMPTY_CHANNEL;
private:
	ChannelsList *channelsList;
	//Присутствующие анонсы
	TStringList *currentChannelsList;
};

#endif