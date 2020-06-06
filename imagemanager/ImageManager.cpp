#include "ImageManager.h"
#include "FileOperations.cpp"
#include <SysUtils.hpp>
//#include "ShellAPI.h"
#include <stdio.h>
#include "ShareFoldersManager.h"
#include "FilmIterator.h"
#include "StringsUtilites.h"
#include "FileReaderWriter.h"

ImageManager::ImageManager(FilmContainer *inFilmContainer){
	filmContainer = inFilmContainer;

	imageStoragePatch = *new AnsiString();
	workDirectoryPatch = *new AnsiString();
    shareFolderPatch = *new AnsiString();

    imageBaseContent = new TStringList();
}

//Файлы рабочей директории
TStringList *ImageManager::getWorkFolderContent(){
	TStringList *content = new TStringList();

        //Получаем список файлов рабочей папки
	getDirectoryContent(workDirectoryPatch, content);

	//Вытираем расширения
        clearExtension(content);

        //в нижний регистр
        listToLowerCase(content);

        return content;
}

//Содержимое базы изображений
TStringList *ImageManager::getBaseImageContent(){
     return imageBaseContent;
}




void ImageManager::listToLowerCase(TStringList *inList){
        for(int ch=0; ch<inList->Count; ch++){
            inList->Strings[ch] = inList->Strings[ch].LowerCase();
        }
}


void ImageManager::clearExtension(TStringList *inList){
        for (int ch=0; ch<inList->Count; ch++){
                //Берём имя файла без расширения
                inList->Strings[ch] = getWithoutExtension(inList->Strings[ch]);
        }
}



//Возвращает имя файла name без расширения
AnsiString ImageManager::getWithoutExtension(AnsiString name){
     //Находим позицию начала расширения файла
     int pos = name.Pos(ExtractFileExt(name));

     //Усекаем имя до этой позиции
     name.SetLength(pos-1);

     return name;
}


AnsiString ImageManager::getExtension(AnsiString patch, AnsiString file){
        //Если путь - база изображений, там только tif
        if (patch == imageStoragePatch) return *new AnsiString(".tif");

        //Получаем список файлов по пути patch
        TStringList *fileList = new TStringList();
        getDirectoryContent(patch, fileList);
        //В нижний регистр!
        listToLowerCase(fileList);


        //Находим совпадения в листе с искомым файлом
        for (int ch=0; ch<fileList->Count; ch++){
                if (fileList->Strings[ch].Pos(file) != 0){
                        return ExtractFileExt(fileList->Strings[ch]);
                }
        }

        return *new AnsiString();
}


AnsiString ImageManager::getPatch(AnsiString fileName){
        if (fileName.IsEmpty()) return *new AnsiString();

        //С начала определяем в какой папке лежит искомый файл
        AnsiString patch = searchFileInDirectories(fileName);

        //Если мы ничего не нашли,
        if (patch.IsEmpty()){
                return patch;
        }

	//Находим расширение файла
        AnsiString ext = getExtension(patch, fileName);

        return patch+fileName+ext;
}

void ImageManager::renameFile(AnsiString oldName, AnsiString newName){
        AnsiString oldNameDirectory = searchFileInDirectories(oldName);
        AnsiString oldNameExtension = getExtension(oldNameDirectory, oldName);

        if (oldNameDirectory.IsEmpty()){
                ShowMessage("Файл "+oldName+" отсутствует!");
                return;
        }

        rename(
                new AnsiString (oldNameDirectory+oldName+oldNameExtension)->c_str(),
                new AnsiString (oldNameDirectory+newName+oldNameExtension)->c_str()
        );
}

AnsiString ImageManager::searchFileInDirectories(AnsiString fileName){
        //С начала ведём поиск в папках выхода
        TStringList *dirList = getWorkFolderContent();

	if (dirList->IndexOf(fileName) != -1) return workDirectoryPatch;

        //Ищем в базе изображений
        //В базе могут лежать только .tif поэтому
	if (FileExists(imageStoragePatch+fileName+".tif")) return imageStoragePatch;

        //Ничего не найдено, пустая строка означает этот прискорбный факт
        return *new AnsiString();
}


////////////////////////////СЕССИЯ//////////////////////////////////////////////
//Корректны только файлы с расширением *.tif
bool ImageManager::fileIsCorrect(AnsiString name){
        if (ExtractFileExt(name) == ".tif") return true;
        return false;
}

//Проверяет список файлов folderContent на наличие файлов не tif - необработанных фильмов
bool ImageManager::checkNotCorrectFilms(TStringList *folderContent){
        for (int fileCh=0; fileCh<folderContent->Count; fileCh++){
                if (!fileIsCorrect(folderContent->Strings[fileCh])){
                      return false;
                }
        }
        return true;
}

//проверяем содержимое выходных директорий
bool ImageManager::DirectoryContentIsOk(){
        TStringList *files = new TStringList();

	getDirectoryContent(workDirectoryPatch, files);
        if (!checkNotCorrectFilms(files)){
        	ShowMessage("Недопустимый формат выходного файла!!!");
                return false;
        }

        return true;
}

//копирование содержимого директорий выхода в хранилище файлов
void ImageManager::saveDirectoryContentInStore(){
        TStringList *files = new TStringList();

        //Берём список файлов рабочей папки
        getDirectoryContent(workDirectoryPatch, files);

        //Копируем список файлов в хранилище
        copyFiles(workDirectoryPatch, imageStoragePatch, files);
}


//В соответствии с типом фильма(для не художественных), создаётся метка в виде пустого файла в базе изображений с именем фильма и его типом
//Это позволяет найти этот злополучный фильм в следующий раз в базе
void ImageManager::createBadTypesFilmLabels(){
	FilmIterator *iterator = filmContainer->getIterator();
        Film *film;
        AnsiString patch;
        AnsiString filmName;
        AnsiString filmDirector;
        while(iterator->nextFilm()){
                film = iterator->getFilm();
                //Если тип фильма - не художественный
                if (film->getType() != FEATURE){
                	filmName = film->getBaseFilmName();

			filmDirector = film->getDirectors()->Strings[0];
	                //Очищаем имя от возможных плохих символов
        	        clearFileSystemServiceSymbol(&filmName);

                	patch = imageStoragePatch+"("+film->getTypeString()+")"+filmName+" "+film->getYear()+" ("+filmDirector+").tif";

                	//ShowMessage(patch);
                	//Создаём пустой файл с именем

                	FileReaderWriter *fileReaderWriter = new FileReaderWriter();
			fileReaderWriter->saveTextToFile(patch, new AnsiString(" "));
                }
        }
}

void ImageManager::terminateSession(){


        //проверяем все выходные директории
        //если в содержимом ошибки, то выходим
        if (!DirectoryContentIsOk()) return;

        //копируем содержимое директорий выхода в хранилище файлов
        saveDirectoryContentInStore();

	//Создаём метки плохих типов, сериал, мультики что-бы в буду... та нахуй
        createBadTypesFilmLabels();

        //копируем содержимое выходных директорий в директории Верстки
	ShareFoldersManager *shareFoldersManager = new ShareFoldersManager(imageStoragePatch, shareFolderPatch);
        shareFoldersManager->saveSession(filmContainer);

}


//Очистка выходных директорий
void ImageManager::clearOutFolders(){
	TStringList *workContent = new TStringList();

        getDirectoryContent(workDirectoryPatch, workContent);

        //Проверяем присутствуют-ли удаляемые файлы в хранилище?
        for(int ch=0; ch<workContent->Count; ch++){
        	//Есть-ли текущий файл в хранилище?
		if (!FileExists(imageStoragePatch+workContent->Strings[ch])){
                	ShowMessage("Файл ("+workContent->Strings[ch]+")  в хранилище отсутствует!");
                        return;
                }
        }
	deleteFiles(workDirectoryPatch, workContent);
}

//////////////Инициализация путей///////////////
void ImageManager::setImageStoragePatch(AnsiString inImageStoragePatch){
	imageStoragePatch = inImageStoragePatch;

        //Считываем файлы хранилища
        getDirectoryContent(imageStoragePatch, imageBaseContent);

        //Стираем расширения
        clearExtension(imageBaseContent);

        //В нижний регистр!
        listToLowerCase(imageBaseContent);
}

void ImageManager::setWorkDirectoryPatch(AnsiString inWorkDirectoryPatch){
	workDirectoryPatch = inWorkDirectoryPatch;
}

void ImageManager::setShareFolderPatch(AnsiString inShareFolderPatch){
	shareFolderPatch = inShareFolderPatch;
}
