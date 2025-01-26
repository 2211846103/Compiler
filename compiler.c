#include "compiler.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: compiler <sourceFile>\n");
        return 1;
    }

    char* filename = argv[1];
    char* sourceCode = read_file(filename);

    SymbolTable* symbolTable = create_symbol_table();

    int count;
    Token** tokens = tokenize(sourceCode, &count, symbolTable);

    print_tokens(tokens, count);
    print_symbol_table(symbolTable);

    free_symbol_table(symbolTable);
    free_tokens(tokens, count);
    free(sourceCode);

    return 0;
}