#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

/*
 * The util file contains helper functions to be used by main, movie, and menu.
 * 
 * There are functions to check for command line arguments, valid files, and
 * input.
 * 
 * There is also a function to get the number of characters in a
 * null-terminated string.
 * 
 * Function comments are included util.c.
 */

int hasCommandLineArgument(char *argv[]);

int isValidFile(char *filename);

int isValidChoice(char ch);

int isValidChar(char ch);

int isValidDigit(char ch); 

void clearBuffer(char *buffer, int size);

int stringLength(char *string);

#endif