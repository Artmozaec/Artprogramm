#include "FilesSearcher.h"
#include "TranslitVariator.h"
#include "FileOperations.cpp"

FilesSearcher::FilesSearcher(TStringList *inImageDirContent){
        imageDirContent = inImageDirContent;
}

TStringList *FilesSearcher::searchVariationsInDirContent(TStringList *translitVariations){
        TStringList *result = new TStringList();




        for(int DirContentCh=0; DirContentCh<imageDirContent->Count; DirContentCh++){

                AnsiString dirStr = imageDirContent->Strings[DirContentCh];
                for (int VarCh=0; VarCh<translitVariations->Count; VarCh++){
                     AnsiString queryStr = translitVariations->Strings[VarCh];

                     //Если вариация запроса найдена в текущем имени файла
                     int res = dirStr.Pos(queryStr);
                     if (res != 0){
                        //Добавляем имя файла в результаты поиска
                        result->Add(dirStr);
                        //Покидаем цикл пропуская ненужные итерации поиска
                        break;
                     }
                }
        }
        return result;
}


void FilesSearcher::trimTStringList(TStringList *list, int maxSize){
	for (int ch=list->Count-1; ch>maxSize; ch--){
		list->Delete(ch);
        }
}


TStringList *FilesSearcher::Search(AnsiString searchPattern){
        TStringList *searchResult;
        TStringList *translitVariations;

        //Создаём возможные вариации транслита русской надписи
        TranslitVariator *variator = new TranslitVariator(&searchPattern);
        translitVariations = variator->getVariationList();

        //Если колличество вариаций больше чем максимально возможное,
        if (translitVariations->Count > MAX_VARIATION){
        	//обрезаем лишние вариации
                trimTStringList(translitVariations, MAX_VARIATION);
        }

        //добавляем исходный запрос
        translitVariations->Add(searchPattern);
        searchResult = searchVariationsInDirContent(translitVariations);

        return searchResult;
}
