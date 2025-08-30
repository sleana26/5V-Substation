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

char *scanLine(FILE *fileptr, char *line) {
    fgets(line, size(line), fileptr);
}