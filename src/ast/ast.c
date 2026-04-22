#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *ast_new_program(void) {

  ASTNode *node = malloc(sizeof(ASTNode));
  node->kind = NODE_PROGRAM;

  node->program.statements.capacity = 0;
  node->program.statements.count = 0;
  node->program.statements.items = NULL;

  return node;
}

ASTNode *ast_new_var_decl(TokenType keyword, char *name, ASTNode *value) {

  ASTNode *node = malloc(sizeof(ASTNode));
  node->kind = NODE_VAR_DECL;
  node->var_decl.keyword = keyword;
  node->var_decl.name = strdup(name);
  node->var_decl.value = value;
  return node;
}

ASTNode *ast_new_assign(char *name, ASTNode *value) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->kind = NODE_ASSIGN;
  node->assign.name = strdup(name);
  node->assign.value = value;
  return node;
}

ASTNode *ast_new_binop(TokenType op, ASTNode *left, ASTNode *right) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->kind = NODE_BINOP;
  node->binop.left = left;
  node->binop.right = right;
  node->binop.op = op;
  return node;
}

ASTNode *ast_new_int_lit(int value) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->kind = NODE_INT_LIT;
  node->int_lit.value = value;
  return node;
}

ASTNode *ast_new_ident(char *name) {
  ASTNode *node = malloc(sizeof(ASTNode));
  node->kind = NODE_IDENT;
  node->ident.name = strdup(name);
  return node;
}

void ast_add_statement(ASTNode *program, ASTNode *stmt) {
  ASTNodeList *list = &program->program.statements;
  if (list->count == list->capacity) {
    list->capacity = list->capacity == 0 ? 8 : list->capacity * 2;
    list->items = realloc(list->items, sizeof(ASTNode *) * list->capacity);
  }

  list->items[list->count] = stmt;
  list->count++;
}

void ast_print(ASTNode *node, int indent) {
  if (node == NULL)
    return;

  for (int i = 0; i < indent; i++)
    printf(" ");

  switch (node->kind) {
  case NODE_PROGRAM:
    printf("program\n");
    for (int i = 0; i < node->program.statements.count; i++) {
      ast_print(node->program.statements.items[i], indent + 2);
    }
    break;
  case NODE_VAR_DECL:
    printf("var_decl: %s\n", node->var_decl.name);
    ast_print(node->var_decl.value, indent + 2);
    break;
  case NODE_ASSIGN:
    printf("assign: %s\n", node->assign.name);
    ast_print(node->assign.value, indent + 2);
    break;
  case NODE_BINOP:
    printf("binop: %d\n", node->binop.op);
    ast_print(node->binop.left, indent + 2);
    ast_print(node->binop.right, indent + 2);
    break;
  case NODE_INT_LIT:
    printf("int_lit: %d\n", node->int_lit.value);
    break;
  case NODE_IDENT:
    printf("ident: %s\n", node->ident.name);
    break;
  }
}

void ast_free(ASTNode *node) {
  if (node == NULL)
    return;

  switch (node->kind) {
  case NODE_PROGRAM:
    for (int i = 0; i < node->program.statements.count; i++) {
      ast_free(node->program.statements.items[i]);
    }
    free(node->program.statements.items);
    break;

  case NODE_VAR_DECL:
    free(node->var_decl.name);
    ast_free(node->var_decl.value);
    break;

  case NODE_ASSIGN:
    free(node->assign.name);
    ast_free(node->assign.value);
    break;

  case NODE_BINOP:
    ast_free(node->binop.left);
    ast_free(node->binop.right);
    break;

  case NODE_INT_LIT:
    break;

  case NODE_IDENT:
    free(node->ident.name);
    break;
  }

  free(node);
}
