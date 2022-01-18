#include "movie.h"

/*
 * The file will contain the following column headers and max lengths:
 * Title [unknown], Year [4], Languages [(5 * 20) + 4 + 2], Rating Value [2].
 * The head of a Movie linked list is returned.
 */
struct Movie *createListFromFile(char *filename) {
    FILE *fp = fopen(filename, "r");
    struct Movie *head = NULL;
    struct Movie *curr = NULL;
    struct Movie *movie = NULL;
    int index = 0;
    int column = 0;
    int line = 0;
    const int SIZE = 255;
    char buffer[SIZE];

    for (char ch = fgetc(fp); ch != EOF; ch = fgetc(fp)) {
        buffer[index] = ch;
        index++;

        if ((ch == ',' || ch == '\n') && line > 0) {
            buffer[index - 1] = '\0';

            if (column == 0) {
                movie = malloc(sizeof(struct Movie));
                movie->next = NULL;
                if (head == NULL) {
                    head = movie;
                    curr = movie;
                } else {
                    curr->next = movie;
                    curr = movie;
                }
            }

            addData(movie, buffer, index, column);

            column++;
            index = 0;
        }

        if (ch == '\n') {
            line++;
            index = 0;
            column = 0;
        }
    }

    fclose(fp);

    return head;
}

struct Movie *createListHighestRatedMoviePerYear(struct Movie* source) {
    struct Movie *curr = source;
    struct Movie *temp = NULL;
    struct Movie *tempCurr = NULL;
    struct Movie *tempHead = NULL;
    struct Movie *head = NULL;
    int count = 0;
    int hasYearInList = 0;

    while (curr != NULL) {
        while (head != NULL && !hasYearInList) {
            if (*(head->year) == *(curr->year)) {
                if (*(head->ratingValue) < *(curr->ratingValue)) {
                    copyMovieReallocate(curr, head);
                }
                hasYearInList = 1;
            }
            head = head->next;
        }

        if (!hasYearInList) {
            temp = malloc(sizeof(struct Movie));
            temp->next = NULL;
            copyMovie(curr, temp);
            if (count == 0) {
                tempHead = temp;
                tempCurr = temp;
            } else {
                tempCurr->next = temp;
                tempCurr = temp;
            }
            count++;
        }
        curr = curr->next;
        head = tempHead;
        hasYearInList = 0;
    }

    return head;
}

void addData(struct Movie *movie, char *buffer, int length, int column) {
    switch (column) {
        case 0:
            addTitle(movie, buffer, length);
            break;
        case 1:
            addYear(movie, buffer, length);
            break;
        case 2:
            addLanguages(movie, buffer, length);
            break;
        case 3:
            addRatingValue(movie, buffer, length);
            break;
    }
}

void addTitle(struct Movie *movie, char *buffer, int length) {
    movie->title = malloc(sizeof(char) * length);
    for (int i = 0; i < length; i++) {
        *(movie->title + i) = buffer[i];
    }
}

void addYear(struct Movie *movie, char *buffer, int length) {
    movie->year = malloc(sizeof(int));
    sscanf(buffer, "%d", movie->year);
}

void addLanguages(struct Movie *movie, char *buffer, int length) {
    movie->languages = malloc(sizeof(char) * length);
    for (int i = 0; i < length; i++) {
        *(movie->languages + i) = buffer[i];
    }
}

void addRatingValue(struct Movie *movie, char *buffer, int length) {
    movie->ratingValue = malloc(sizeof(double));
    *(movie->ratingValue) = strtod(buffer, NULL);
}

void copyMovie(struct Movie *source, struct Movie *target) {
    target->year = malloc(sizeof(int));
    target->ratingValue = malloc(sizeof(double));
    target->title = malloc(sizeof(char) * (stringLength(source->title) + 1));
    target->languages = malloc(sizeof(char) * (stringLength(source->languages) + 1));
    *(target->year) = *(source->year);
    *(target->ratingValue) = *(source->ratingValue);
    for (int i = 0; i < stringLength(source->title); i++) {
        *(target->title + i) = *(source->title + i);
    }
    *(target->title + (stringLength(source->title))) = '\0';
    for (int i = 0; i < stringLength(source->languages); i++) {
        *(target->languages + i) = *(source->languages + i);
    }
    *(target->languages + (stringLength(source->languages))) = '\0';
}

void copyMovieReallocate(struct Movie *source, struct Movie *target) {
    *(target->ratingValue) = *(source->ratingValue);
    *(target->year) = *(source->year);

    target->title = realloc(target->title, (sizeof(char) * (stringLength(source->title) + 1)));
    for (int i = 0; i < stringLength(source->title); i++) {
        *(target->title + i) = *(source->title + i);
    }
    *(target->title + (stringLength(source->title))) = '\0';

    target->languages = realloc(target->languages, (sizeof(char) * (stringLength(source->languages) + 1)));
    for (int i = 0; i < stringLength(source->languages); i++) {
        *(target->languages + i) = *(source->languages + i);
    }
    *(target->languages + (stringLength(source->languages))) = '\0';
}

void readList(struct Movie *head) {
    struct Movie *curr = head;
    while (curr != NULL) {
        printf("%-50s ", curr->title);
        printf("%-10d ", *(curr->year));
        printf("%-10.1f ", *(curr->ratingValue));
        printf("%-100s ", curr->languages);
        printf("\n");
        curr = curr->next;
    }
}

void readListMoviesByYear(struct Movie *head, int year) {
    struct Movie *curr = head;
    int count = 0;
    char *noRecords = "No records were found for the specified year.\n";

    while (curr != NULL) {
        if (*(curr->year) == year) {
            count++;
            printf("%s\n", curr->title);
        }
        curr = curr->next;
    }

    if (count == 0) {
        printf("%s", noRecords);
    }
}

void readListMoviesByLanguage(struct Movie *head, char *language) {
    struct Movie *curr = head;
    int match = 0;
    int count = 0;
    char *noRecords = "\nNo records were found for the specified language.";

    while (curr != NULL) {
        for (int i = 0; i < stringLength(curr->languages); i++) {
            if (*(language + 0) == *(curr->languages + i)) {
                for (int j = 0; j < stringLength(language); j++) {
                    if (*(language + j) != *(curr->languages + i + j)) {
                        break;
                    }
                    if (j == (stringLength(language) - 1) &&\
                        (*(curr->languages + i + j + 1) == ';' ||\
                        *(curr->languages + i + j + 1) == ']')) {
                        match = 1;
                    }
                }
            }
            if (match) {
                printf("\n%-6d %s", *(curr->year), curr->title);
                count++;
                break;
            }
        }
        match = 0;
        curr = curr->next;
    }

    if (count == 0) {
        printf("%s", noRecords);
    }
}

void readListYearRatingValueTitle(struct Movie *head) {
    struct Movie *curr = head;
    while (curr != NULL) {
        printf("%-6d ", *(curr->year));
        printf("%-5.1f ", *(curr->ratingValue));
        printf("%-s ", curr->title);
        printf("\n");
        curr = curr->next;
    }
}

void freeList(struct Movie *head) {
    struct Movie *curr = head;
    struct Movie *temp = NULL;
    while (curr != NULL) {
        free(curr->title);
        free(curr->year);
        free(curr->languages);
        free(curr->ratingValue);
        temp = curr;
        curr = curr->next;
        free(temp);
    }
}