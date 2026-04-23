#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lexer_init(Lexer *l, const char *src) {
  l->src = src;
  l->length = strlen(src);
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

char peek(Lexer *l) { return l->src[l->pos + 1]; }

void abort_token(Lexer *l, char *msg) {
  fprintf(stderr, "lexer error [line %d, col %d]: %s\n", l->line, l->col, msg);
}

bool is_digit(char c) { return isdigit((unsigned char)c); }

bool is_alpha(char c) { return isalpha((unsigned char)c) || c == '_'; }

void skip_white_space(Lexer *l) {
  while (isspace((unsigned char)l->current)) {
    next_char(l);
  }
}

TokenType get_token(Lexer *l) {
  skip_white_space(l);

  if (l->current == '\0') {
    return TOKEN_EOF;
  }

  if (l->current == '+') {
    next_char(l);
    return TOKEN_PLUS;
  }
  if (l->current == '-') {
    next_char(l);
    return TOKEN_MINUS;
  }
  if (l->current == '*') {
    next_char(l);
    return TOKEN_MULTIPLY;
  }
  if (l->current == '/') {
    next_char(l);
    return TOKEN_DIVIDE;
  }
  if (l->current == '=') {
    next_char(l);
    return TOKEN_EQUAL;
  }
  if (l->current == ';') {
    next_char(l);
    return TOKEN_SEMICOLON;
  }
  if (l->current == '(') {
    next_char(l);
    return TOKEN_LEFT_PAREN;
  }
  if (l->current == ')') {
    next_char(l);
    return TOKEN_RIGHT_PAREN;
  }
  if (l->current == '{') {
    next_char(l);
    return TOKEN_LEFT_BRACE;
  }
  if (l->current == '}') {
    next_char(l);
    return TOKEN_RIGHT_BRACE;
  }

  if (is_digit(l->current)) {
    while (is_digit(l->current)) {
      next_char(l);
    }
    return TOKEN_INT;
  }

  if (is_alpha(l->current)) {
    int start = l->pos;

    while (is_alpha(l->current) || is_digit(l->current)) {
      next_char(l);
    }

    int len = l->pos - start;

    if (len == 3 && strncmp(l->src + start, "let", 3) == 0)
      return TOKEN_LET;
    if (len == 3 && strncmp(l->src + start, "var", 3) == 0)
      return TOKEN_VAR;
    if (len == 2 && strncmp(l->src + start, "if", 2) == 0)
      return TOKEN_IF;
    if (len == 5 && strncmp(l->src + start, "while", 5) == 0)
      return TOKEN_WHILE;
    if (len == 6 && strncmp(l->src + start, "return", 6) == 0)
      return TOKEN_RETURN;

    return TOKEN_IDENT;
  }

  abort_token(l, "unexpected character");
  next_char(l);
  return TOKEN_EOF;
}
