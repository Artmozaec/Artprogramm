#ifndef ChannelListH
#define ChannelListH
#include <vcl.h>
class ChannelsList{
public:
	ChannelsList();
	
	//���������� ��� ����� �� ����� ������
	AnsiString getFileName(AnsiString channel);

	//���������� �������� ������ �� ����� �����
	AnsiString getChannelName(AnsiString fileName);
private:
	TStringList *fileNames;
	TStringList *channelNames;
};

#endif