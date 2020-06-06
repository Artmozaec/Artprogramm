#include "DirectorCategory.h"
#include "StringContainer.h"
#include "StringsUtilites.h"

DirectorCategory::DirectorCategory(){
	directorLabel = new TStringList();
        directorLabel->Add( *new AnsiString("режиссеры"));
        directorLabel->Add( *new AnsiString("режисеры"));
        directorLabel->Add( *new AnsiString("режиссер"));
        directorLabel->Add( *new AnsiString("режиссёр"));
        directorLabel->Add( *new AnsiString("режисер"));
        directorLabel->Add( *new AnsiString("режисёр"));


        //Латинская первая с
        directorLabel->Add( *new AnsiString("режиcсеры"));
        directorLabel->Add( *new AnsiString("режиcеры"));
        directorLabel->Add( *new AnsiString("режиcсер"));
        directorLabel->Add( *new AnsiString("режиcсёр"));
        directorLabel->Add( *new AnsiString("режиcер"));



        //Латинская вторая с
        directorLabel->Add( *new AnsiString("режисcеры"));
        directorLabel->Add( *new AnsiString("режисcер"));
        directorLabel->Add( *new AnsiString("режисcёр"));

}


//Создаём из directorsString
TStringList *DirectorCategory::getCategoryList(){
        AnsiString text = directorsString;
        trimString(&text);
        AnsiString delimiters = *new AnsiString(",");
        TStringList *result = new TStringList();

        if (directorsString.IsEmpty()) return result;
        int end = 0;


        while ((end = text.Pos(delimiters)) != 0){
		result->Add(text.SubString(0, end-1).Trim());
                text = text.SubString(end+1, text.Length());
        }

        result->Add(text.Trim());

        return result;
}

bool DirectorCategory::search(StringContainer *stringContainer){
	//Ищем начало категории
        int searchIndex = stringContainer->searchStringList(directorLabel);

	if (searchIndex == StringContainer::NOT_SEARCH) return false;

        //Смещаемся вперёд на размер метки
        stringContainer->movePointerFrontTo(directorLabel->Strings[searchIndex].Length());

	//Запоминаем текущую позицию
        stringContainer->memoryPosition();

        //Ищем перенос строки
	stringContainer->searchString( *new AnsiString("\r\n"));

        directorsString = stringContainer->getSubstringInMemoryPositionToCurrent();

        //Восстанавливаем позицию
        stringContainer->restorePosition();

        return true;
}


CategoryType DirectorCategory::getCategoryType(){
	return DIRECTOR_TYPE;
}

//возвращает истину если строка содержит категорию
bool DirectorCategory::contentCategory(AnsiString inString){
	return false;
}

void DirectorCategory::movePointerFront(StringContainer *stringContainer){
	stringContainer->movePointerFrontTo(directorsString.Length());
}
