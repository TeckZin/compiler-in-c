#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>

void analyzer_init(Analyzer *a, SymTable *table) {
  a->table = table;
  a->err_flag = false;
}

void analyze_program(Analyzer *a, ASTNode *node) {
  for (int i = 0; i < node->program.statements.count; i++) {
    analyze_statement(a, node->program.statements.items[i]);
  }
}

void analyze_statement(Analyzer *a, ASTNode *node) {
  if (node == NULL)
    return;
  switch (node->kind) {
  case NODE_VAR_DECL:
    analyze_var_decl(a, node);
    break;
  case NODE_ASSIGN:
    analyze_assign(a, node);
    break;
  default:
    analyze_error(a, "unexpected node in statement");
    break;
  }
}

void analyze_var_decl(Analyzer *a, ASTNode *node) {
  if (!symtable_add(a->table, node->var_decl.name)) {
    analyze_error(a, "variable already declared");
  }
  analyze_expression(a, node->var_decl.value);
}

void analyze_assign(Analyzer *a, ASTNode *node) {
  if (!symtable_lookup(a->table, node->assign.name)) {
    analyze_error(a, "variable not declared");
  }
  analyze_expression(a, node->assign.value);
}

void analyze_expression(Analyzer *a, ASTNode *node) {
  if (node == NULL)
    return;
  switch (node->kind) {
  case NODE_BINOP:
    analyze_binop(a, node);
    break;
  case NODE_INT_LIT:
    analyze_int_lit(a, node);
    break;
  case NODE_IDENT:
    analyze_ident(a, node);
    break;
  default:
    analyze_error(a, "unexpected node in expression");
    break;
  }
}

void analyze_binop(Analyzer *a, ASTNode *node) {
  analyze_expression(a, node->binop.left);
  analyze_expression(a, node->binop.right);
}

void analyze_int_lit(Analyzer *a, ASTNode *node) {
  // nothing to check
}

void analyze_ident(Analyzer *a, ASTNode *node) {
  if (!symtable_lookup(a->table, node->ident.name)) {
    analyze_error(a, "undeclared variable");
  }
}

void analyze_error(Analyzer *a, const char *msg) {
  a->err_flag = true;
  fprintf(stderr, "semantic error: %s\n", msg);
}
