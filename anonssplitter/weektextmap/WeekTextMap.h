#ifndef WeekTextMapH
#define WeekTextMapH
#include "WeekDay.h"
#include "TextSelection.cpp"

class TChannelText;
class WeekTextMap{
public:
	WeekTextMap();

	WeekDay weekDayInPosition(int position);

	void createMap(AnsiString *inString);

	bool isOk();

	//� ������ ������ �������� ���������� ���������� ��������� ����� ������ � ������
	TextSelection getErrorSelectionInText();
private:
	//������� ������ �����
	int mapLength;
	int dayIndexes[8];
	int dayBegin[8];

        void addDayToMap(WeekDay day, int begin);

	//��� ������ ���, ���� �������, ���� ��� ���������� -1
        int getIndexDay(int day);

	//��������� ���������� ��������� �������������� ������
        TextSelection errSelection;

        bool parseError;
};
#endif