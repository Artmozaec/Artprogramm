#include "StringsUtilites.h"


//������� �� ������ str ������� �� ���������� � ����� �����
void clearFileSystemServiceSymbol(AnsiString *str){

	//��������� ������� �������� �������
        AnsiString delimiters = *new AnsiString("/\\,.*:'\"?<>|");

        //�������� �� ���� �������� ������ � ������� ��������� ������� ������ ��
        for(int ch=1; ch<=str->Length(); ch++){
		//��-��� ������ �������, ��������� �������! �� �����!!!!
                unsigned char sym = (*str)[ch];
                if ((sym< 0x20) || (str->IsDelimiter(delimiters, ch))){
                        str->Delete(ch, 1);
                        //��-�� ���� ������ ��������!
                        ch--;
                }
        }
}


//�������� �������, �������� �����
void trimString(AnsiString *str){
	AnsiString delimiters = *new AnsiString("\t\r\n \" {}[]/*':;");
	//�������� ������
        while (str->IsDelimiter(delimiters, 1)){
               str->Delete(1,1);
        }

        //�������� �����
        while (str->IsDelimiter(delimiters, str->Length())){
               str->Delete(str->Length(),1);
        }
}


