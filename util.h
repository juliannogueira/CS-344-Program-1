#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

int hasCommandLineArgument(char *argv[]);

int isValidFile(char *filename);

int isValidChoice(char ch);

int isValidChar(char ch);

int isValidDigit(char ch); 

void clearBuffer(char *buffer, int size);

int stringLength(char *string);

#endif