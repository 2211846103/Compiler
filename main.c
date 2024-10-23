#include "main.h"

int main() {
    char* contents = read_file("test.txt");
    printf("%s\n", contents);

    free(contents);

    return 0;
}