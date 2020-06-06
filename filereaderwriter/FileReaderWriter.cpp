#include "FileReaderWriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream.h>
#include <system.hpp>

FileReaderWriter::FileReaderWriter(){

}


TStringList *FileReaderWriter::readWinText(AnsiString patch){
	FILE *file;

        //Пытаемся открыть файл
        if ((file = fopen(patch.c_str(), "rt")) == NULL){
        	//файл открыть не удалось
                //ShowMessage("Почему-то файл "+patch+" прочитать не удаётся!");
        	return NULL;
        }

        TStringList *text = new TStringList();

        //Буфер
        char buf[BUFER_SIZE];

        do{
        	//Читаем из файла в буфер BUFER_SIZE символов
		fgets(buf, BUFER_SIZE, file);

                //Если дочитали файл до конца, выходим из цикла
                if (feof(file)) break;

                //Если при текущем чтении в буфере остался символ окончания строки '\n'
                //Что - бы выглядело красивее там должен быть 0
                if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;

                text->Add( *new AnsiString(buf));
        } while (true);

        fclose(file);
	return text;
}

TStringList *FileReaderWriter::convertTStringListToDOS(TStringList *list){
	if (list == NULL) return NULL;
        TStringList *result = new TStringList();

        AnsiString win;

        char dos[BUFER_SIZE];
        for (int ch=0; ch<list->Count; ch++){
        	win = list->Strings[ch];
                OemToChar(win.c_str(), dos);
                result->Add(*new AnsiString(dos));

	}

	return result;
}


TStringList *FileReaderWriter::readDosText(AnsiString patch){
        TStringList *resultList = readWinText(patch);
        return convertTStringListToDOS(resultList);
}


void FileReaderWriter::saveTextToFile(AnsiString filePatch, AnsiString *fileText){
        FILE *file;

        if ((file = fopen(filePatch.c_str(), "wb")) == NULL){
        	//файл открыть не удалось
                ShowMessage("Почему-то файл "+filePatch+" создать не удаёться!");
        	return;
        }


        fwrite(fileText->c_str(), sizeof(char), fileText->Length(), file);

        fclose(file);
}
