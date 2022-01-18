#ifndef MENU_H
#define MENU_H

#include "movie.h"

void runMenu(struct Movie *head);

void getMoviesByYear(struct Movie *head);

void getHighestRatedMoviePerYear(struct Movie *head);

void getMoviesByLanguage(struct Movie *head);

#endif