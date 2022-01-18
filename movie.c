#include "movie.h"

/*
 * The file will contain the following column headers and max lengths:
 * Title [255], Year [4], Languages [(5 * 20) + 4 + 2], Rating Value [2].
 * 
 * Each character in the file is checked and stored in a buffer, until the EOF
 * is reached.
 * 
 * The first line of the file is read, but no processing takes place.
 * 
 * The index, column, and line are tracked and reset throughout the function.
 * 
 * When a ',' or '\n' is encountered, it triggers the data in the buffer to be
 * written to a movie struct. If the column number equals 0 at this trigger, a
 * new movie struct will be created first and linked accordingly.
 * 
 * All data from the file will be read into a char buffer. The buffer will be
 * manually null terminated. Once the data is assigned to a movie struct
 * attribute, the data will be converted to the respective data type.
 * 
 * The column number is reset when a '\n' is encountered. This is what
 * determines which attribute to write the data too.
 * 
 * After the file is processed, if the column number is not equal to 0, then
 * the last character was not a new line. Therefore, data is still in the
 * buffer, and it needs to be written to the current column.
 * 
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
    int recordCount = 0;
    const int SIZE = 255;
    char buffer[SIZE];

    for (char ch = fgetc(fp); ch != EOF; ch = fgetc(fp)) {
        buffer[index] = ch;
        index++;

        if ((ch == ',' || ch == '\n') && line > 0) {
            buffer[index - 1] = '\0';

            if (column == 0) {
                recordCount++;
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

    if (column != 0) {
        addData(movie, buffer, index, column);
    }

    printf("Processed file %s and parsed data for %d movies", filename, recordCount);

    fclose(fp);

    return head;
}

/*
 * Create a linked list containing the highest rated movie per year from a
 * passed linked list.
 * 
 * The passed list will be iterated through. If the year of the current movie
 * does not exist in the new list, the movie will be added to the new list.
 * 
 * If the year does exist in the new list, then the rating will be compared to
 * the current movie rating. If the current rating is higher, the movie with
 * the higher rating will replace the movie with the lower rating.
 * 
 * The new list is returned, such that only one movie per year exists in the
 * list, where this movie contains the highest rating. 
 */
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

/*
 * Add data to the passed movie struct.
 * 
 * The column number will determine which attribute to write the data to, such
 * that the appropriate helper function will be called depending on the column
 * number.
 */
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

/*
 * Add a title to the movie struct.
 * 
 * Iterate through the buffer and assign each character to the char array. The
 * null terminator is included in the buffer.
 */
void addTitle(struct Movie *movie, char *buffer, int length) {
    movie->title = malloc(sizeof(char) * length);
    for (int i = 0; i < length; i++) {
        *(movie->title + i) = buffer[i];
    }
}

/*
 * Add a year to the movie struct.
 * 
 * The buffer is parsed for an integer, and the integer is assigned to the
 * year.
 */
void addYear(struct Movie *movie, char *buffer, int length) {
    movie->year = malloc(sizeof(int));
    sscanf(buffer, "%d", movie->year);
}

/*
 * Add the language(s) to the movie struct.
 * 
 * The language(s) are added in the same manner as the title, such that each
 * character is added to the char array, and the null terminator is already
 * included in the buffer.
 */
void addLanguages(struct Movie *movie, char *buffer, int length) {
    movie->languages = malloc(sizeof(char) * length);
    for (int i = 0; i < length; i++) {
        *(movie->languages + i) = buffer[i];
    }
}

/*
 * Add a rating value to the movie struct.
 * 
 * The buffer is parsed for a double, and the double is assigned to the year.
 */
void addRatingValue(struct Movie *movie, char *buffer, int length) {
    movie->ratingValue = malloc(sizeof(double));
    *(movie->ratingValue) = strtod(buffer, NULL);
}

/*
 * Copy the contents of a source movie struct into a target movie struct.
 *
 * Memory is allocated for the target movie struct.
 * 
 * The year and rating value can be easily assigned.
 * 
 * The title and language(s) must be iterated through, and the null terminators
 * are added.
 */
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

/*
 * Copy the contents of a source movie struct into a target movie struct.
 * 
 * Memory is reallocated in this function, such that the target movie struct
 * was initialized prior to the function call, and the contents are only being
 * updated.
 * 
 * The title and languages attributes must be reallocated because the size
 * could be different, whereas the year and ratingValue do not need to be
 * reallocated, as the size is constant.
 */
void copyMovieReallocate(struct Movie *source, struct Movie *target) {
    *(target->year) = *(source->year);
    *(target->ratingValue) = *(source->ratingValue);

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

/*
 * Read and print the contents of a movies struct linked list.
 *
 * The output is formatted.
 */
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

/*
 * Read and print the contents of a movies struct linked list by year.
 *
 * The year is passed, and only movies with a year equal to the passed year
 * will be printed.
 */
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

/*
 * Read and print the contents of a movie struct linked list by language.
 * 
 * The language is passed, and only movies containing that language string will
 * be printed.
 * 
 * The function scans every movie languages string for the first character of
 * the passed language.
 * 
 * If the first letter is encountered, the position of the movie languages
 * string will continue to be iterated through for as many characters are in
 * the passed language.
 * 
 * If all characters in the passed language are also in the movie languages
 * string, and the next character is either a ';' or ']' that indicates the
 * delineation of an item, the movie data will be printed.
 */
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

/*
 * Read and print the contents of movie struct linked list.
 *
 * Only print the year, rating value, and title.
 */
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

/*
 * Free memory of all movie structs and respective data elements of a passed
 * movie struct linked list.
 */
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