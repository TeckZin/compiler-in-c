#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"
#include <stdbool.h>

#define EBNF_PATH "../../../grammar.ebnf"

typedef struct {
  Lexer *lexer;
  TokenType curr;
  TokenType prev;
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
void parse_program(Parser *p);
void parse_statement(Parser *p);
void parse_expression(Parser *p);
void parse_term(Parser *p);
void parse_factor(Parser *p);

#endif
