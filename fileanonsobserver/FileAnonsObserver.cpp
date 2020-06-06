//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#pragma package(smart_init)
#include "ArtProgrammFrm.h"
#include "FileAnonsObserver.h"
#include "FileOperations.cpp"
#include "FileReaderWriter.h"

#include <SysUtils.hpp>
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall FileAnonsObserver::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall FileAnonsObserver::FileAnonsObserver(bool CreateSuspended, TArtProgramm *inListener)
        : TThread(CreateSuspended)
{
        listener = inListener;
        anonsTextPatch = *new AnsiString();
        anonsFiles = new TStringList();

        //����� ��������� ��������
        observe = true;
}


//����� ����������� � ����� ������� ������
void FileAnonsObserver::searchAddedFiles(TStringList *folderContent){
        for (int ch=0; ch<folderContent->Count; ch++){
                 //���� ������� ������ ��� � �������� ������
                 if (anonsFiles->IndexOf(folderContent->Strings[ch]) == -1){
                        //��������� ��� ����� � �������� ������
                        anonsFiles->Add(folderContent->Strings[ch]);

                        //�������� ����� ��������� - ����� ����!
                        listener->newChannelDetected(folderContent->Strings[ch]);

                 }
        }
}


//����� �������� �� ����� ������� ������
void FileAnonsObserver::searchDeletedFiles(TStringList *folderContent){

        int ch=0;
        while (ch<anonsFiles->Count){
                //���� �� ������� ������ ��������� ������ � ������� ����������
                //������ ���� �����!
                if (folderContent->IndexOf(anonsFiles->Strings[ch]) == -1){
                        //����� ��������� ���� �����
                        listener->deleteChannelDetected(anonsFiles->Strings[ch]);


                        //������� ��� ����� �� ����������� �����
                        anonsFiles->Delete(ch);

                        //���������� ���� ��� �������� ch
                        continue;
                }

                ch++;
       }
}


//��������� ������� ������ ����� ������
void __fastcall FileAnonsObserver::refresh(){
	TStringList *folderContent = new TStringList();
        //ShowMessage("refre");
	if (DirectoryExists(anonsTextPatch)){
		//�������� ������ ������ �� ���������� ������� �� ������� ������
		getDirectoryContent(anonsTextPatch, folderContent);

		//���� ����������� �����
		searchAddedFiles(folderContent);

		//���� �������� �����
		searchDeletedFiles(folderContent);
	} else {
        	ShowMessage("�� �������� ����� �������! ���������� ��������������");
                observe = false;
                listener->stopTrackingAnonsFolder();
	}
}

//---------------------------------------------------------------------------
void __fastcall FileAnonsObserver::Execute()
{
        //---- Place thread code here ----
        while (!Terminated){
                if (observe) Synchronize(refresh);
                Sleep(10000);
        }
}

TStringList *FileAnonsObserver::getChannelText(AnsiString fileName){
	TStringList *textList;
	FileReaderWriter *reader = new FileReaderWriter();

        textList = reader->readDosText(anonsTextPatch+fileName);

        return textList;
}



//���������� ��������
void FileAnonsObserver::stopTracking(){
	observe = false;
}

//����������� ��������
void FileAnonsObserver::startTracking(){
	observe = true;
}

void FileAnonsObserver::setAnonsTextPatch(AnsiString inAnonsTextPatch){
	anonsTextPatch = inAnonsTextPatch;
}
//---------------------------------------------------------------------------
