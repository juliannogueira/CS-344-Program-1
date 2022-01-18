#include <stdio.h>

#include "util.h"
#include "movie.h"
#include "menu.h"

/*
 * Check if a command line argument was passed. If it was passed, continue.
 * Otherwise, inform the user and quit the program.
 * 
 * Check if the passed command line argument is a valid file. The isValidFile()
 * function will attempt to open the file. If it can be opened, continue.
 * Otherwise, inform the user and quit the program.
 * 
 * Create a linked list from the passed file, such that the head of the list is
 * returned to the main program.
 * 
 * Run the menu, passing the head of the linked list for input.
 * 
 * Free memory after using the linked list.
 */
int main(int argc, char *argv[]) {
    struct Movie *head;

    if (!hasCommandLineArgument(argv)) {
        printf("A file was not passed.\n");
        return 1;
    }

    if (!isValidFile(*(argv + 1))) {
        printf("An invalid filename was passed.\n");
        return 1;
    }

    head = createListFromFile(*(argv + 1));

    runMenu(head);

    freeList(head);

    return 0;
}