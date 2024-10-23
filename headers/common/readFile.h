#ifndef COMMON_READ_FILE
#define COMMON_READ_FILE

#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* path) {
    // Open file stream
    FILE* file = fopen(path, "r");
    if (!file) {
        perror("File Reading Failed");
        return NULL;
    }

    // Get the size of file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate buffer to hold contents
    char* buffer = (char*)malloc(file_size + 1);
    if (!buffer) {
        perror("Memory Allocation Failed");
        return NULL;
    }

    // Read file into buffer
    // And assign terminating character
    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0';

    // Close file and return contents
    fclose(file);
    return buffer;
}

#endif