/**
 * @file files.c
 */

#include <stdio.h>

/**
 * Opens password file in read or write mode
 * @param mode 'r' for read, 'w' for write
 */
FILE *openFile(char *path, char mode) {
    FILE * fileptr;
    fileptr = fopen(path, mode);
    //check if file was found
    if(!fileptr) {
        fprintf(stderr, "Error: Can't access file.\n");
        exit(1);
    }
    return fileptr;
}

/**
 * Scans line from file stream passed in and returns the char pointer
 */
char *scanLine(FILE *fileptr) {
    if(fileptr == NULL) {
        return NULL;
    }
    int capacity = 5;
    int len = 0;
    char *line = (char*) malloc(capacity * sizeof(char));
    while((ch = fgetc(fileptr)) != '\n' && ch != EOF) {
        if(len >= capacity) {
            capacity *= 2;
            char *newline = (char *) malloc(capacity * sizeof(char));
            strcpy(newline, line);
            free(line);
            line = newLine;
        }
        line[len++] = ch;
    }
    line[len] = '\0';
    return line;
}