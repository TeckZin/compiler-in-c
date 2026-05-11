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
  fprintf(cg->output, "section .text\n");
  fprintf(cg->output, "global main\n");
  fprintf(cg->output, "main:\n");
  fprintf(cg->output, "    push rbp\n");
  fprintf(cg->output, "    mov rbp, rsp\n");
  fprintf(cg->output, "    sub rsp, 256\n");

  for (int i = 0; i < cg->ir->count; i++) {
    IRInstr *instr = cg->ir->items[i];
    ir_print_to_asm(instr, cg->output);
  }

  fprintf(cg->output, "    mov rax, 0\n");
  fprintf(cg->output, "    leave\n");
  fprintf(cg->output, "    ret\n");
}
void codegen_free(CodeGen *cg) {}
