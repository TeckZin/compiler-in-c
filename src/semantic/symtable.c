#include "symtable.h"
#include <stdlib.h>
#include <string.h>

void symtable_init(SymTable *t) {
  t->names = NULL;
  t->count = 0;
  t->capacity = 0;
}
bool symtable_add(SymTable *t, const char *name) {
  if (symtable_lookup(t, name))
    return false;
  if (t->count == t->capacity) {
    if (t->capacity == 0) {
      t->names = malloc(sizeof(char *) * 8);
      t->capacity = 8;
    } else {
      t->capacity = t->capacity * 2;
      t->names = realloc(t->names, sizeof(char *) * t->capacity);
    }
  }

  t->names[t->count] = strdup(name);
  t->count++;

  return true;
}
bool symtable_lookup(SymTable *t, const char *name) {
  for (int i = 0; i < t->count; i++) {
    if (strcmp(name, t->names[i]) == 0) {
      return true;
    }
  }
  return false;
}
void symtable_free(SymTable *t) {
  for (int i = 0; i < t->count; i++) {
    free(t->names[i]);
  }
  free(t->names);
}
