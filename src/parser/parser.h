#ifndef PARSER_H
#define PARSER_H

#include "../ast/ast.h"
#include "../lexer/lexer.h"
#include <stdbool.h>

typedef struct {
  Lexer *lexer;
  Token curr;
  Token prev;
  bool err_flag;
} Parser;

// lifecycle
void parser_init(Parser *p, Lexer *l);

// token stream control
void parser_advance(Parser *p);
bool parser_check(Parser *p, TokenType kind);
bool parser_is_at_end(Parser *p);
bool parser_match(Parser *p, TokenType kind);
void parser_expect(Parser *p, TokenType kind, const char *msg);

// errors
void parser_error_at_current(Parser *p, const char *msg);

// grammar -> syntax
// these return void for now
// when you add AST: change to ASTNode*
ASTNode *parse_program(Parser *p);
ASTNode *parse_statement(Parser *p);
ASTNode *parse_expression(Parser *p);
ASTNode *parse_term(Parser *p);
ASTNode *parse_factor(Parser *p);

#endif
