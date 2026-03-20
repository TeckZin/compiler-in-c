#include "parser.h"
#include <stdbool.h>

void paser_init(Parser *p, Lexer *l) {
  p->lexer = l;
  p->curr = TOKEN_EOF;
  p->prev = TOKEN_EOF;
}

void parser_advance(Parser *p) {
  p->prev = p->curr;
  p->curr = p->lexer->current;
}

bool paser_check(Parser *p, TokenType kind) { return p->curr = kind; }

bool paser_eof(Parser *p) { return p->curr == TOKEN_EOF; }

bool paser_match(Parser *p, TokenType kind, const char *msg) {
  bool flag = parser_check(p, kind);
  if (flag) {
    parser_advance(p);
  }
  return flag;
}

void parser_expect(Parser *p, TokenType kind, const char *msg) {}
