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

// a growable list of statements for the program node
typedef struct {
  ASTNode **items;
  int count;
  int capacity;
} ASTNodeList;

struct ASTNode {
  NodeKind kind;

  union {
    // NODE_PROGRAM
    struct {
      ASTNodeList statements;
    } program;

    // NODE_VAR_DECL: let x = expr;
    struct {
      TokenType keyword; // TOKEN_ASSIGN in your enum (let/var)
      char *name;
      ASTNode *value;
    } var_decl;

    // NODE_ASSIGN: x = expr;
    struct {
      char *name;
      ASTNode *value;
    } assign;

    // NODE_BINOP: left + right
    struct {
      TokenType op; // TOKEN_PLUS, TOKEN_MINUS, etc.
      ASTNode *left;
      ASTNode *right;
    } binop;

    // NODE_INT_LIT: 42
    struct {
      int value;
    } int_lit;

    // NODE_IDENT: x
    struct {
      char *name;
    } ident;
  };
};

// constructors - each one allocates and returns a node
ASTNode *ast_new_program(void);
ASTNode *ast_new_var_decl(TokenType keyword, char *name, ASTNode *value);
ASTNode *ast_new_assign(char *name, ASTNode *value);
ASTNode *ast_new_binop(TokenType op, ASTNode *left, ASTNode *right);
ASTNode *ast_new_int_lit(int value);
ASTNode *ast_new_ident(char *name);

// program helpers
void ast_add_statement(ASTNode *program, ASTNode *stmt);

// debug
void ast_print(ASTNode *node, int indent);

// cleanup
void ast_free(ASTNode *node);

#endif
