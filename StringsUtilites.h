#ifndef StringsUtilitesH
#define StringsUtilitesH
#include <vcl.h>

//Удаляет из строки str символы не допустимые в имени файла
void clearFileSystemServiceSymbol(AnsiString *str);

//Обрезка строки по бокам
void trimString(AnsiString *str);

#endif