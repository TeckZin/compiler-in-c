#include "parser.h"
#include <stdbool.h>

void paser_init(Parser *p, Lexer *l) {
  p->lexer = l;
  p->curr = TOKEN_EOF;
  p->prev = TOKEN_EOF;
}

void parser_advance(Parser *p) { p->lexer = p->curr; }

bool paser_check(Parser *p, TokenType kind) {}

bool paser_eof(Parser *p) {}

bool paser_match(Parser *p, TokenType kind, const char *msg) {}
