#ifndef FilmsMapH
#define FilmsMapH
#include <vcl.h>
#include "TextSelection.cpp"
#include "ShowTime.h"

class FilmsMap{
public:
	FilmsMap();
	void createMap(AnsiString *channelText);

	AnsiString getFilmText(AnsiString *channelText);

        ShowTime getTimeInPosition(int position);

	bool isOk();
	//� ������ ������ �������� ���������� ���������� ��������� ����� ������ � ������
	TextSelection getErrorSelectionInText();
private:
        static const int MAP_SIZE = 100;
	//��������� �� ������� �����
        int mapPointer;
	//������� ������ �����
	int mapLength;
	int filmBegin[MAP_SIZE];
	int filmLength[MAP_SIZE];
        ShowTime *showTimeArray[MAP_SIZE];

	//��������� ���������� ��������� �������������� ������
        TextSelection errSelection;

        bool parseError;

        //��������� � ����� ���������� ������ ������
        void addFilmToMap(int begin, int length, ShowTime showTime);

	//������� ��������� �� ��������� �����
        bool nextFilm();
};
#endif