#ifndef FilesSearcherH
#define FilesSearcherH
#include <vcl.h>

class FilesSearcher{
public:
	FilesSearcher(TStringList *inImageDirContent);
	TStringList *Search(AnsiString searchPattern);

private:

        //void DirectoryContentToLowerCase();
        TStringList *searchVariationsInDirContent(TStringList *translitVariations);
        bool isExistPattern(AnsiString *pattern, AnsiString *text);
	//������ ���� ������ ����������
	TStringList *imageDirContent;

	//������������ ����������� �������� ��������� ������� ������
        const static int MAX_VARIATION = 200;

        //������� TStringList
        void trimTStringList(TStringList *list, int maxSize);
};
#endif