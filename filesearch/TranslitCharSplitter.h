#ifndef TranslitCharSplitterH
#define TranslitCharSplitterH
#include <vcl.h>
class TranslitCharSplitter{
public:
	TranslitCharSplitter(AnsiString *inString);

	//���������� ������� ������ ��������
	TStringList *getTranslitList();
private:
	bool nextChar();
	int length;
	int pointer;
	char *contentPtr;
};
#endif