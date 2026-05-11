#ifndef IR_GEN_H
#define IR_GEN_H

#include "../ast/ast.h"
#include "ir.h"

typedef struct {
  IRList list;
  int reg_counter;
} IRGen;

void irgen_init(IRGen *gen);

void irgen_program(IRGen *gen, ASTNode *node);

void irgen_statement(IRGen *gen, ASTNode *node);

void irgen_var_decl(IRGen *gen, ASTNode *node);

void irgen_assign(IRGen *gen, ASTNode *node);

int irgen_expression(IRGen *gen, ASTNode *node);

int irgen_binop(IRGen *gen, ASTNode *node);

int irgen_int_lit(IRGen *gen, ASTNode *node);

int irgen_ident(IRGen *gen, ASTNode *node);

#endif
