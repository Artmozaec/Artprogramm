#ifndef FileOperationsH
#define FileOperationsH
#include <vcl.h>
#include <SysUtils.hpp>

//Возвращает список директорий и файлов в directoryPatch
void getDirectoryContent(AnsiString directoryPatch, TStringList *directoryContentPtr);

//Копирует файлы - files, из источника source в приемник dest
void copyFiles(AnsiString source, AnsiString dest, TStringList *files);

//Удаляет список файлов - files в директории dir
void deleteFiles(AnsiString dir, TStringList *files);



#endif