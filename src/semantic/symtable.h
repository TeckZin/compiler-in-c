#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdbool.h>

typedef struct {
  char **names;
  int count;
  int capacity;
} SymTable;

void symtable_init(SymTable *t);
bool symtable_add(SymTable *t, const char *name);
bool symtable_lookup(SymTable *t, const char *name);
void symtable_free(SymTable *t);

#endif
