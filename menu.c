#include "menu.h"

void runMenu(struct Movie *head) {
    int runProgram = 1;
    const int SIZE = 255;
    char buffer[SIZE];
    char choice;
    char *header =         "------------------------ Movies: Main Menu -------------------------\n";
    char *headerLine =     "--------------------------------------------------------------------\n";
    char *option1 =        "1) Show movies released in a specified year\n";
    char *option2 =        "2) Show highest rated movie for each year\n";
    char *option3 =        "3) Show the title and year of movies in a specified language\n";
    char *option4 =        "4) Quit the program\n";
    char *prompt =         "\nEnter a valid menu option: ";
    char *invalidChoice =  "\nAn invalid menu option was entered.\n";

    while (runProgram) {
        printf("\n\n%s", headerLine);
        printf("%s", header);
        printf("%s", headerLine);
        printf("%s", option1);
        printf("%s", option2);
        printf("%s", option3);
        printf("%s", option4);
        printf("%s", prompt);

        fgets(buffer, SIZE, stdin);
        choice = buffer[0];

        switch (choice) {
            case '1':
                getMoviesByYear(head);
                break;
            case '2':
                getHighestRatedMoviePerYear(head);
                break;
            case '3':
                getMoviesByLanguage(head);
                break;
            case '4':
                runProgram = 0;
                printf("\n\n");
                break;
            default:
                printf("%s", invalidChoice);
                break;
        }
    }
}

void getMoviesByYear(struct Movie *head) {
    const int SIZE = 255;
    const int SIZE_YEAR = 4;
    int year = 0;
    char buffer[SIZE];
    char choice[SIZE_YEAR + 1];
    char *header =         "-------------- Movies: Released in a Specified Year ----------------\n";
    char *headerLine =     "--------------------------------------------------------------------\n";
    char *prompt =         "\nEnter the year: ";

    printf("\n\n%s", headerLine);
    printf("%s", header);
    printf("%s", headerLine);
    printf("%s", prompt);
    
    fgets(buffer, SIZE, stdin);
    
    for (int i = 0; i < SIZE_YEAR; i++) {
        if (isValidDigit(buffer[i])) {
            choice[i] = buffer[i];
        } else {
            choice[i] = '\0';
        }
    }
    
    choice[SIZE_YEAR] = '\0';

    sscanf(choice, "%d", &year);

    printf("\n");

    readListMoviesByYear(head, year);
}

void getHighestRatedMoviePerYear(struct Movie *head) {
    struct Movie *highestRatedList = NULL;
    char *header =         "----------------- Movies: Highest Rated Per Year -------------------\n";
    char *headerLine =     "--------------------------------------------------------------------\n";

    printf("\n\n%s", headerLine);
    printf("%s", header);
    printf("%s", headerLine);

    highestRatedList = createListHighestRatedMoviePerYear(head);

    printf("\n");

    readListYearRatingValueTitle(highestRatedList);

    freeList(highestRatedList);
}

void getMoviesByLanguage(struct Movie *head) {
    const int SIZE = 255;
    const int SIZE_LANGUAGE = 20;
    char *header =         "----------- Movies: Available in a Specified Language --------------\n";
    char *headerLine =     "--------------------------------------------------------------------\n";
    char *prompt =         "\nEnter the language: ";
    char buffer[SIZE];
    char language[SIZE_LANGUAGE + 1];

    for (int i = 0; i < SIZE_LANGUAGE; i++) {
        language[i] = '\0';
    }

    printf("\n\n%s", headerLine);
    printf("%s", header);
    printf("%s", headerLine);
    printf("%s", prompt);

    fgets(buffer, SIZE, stdin);

    for (int i = 0; i < SIZE_LANGUAGE; i++) {
        if (buffer[i] == '\n') {
            break;
        }

        language[i] = buffer[i];
    }

    language[SIZE_LANGUAGE] = '\0';

    readListMoviesByLanguage(head, language);

    printf("\n");
}