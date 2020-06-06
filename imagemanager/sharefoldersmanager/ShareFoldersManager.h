#ifndef ShareFoldersManagerH
#define ShareFoldersManagerH
#include <vcl.h>
#include "FilmContainer.h"
#include "Film.h"


class ShareFoldersManager{
public:
	ShareFoldersManager(AnsiString inStorePatch, AnsiString inShareFolderPatch);
	
	//запускает процесс сохранения изображений сессии в выходных директориях
	void saveSession(FilmContainer *filmContainer);
private:

	AnsiString shareFolderPatch;

	AnsiString storePatch;

	//выходные директрории сответствующие дням недели
	TStringList *weekDayFolders;
	
	//Копирование файла содержащегося в film в папку вёрстки
	void copyContentImageToShare(Film *film);
	
	//Генерация пути к файлу, выбор папки дня недели
	AnsiString generateSharePatch(Film *film);
	
	//Генерация нового имени для вёрстки по заданному шаблону
	AnsiString generateFileName(Film *film);

        //очистка директории верстки
        void clearShareDirectories();
};

#endif