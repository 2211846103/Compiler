#ifndef READ_FILE_H
#define READ_FILE_H

#include <stdio.h>
#include <stdlib.h>

char* read_file(char* path) {
    char * buffer = 0;
    long length;
    FILE * f = fopen (path, "r");

    if (!f) return NULL;

    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = (char*) malloc (length+1);
    if (buffer) {
        fread (buffer, 1, length, f);
    }
    fclose (f);

    buffer[length] = '\0';
    return buffer;
}

#endif