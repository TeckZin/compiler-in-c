#ifndef AST_H
#define AST_H

#include "../lexer/lexer.h"

typedef enum {
  NODE_PROGRAM,
  NODE_VAR_DECL,
  NODE_ASSIGN,
  NODE_BINOP,
  NODE_INT_LIT,
  NODE_IDENT,
} NodeKind;

typedef struct ASTNode ASTNode;

typedef struct {
  ASTNode **items;
  int count;
  int capacity;
} ASTNodeList;

struct ASTNode {
  NodeKind kind;

  union {
    struct {
      ASTNodeList statements;
    } program;

    struct {
      TokenType keyword;
      char *name;
      ASTNode *value;
    } var_decl;

    struct {
      char *name;
      ASTNode *value;
    } assign;

    struct {
      TokenType op;
      ASTNode *left;
      ASTNode *right;
    } binop;

    struct {
      int value;
    } int_lit;

    struct {
      char *name;
    } ident;
  };
};

ASTNode *ast_new_program(void);
ASTNode *ast_new_var_decl(TokenType keyword, char *name, ASTNode *value);
ASTNode *ast_new_assign(char *name, ASTNode *value);
ASTNode *ast_new_binop(TokenType op, ASTNode *left, ASTNode *right);
ASTNode *ast_new_int_lit(int value);
ASTNode *ast_new_ident(char *name);

void ast_add_statement(ASTNode *program, ASTNode *stmt);

void ast_print(ASTNode *node, int indent);

void ast_free(ASTNode *node);

#endif
