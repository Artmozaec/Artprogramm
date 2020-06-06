#ifndef FilmContainerUtilitesH
#define FilmContainerUtilitesH
#include <vcl.h>
#include "FilmContainer.h"
#include "Film.h"
#include "WeekDay.h"

Film *searchFilmName(FilmContainer *container, AnsiString fileName);

Film *getFilmToImageFile(AnsiString imageFileName, FilmContainer *container);

int getFilmsInDay(WeekDay weekDay, FilmContainer *container);

int getImagesInDay(WeekDay weekDay, FilmContainer *container);

bool existFilm(Film *film, FilmContainer *container);
#endif