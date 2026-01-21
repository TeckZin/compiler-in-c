#include "paser.h"
#include <stdbool.h>

void paser_init(Paser *p, Lexer *l) {
  p->lexer = l;
  p->curr = TOKEN_EOF;
  p->prev = TOKEN_EOF;
}

void next_token(Paser *p) {}

bool paser_check(Paser *p, TokenType kind) {}

bool paser_eof(Paser *p) {}

bool paser_match(Paser *p, TokenType kind, const char *msg) {}
