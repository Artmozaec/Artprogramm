#ifndef FileOperationsH
#define FileOperationsH
#include <vcl.h>
#include <SysUtils.hpp>

//���������� ������ ���������� � ������ � directoryPatch
void getDirectoryContent(AnsiString directoryPatch, TStringList *directoryContentPtr);

//�������� ����� - files, �� ��������� source � �������� dest
void copyFiles(AnsiString source, AnsiString dest, TStringList *files);

//������� ������ ������ - files � ���������� dir
void deleteFiles(AnsiString dir, TStringList *files);



#endif