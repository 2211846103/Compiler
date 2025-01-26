#include "compiler.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: compiler <sourceFile>\n");
        return 1;
    }

    char* filename = argv[1];
    char* sourceCode = read_file(filename);

    int count;
    Token** tokens = tokenize(sourceCode, &count);

    for (int i = 0; i < count; i++) {
        print_token(tokens[i]);
        printf(" ");
    }
    printf("\n");

    //free_tokens(tokens, count);
    free(sourceCode);

    return 0;
}