#include <stdio.h>

#include "util.h"
#include "movie.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    struct Movie *head;

    if (!hasCommandLineArgument(argv)) {
        // Inform the user if a command line argument was not passed.
        printf("A file was not passed.\n");
        return 1;
    }

    if (!isValidFile(*(argv + 1))) {
        // Inform the user if an invalid filename was passed.
        printf("An invalid filename was passed.\n");
        return 1;
    }

    head = createListFromFile(*(argv + 1));

    runMenu(head);

    freeList(head);

    return 0;
}