#include "lexer.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void lexer_init(Lexer *l, const char *src) {
  l->src = src;
  l->pos = 0;
  l->current = src[0];
  l->line = 1;
  l->col = 1;
}

char next_char(Lexer *l) {
  if (l->current == '\n') {
    l->line++;
    l->col = 0;
  }

  l->pos++;
  l->current = l->src[l->pos];
  l->col++;
  return l->current;
}

char peek(Lexer *l) {
  char c = l->src[l->pos + 1];
  return c;
}

void abort_token(Lexer *l, char *msg) {
  fprintf(stderr, "Lexer error line:%d, col %d: %s\n", l->line, l->col, msg);
}

TokenType get_token(Lexer *l) {
  if (l->current == '+') {
    return TOKEN_PLUS;
  } else if (l->current == '-') {
    return TOKEN_MINUS;
  } else if (l->current == '*') {
    return TOKEN_MULTIPLY;
  } else if (l->current == '/') {
    return TOKEN_DIVIDE;
  } else if (l->current == '=') {
    return TOKEN_ASSIGN;
  } else if (is_digit(l->current)) {
    return TOKEN_INT;
  } else if (l->current == '\0') {
    return TOKEN_EOF;
  }

  abort_token(l, "token not found");
}

void skip_white_space(Lexer *l) {
  while (isspace((unsigned char)l->current)) {
    next_char(l);
  }
}

static bool is_digit(char c) { return isdigit((unsigned char)c); }
