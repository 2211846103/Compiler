#ifndef PRINT_TOKEN_H
#define PRINT_TOKEN_H

#include <stdio.h>

#include "../lexical_analysis/scanner.h"

void print_token(Token* token) {
    switch (token->name) {
        case CONST:
            printf("<CONST, %f>", token->value.floatValue);
            break;
        case ID:
            printf("<ID, %i>", token->value.intValue);
            break;
        case OP:
            printf("<OP, %c>", token->value.charValue);
            break;
        case LITER:
            printf("<LIT, %s>", token->value.strValue);
            break;
        case PUNC:
            printf("<PUNC, %c>", token->value.charValue);
            break;
    }
}

#endif