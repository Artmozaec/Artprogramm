#include "WeekTextMap.h"
#include "StringContainer.h"
#include "WeekDayCategory.h"
#include "TextSelection.cpp"
WeekTextMap::WeekTextMap(){
	mapLength = 0;

        parseError = false;

        errSelection.begin = 0;
        errSelection.length = 0;
}

WeekDay WeekTextMap::weekDayInPosition(int position){
	for (int ch=1; ch<=mapLength; ch++){
        	if (position<dayBegin[ch]){
                	//if (ch == 1) return *new WeekDay(-1);

                        return *new WeekDay(dayIndexes[ch-1]);
                }
        }

        return *new WeekDay(dayIndexes[mapLength]);
}


void WeekTextMap::addDayToMap(WeekDay day, int begin){
	//Увеличиваем ёмкость
        mapLength++;


        dayIndexes[mapLength] = day.getDayInt();
        dayBegin[mapLength] = begin;

}

int WeekTextMap::getIndexDay(int day){
	for (int ch=1; ch<=mapLength; ch++){
        	if (dayIndexes[ch] == day) return ch;
        }

        return -1;
}

TextSelection WeekTextMap::getErrorSelectionInText(){
	return errSelection;
}

bool WeekTextMap::isOk(){
	return !parseError;
}

void WeekTextMap::createMap(AnsiString *inString){
	mapLength = 0;
	//ShowMessage("createMap"+inString);
        AnsiString lowCaseText = inString->LowerCase();
        StringContainer *container = new StringContainer(&lowCaseText);
        WeekDayCategory *weekDayCategory = new WeekDayCategory();

        //Пока следующий день недели найден

        while (weekDayCategory->search(container)){
                WeekDay curDay = weekDayCategory->getWeekDay();
                weekDayCategory->movePointerFront(container);
        	//ShowMessage(curDay.getDayString());


                int index = getIndexDay(curDay.getDayInt());

                //Такой день только-что был, (повторения в пределах одного дня)
		if (index == mapLength){
                        //ShowMessage("Повтор "+curDay.getDayString());
                        continue;
                }

                //Если день встречался, это не есть гуд!
                if (index != -1){
                	ShowMessage("!!!!!!!ТАКОЙ ДЕНЬ БЫЛ!!!!!!!!" + curDay.getDayString());

                        //Устанавливаем позицию ошибочного выделения
                        errSelection.begin = container->getCurrentPosition();
                        errSelection.length = 5;
                        parseError = true;

                        return;
                }

                //День недели должен последовательно увеличиваться
                if ((mapLength !=0) && (dayIndexes[mapLength]>curDay.getDayInt())){
                        ShowMessage("!!!!!!!НАРУШЕНИЕ ПОСЛЕДОВАТЕЛЬНОСТИ ДНЕЙ!!!!!!!!");

                        //Устанавливаем позицию ошибочного выделения
                        errSelection.begin = container->getCurrentPosition();
                        errSelection.length = 5;
                        parseError = true;

                        return;
                }

		addDayToMap(curDay, container->getCurrentPosition());

        }

}