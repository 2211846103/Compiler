#ifndef COMMON_READ_FILE
#define COMMON_READ_FILE

#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        perror("File Reading Failed");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(file_size + 1);
    if (!buffer) {
        perror("Memory Allocation Failed");
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0';

    fclose(file);
    return buffer;
}

#endif