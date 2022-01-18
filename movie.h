#ifndef MOVIE_H
#define MOVIE_H

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

/*
 * The movie file contains functions to create a linked list from a .csv file,
 * as well as from an existing movie linked list.
 * 
 * Functions are available to read and print the linked list, with or without
 * filtering options.
 * 
 * Memory can be deallocated by passing a movie linked list to freeList().
 * 
 * Function comments are included in movie.c.
 */

struct Movie {
    char *title;
    int *year;
    char *languages;
    double *ratingValue;
    struct Movie *next;
};

struct Movie *createListFromFile(char *filename);

struct Movie *createListHighestRatedMoviePerYear(struct Movie* source);

void addData(struct Movie *movie, char *buffer, int length, int column);

void addTitle(struct Movie *movie, char *buffer, int length);

void addYear(struct Movie *movie, char *buffer, int length);

void addLanguages(struct Movie *movie, char *buffer, int length);

void addRatingValue(struct Movie *movie, char *buffer, int length);

void copyMovie(struct Movie *source, struct Movie *target);

void copyMovieReallocate(struct Movie *source, struct Movie *target);

void readList(struct Movie *head);

void readListMoviesByYear(struct Movie *head, int year);

void readListMoviesByLanguage(struct Movie *head, char *language);

void readListYearRatingValueTitle(struct Movie *head);

void freeList(struct Movie *head);

#endif