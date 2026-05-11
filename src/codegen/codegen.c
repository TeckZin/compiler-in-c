#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>

void codegen_init(CodeGen *cg, IRList *ir, FILE *output) {
  if (ir == NULL || output == NULL)
    return;
  cg = malloc(sizeof(CodeGen *));
  cg->ir = ir;
  cg->output = output;
}

void codegen_emit(CodeGen *cg) {

  IRInstr **items = cg->ir->items;
  for (int i = 0; i < cg->ir->count; i++) {
    IRInstr *isntr = items[i];
    ir_print_to_asm(isntr, cg->output);
  }
}
void codegen_free(CodeGen *cg) {}
