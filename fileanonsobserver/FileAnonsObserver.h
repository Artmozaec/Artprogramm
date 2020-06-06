//---------------------------------------------------------------------------

#ifndef FileAnonsObserverH
#define FileAnonsObserverH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TArtProgramm;
class FileAnonsObserver : public TThread
{
public:
        __fastcall FileAnonsObserver(bool CreateSuspended, TArtProgramm *inListener);

        //������� ���� ������
        void clear();

        //��� ������ ������
        TStringList *getFilesList();

        //���������� ����� ����������� � fileName
        TStringList *getChannelText(AnsiString fileName);

        //���������� ��������
        void stopTracking();

        //����������� ��������
        void startTracking();

        //��������� ������� ������ ����� ������
	void __fastcall refresh();
		
		void setAnonsTextPatch(AnsiString inAnonsTextPatch);
protected:
        void __fastcall Execute();

private:
	//��������� ����� �������� ���������� ��� ����������� ����� ������
	TArtProgramm *listener;

        //���� � ����� � �������� �������
        AnsiString anonsTextPatch;

        //���� � ������� �������� �������� ������ ������ �������
        TStringList *anonsFiles;

        //����� ����������� � ����� ������� ������
        void searchAddedFiles(TStringList *folderContent);

        //����� �������� �� ����� ������� ������
        void searchDeletedFiles(TStringList *folderContent);

        //���� �� ������ - ���������� �������� ���������� �������
        bool observe;
};
//---------------------------------------------------------------------------
#endif
