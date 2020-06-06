#ifndef OutDirectoryManagerH
#define OutDirectoryManagerH
#include <vcl.h>
#include "WeekDay.h"
#include "FilmContainer.h"

class ImageManager{
public:
	ImageManager(FilmContainer *inFilmContainer);

        //Возвращает полный путь к файлу
        //Ищет в выходных директориях, затем в хранилище изображений
        //Если ни чего не находится, то тогда возвращает NULL
        AnsiString getPatch(AnsiString fileName);

        //Возвращает список файлов в папке базы изображений(без рсширений)
        TStringList *getBaseImageContent();

        //Файлы рабочей директории
        TStringList *getWorkFolderContent();

        //Переименовывает файл с именем oldName
        void renameFile(AnsiString oldName, AnsiString newName);


        //////////////////////СЕССИЯ////////////////////////////
        //Завершение сессии, копирование файлов
        void terminateSession();

        //Очистка выходных директорий
        void clearOutFolders();
		
		
        //////////////Инициализация путей///////////////
        void setImageStoragePatch(AnsiString inImageStoragePatch);

        void setWorkDirectoryPatch(AnsiString inWorkDirectoryPatch);

        void setShareFolderPatch(AnsiString inShareFolderPatch);
private:
	//Путь к каталогу с картинками
	AnsiString imageStoragePatch;

	//Рабочий каталог
	AnsiString workDirectoryPatch;

	//Каталог на шаре
	AnsiString shareFolderPatch;


	//Список файлов в директории - хранилищи изображений, (без расширений)
	TStringList *imageBaseContent;

	//Контейнер
	FilmContainer *filmContainer;

	//Ищет фаил fileName в выходных директориях и в базе
	//возвращает путь к папке в которй находится искомый файл,
	//если не находит возвращает NULL
	AnsiString searchFileInDirectories(AnsiString fileName);

	//Возвращает лист в котором содержатся файлы inList - без расширения
	void clearExtension(TStringList *inList);
	AnsiString getWithoutExtension(AnsiString name);
	AnsiString getExtension(AnsiString patch, AnsiString file);

	void listToLowerCase(TStringList *inList);

	///////////////////////СЕССИЯ///////////////////////////////////////////
	//В соответствии с типом фильма(для не художественных), создаётся метка в виде пустого файла в базе изображений с именем фильма и его типом
	//Это позволяет найти этот злополучный фильм в следующий раз в базе
	void createBadTypesFilmLabels();

	//Проверяет список файлов folderContent на наличие файлов jpg - необработанных фильмов
	bool checkNotCorrectFilms(TStringList *folderContent);

	//Проверяет на name на наличие расширения Tif
	bool fileIsCorrect(AnsiString name);

	//проверяем содержимое выходных директорий
	bool DirectoryContentIsOk();

	//копирование содержимого директорий выхода в хранилище файлов
	void saveDirectoryContentInStore();

};

#endif