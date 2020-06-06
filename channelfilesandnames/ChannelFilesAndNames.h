#ifndef ChannelH
#define ChannelH
#include <vcl.h>
#include "ChannelsList.h"

//�������� ������� ����� ��������� ����� �������
//� ������� ������������ �������� ���� � ����� ������ ����� ������

class ChannelFilesAndNames{
public:
	ChannelFilesAndNames();
	//��������� ��������� ���� ����� � ������ ��������������
	void addChannelFileName(AnsiString fileName);

        //������� ����� �� ������
        void deleteChannelFileName(AnsiString fileName);

	//���������� ������� ������ �������� �������
	TStringList *getChannelList();

	//���������� ��� ����� �� ����� ������
	AnsiString getFileName(AnsiString channelName);

        static const char *EMPTY_CHANNEL;
private:
	ChannelsList *channelsList;
	//�������������� ������
	TStringList *currentChannelsList;
};

#endif