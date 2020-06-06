#include "FileOperations.h" 

void getDirectoryContent(AnsiString directoryPatch, TStringList *directoryContentPtr){
     TSearchRec searchRec;
     //�������� �����, ���� � ���������� ���� ������� ����� - ����������
     
     FindFirst((directoryPatch+"*.*").c_str(), faAnyFile, searchRec);
         while ((FindNext(searchRec))==0){
                if ((searchRec.Name != "..")          &&
                    (searchRec.Name != "...")         &&
                    (searchRec.Name != "Thumbs.db"))
                {
                        directoryContentPtr->Add(searchRec.Name);
                }
         }
     FindClose(searchRec);
}

//�������� ����� - files, �� ��������� source � �������� dest
void copyFiles(AnsiString source, AnsiString dest, TStringList *files){
        AnsiString *sourceFile;
        AnsiString *destFile;
        for (int ch=0; ch<files->Count; ch++){
                sourceFile = new AnsiString(source + files->Strings[ch].c_str());
                destFile = new AnsiString(dest + files->Strings[ch].c_str());
                if (!CopyFile(sourceFile->c_str(), destFile->c_str(), false)){
                            ShowMessage("������ ����������� �����");
                }
        }
}

//������� ������ ������ - files � ���������� dir
void deleteFiles(AnsiString dir, TStringList *files){
        AnsiString *delFile;
        for (int ch=0; ch<files->Count; ch++){
                delFile = new AnsiString(dir + files->Strings[ch].c_str());
                if (!DeleteFile(delFile->c_str())){
                        ShowMessage("������ �������� �����");
                }
        }
}


