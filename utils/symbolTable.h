#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char* name;
} SymbolTableRow;

typedef struct {
    SymbolTableRow** rows;
    int capacity;
    int rowCount;
} SymbolTable;

SymbolTable* create_symbol_table() {
    SymbolTable* table = (SymbolTable*) malloc(sizeof(SymbolTable));
    table->capacity = 4;
    table->rowCount = 0;
    table->rows = (SymbolTableRow**) malloc(sizeof(SymbolTableRow*) * table->capacity);

    return table;
}

void free_symbol_table(SymbolTable* table) {
    for (int i = 0; i < table->rowCount; i++) {
        free(table->rows[i]->name);
        free(table->rows[i]);
    }
    free(table->rows);
    free(table);
}

void add_identifier(SymbolTable* table, int id, char* name) {
    SymbolTableRow* row = (SymbolTableRow*) malloc(sizeof(SymbolTableRow));
    row->id = id;
    row->name = (char*) malloc(strlen(name) + 1);
    strcpy(row->name, name);

    if (table->rowCount >= table->capacity) {
        table->capacity *= 2;
        table->rows = (SymbolTableRow**) realloc(table->rows, sizeof(SymbolTableRow*) * table->capacity);
    }

    table->rows[table->rowCount++] = row;
}

void print_symbol_table(SymbolTable* table) {
    for (int i = 0; i < table->rowCount; i++) {
        SymbolTableRow* row = table->rows[i];
        printf("ID: %i  |  Name: %s\n", row->id, row->name);
    }
}

#endif