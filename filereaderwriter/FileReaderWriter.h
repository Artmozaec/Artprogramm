#ifndef FileReaderH
#define FileReaderH
#include <vcl.h>


class FileReaderWriter{

public:		// User declarations
        FileReaderWriter();

	TStringList *readWinText(AnsiString patch);
	TStringList *readDosText(AnsiString patch);

        void saveTextToFile(AnsiString filePatch, AnsiString *fileText);

private:	// User declarations
	static const int BUFER_SIZE = 1000;

        //Конвертирует строки list в кодировку dos
        TStringList *convertTStringListToDOS(TStringList *list);
};

#endif
