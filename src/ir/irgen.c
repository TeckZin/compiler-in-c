#include "irgen.h"
#include "ir.h"

#include <complex>
#include <stdio.h>
#include <stdlib.h>

void irgen_init(IRGen *gen) {
  gen->list.items = NULL;
  gen->list.count = 0;
  gen->list.capacity = 0;
  gen->reg_counter = 0;
}

void irgen_program(IRGen *gen, ASTNode *node) {
  for (int i = 0; i < node->program.statements.count; i++) {
    irgen_statement(gen, node->program.statements.items[i]);
  }
}

void irgen_statement(IRGen *gen, ASTNode *node) {
  if (node == NULL)
    return;
  switch (node->kind) {
  case NODE_VAR_DECL:
    irgen_var_decl(gen, node);
    break;
  case NODE_ASSIGN:
    irgen_assign(gen, node);
    break;
  default:
    break;
  }
}

void irgen_var_decl(IRGen *gen, ASTNode *node) {
  int value = irgen_expression(gen, node->var_decl.value);
  gen->reg_counter += value;
}

void irgen_assign(IRGen *gen, ASTNode *node) {
  int value = irgen_expression(gen, node->assign.value);
  gen->reg_counter += value;
}

int irgen_expression(IRGen *gen, ASTNode *node) {
  if (node == NULL)
    return -1;
  switch (node->kind) {
  case NODE_BINOP:
    return irgen_binop(gen, node);
  case NODE_INT_LIT:
    return irgen_int_lit(gen, node);
  case NODE_IDENT:
    return irgen_ident(gen, node);
  default:
    return -1;
  }
}

int irgen_binop(IRGen *gen, ASTNode *node) {
  int value = 0;
  value += irgen_expression(gen, node->binop.left);
  value += irgen_expression(gen, node->binop.right);
  return value;
}

int irgen_int_lit(IRGen *gen, ASTNode *node) { return 0; }

int irgen_ident(IRGen *gen, ASTNode *node) { return 0; }
