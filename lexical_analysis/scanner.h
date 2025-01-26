#ifndef SCANNER_H
#define SCANNER_H

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../utils/symbolTable.h"

static const char* KEYWORDS[] = {"if", "let", "print"};

typedef enum {
    CONST, ID, OP, PUNC, LITER, INVALID, KEYWORD
} TokenName;

typedef union {
    int intValue;
    float floatValue;
    char* strValue;
    char charValue;
} TokenValue;

typedef struct {
    TokenName name;
    TokenValue value;
} Token;

static int ID_COUNTER = 0;

static int transition(int current, char input) {
    switch (current) {
        case 0:
            if (isalpha(input) || input == '_') return 1;
            if (isdigit(input)) return 2;
            if (input == '"') return 3;
            if (input == '\'') return 4;
            if (
                input == '(' ||
                input == ')' ||
                input == '{' ||
                input == '}'
            ) return 5;
            if (
                input == '=' ||
                input == '+' ||
                input == '-' ||
                input == '*' ||
                input == '/'
            ) return 6;
            else return 11;
        case 1:
            if (isalnum(input) || input == '_') return 1;
            else return 11;
        case 2:
            if (isdigit(input)) return 2;
            if (input == '.') return 7;
            else return 11;
        case 3:
            if (input == '"') return 8;
            else return 3;
        case 4:
            if (input == '\'') return 9;
            else return 4;
        case 5:
            return 11;
        case 6:
            return 11;
        case 7:
            if (isdigit(input)) return 10;
            else return 11;
        case 8:
            return 11;
        case 9:
            return 11;
        case 10:
            if (isdigit(input)) return 10;
            else return 11;
        case 11:
            return 11;
    }
}

static TokenName check_keywords(char* lexeme) {
    int numKeywords = sizeof(KEYWORDS) / sizeof(const char*);
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(lexeme, KEYWORDS[i]) == 0) {
            return KEYWORD;  // It's a keyword
        }
    }
    return ID;
}

static TokenName get_name(int state, char* lexeme) {
    switch (state) {
        case 1:
            return check_keywords(lexeme);
        case 2:
            return CONST;
        case 5:
            return PUNC;
        case 6:
            return OP;
        case 8:
            return LITER;
        case 9:
            return LITER;
        case 10:
            return CONST;
        default:
            return INVALID;
    }
}

static TokenValue get_value(TokenName name, char* input) {
    TokenValue value;
    if (name == ID) value.intValue = ID_COUNTER++;
    else if (name == CONST) value.floatValue = atof(input);
    else if (name == LITER || name == KEYWORD) {
        value.strValue = (char*) malloc(strlen(input) + 1);
        strcpy(value.strValue, input);
    }
    else if (name == PUNC || name == OP) value.charValue = input[0];

    return value;
}

static void add_token(Token*** list, int* capacity, int* count, int state, char* lexeme, SymbolTable* table) {
    Token* token = (Token*) malloc (sizeof(Token));
    token->name = get_name(state, lexeme);
    token->value = get_value(token->name, lexeme);
    if (token->name == ID) add_identifier(table, token->value.intValue, lexeme);


    if (*count >= *capacity) {
        *capacity *= 2;
        *list = (Token**) realloc(*list, sizeof(Token*) * (*capacity));
    }

    (*list)[*count] = token;
    (*count)++;
}

static char* get_lexeme(char* str, int start, int index) {
    int length = index - start;
    char* lexeme = (char*) malloc(length + 1);
    strncpy(lexeme, str + start, length);
    lexeme[length] = '\0';

    return lexeme;
}

static void print_token(Token* token) {
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
            printf("<LITERAL, %s>", token->value.strValue);
            break;
        case PUNC:
            printf("<PUNCT, %c>", token->value.charValue);
            break;
        case KEYWORD:
            printf("<KEYWORD, %s>", token->value.strValue);
            break;
    }
}

void print_tokens(Token** tokens, int count) {
    for (int i = 0; i < count; i++) {
        print_token(tokens[i]);
        printf(" ");
    }
    printf("\n");
}

void free_tokens(Token** tokens, int count) {
    for (int i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

Token** tokenize(char* str, int* outCount, SymbolTable* symbolTable) {
    Token** result = (Token**) malloc(sizeof(Token*));
    int count = 0;
    int capacity = 1;
    int state = 0;
    int start = 0;
    int i = 0;

    for (; str[i] != '\0'; i++) {
        char input = str[i];

        int temp = transition(state, input);
        if (temp != 11) {
            state = temp;
            continue;
        }

        char* lexeme = get_lexeme(str, start, i);
        add_token(&result, &capacity, &count, state, lexeme, symbolTable);
        free(lexeme);

        state = transition(0, input);
        start = i;
    }

    char* lexeme = get_lexeme(str, start, i);
    add_token(&result, &capacity, &count, state, lexeme, symbolTable);
    free(lexeme);

    *outCount = count;
    return result;
}

#endif