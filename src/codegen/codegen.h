#ifndef CODEGEN_H
#define CODEGEN_H

#include "../ir/ir.h"
#include <stdio.h>

typedef struct {
  IRList *ir;
  FILE *output;
  int stack_size;
} CodeGen;

void codegen_init(CodeGen *cg, IRList *ir, FILE *output);
void codegen_emit(CodeGen *cg);
void codegen_free(CodeGen *cg);

#endif
