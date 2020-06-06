#include "StringsUtilites.h"


//Удаляет из строки str символы не допустимые в имени файла
void clearFileSystemServiceSymbol(AnsiString *str){

	//Служебные символы файловой системы
        AnsiString delimiters = *new AnsiString("/\\,.*:'\"?<>|");

        //Проходим по всем символам строки и находим служебные символы удаляя их
        for(int ch=1; ch<=str->Length(); ch++){
		//Всё-что раньще пробела, служебные символы! Их нахуй!!!!
                unsigned char sym = (*str)[ch];
                if ((sym< 0x20) || (str->IsDelimiter(delimiters, ch))){
                        str->Delete(ch, 1);
                        //Мы-же один символ удалаили!
                        ch--;
                }
        }
}


//Обрезает пробелы, переносы строк
void trimString(AnsiString *str){
	AnsiString delimiters = *new AnsiString("\t\r\n \" {}[]/*':;");
	//Обрезаем начало
        while (str->IsDelimiter(delimiters, 1)){
               str->Delete(1,1);
        }

        //Обрезаем конец
        while (str->IsDelimiter(delimiters, str->Length())){
               str->Delete(str->Length(),1);
        }
}


