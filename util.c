#include "util.h"

/*
 * Check if a command line argument was passed.
 */
int hasCommandLineArgument(char *argv[]) {
    if (*(argv + 1) != NULL) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * Check if the passed file can be opened.
 */
int isValidFile(char *filename) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp != NULL) {
        fclose(fp);
        return 1;
    } else {
        return 0;
    }
}

/*
 * Check if the character is a valid choice.
 */
int isValidChoice(char ch) {
    char charList[98] = {'1', '2', '3', '4'};
    for (int i = 0; i < 4; i++) {
        if (ch == charList[i]) {
            return 1;
        }
    }
    return 0;
}

/* 
 * Check if a character is printable.
 */
int isValidChar(char ch) {
    char charList[98] = {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+',
                    ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7',
                    '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C',
                    'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[',
                    '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f',
                    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~',
                    ' ', '\n', '\t', '\r'};
    for (int i = 0; i < 98; i++) {
        if (ch == charList[i]) {
            return 1;
        }
    }
    return 0;
}

/*
 * Check if the character is a number.
 */
int isValidDigit(char ch) {
    char charList[98] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < 10; i++) {
        if (ch == charList[i]) {
            return 1;
        }
    }
    return 0;
}

/*
 * Clear the content of a buffer.
 */
void clearBuffer(char *buffer, int size) {
    for (int i = 0; i < size; i++) {
        buffer[i] = '\0';
    }
}

/*
 * Get the size of a string.
 */
int stringLength(char *string) {
    int i = 0;
    while (string[i] != '\0') {
        i++;
    }
    return i;
}