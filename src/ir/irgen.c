#include "irgen.h"
#include "ir.h"

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
  ir_list_add(&gen->list,
              ir_new_instr(IR_MOV, -(node->var_decl.name[0]), value, 0));
}

void irgen_assign(IRGen *gen, ASTNode *node) {
  int value = irgen_expression(gen, node->assign.value);
  ir_list_add(&gen->list,
              ir_new_instr(IR_MOV, -(node->assign.name[0]), value, 0));
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
  int left = irgen_expression(gen, node->binop.left);
  int right = irgen_expression(gen, node->binop.right);
  int dest = gen->reg_counter++;
  IROp op;
  switch (node->binop.op) {
  case TOKEN_PLUS:
    op = IR_ADD;
    break;
  case TOKEN_MINUS:
    op = IR_SUB;
    break;
  case TOKEN_DIVIDE:
    op = IR_DIV;
    break;
  case TOKEN_MULTIPLY:
    op = IR_MUL;
    break;
  default:
    op = IR_ADD;
    break;
  }

  ir_list_add(&gen->list, ir_new_instr(op, dest, left, right));

  return dest;
}

int irgen_int_lit(IRGen *gen, ASTNode *node) {
  int dest = gen->reg_counter++;
  ir_list_add(&gen->list, ir_new_instr(IR_MOV, dest, node->int_lit.value, 0));
  return dest;
}

int irgen_ident(IRGen *gen, ASTNode *node) {
  int dest = gen->reg_counter++;
  ir_list_add(&gen->list,
              ir_new_instr(IR_MOV, dest, -(node->ident.name[0]), 0));
  return dest;
}
