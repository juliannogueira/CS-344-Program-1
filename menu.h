#ifndef MENU_H
#define MENU_H

#include "movie.h"

/*
 * The menu file contains functions to run a menu for movie data.
 *
 * The user can get movie data filtered by year and language.
 * 
 * The user can get a list of highest rated movies per year.
 * 
 * Function comments are included in menu.c.
 */

void runMenu(struct Movie *head);

void getMoviesByYear(struct Movie *head);

void getHighestRatedMoviePerYear(struct Movie *head);

void getMoviesByLanguage(struct Movie *head);

#endif