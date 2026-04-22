#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parser_init(Parser *p, Lexer *l) {
  p->lexer = l;
  p->err_flag = false;

  p->prev.kind = TOKEN_EOF;
  p->prev.start = NULL;
  p->prev.length = 0;
  p->prev.line = 0;
  p->prev.col = 0;

  parser_advance(p);
}

void parser_advance(Parser *p) {
  p->prev = p->curr;

  TokenType kind = get_token(p->lexer);

  p->curr.kind = kind;
  p->curr.start = p->lexer->src + p->lexer->pos;
  p->curr.length = 1;
  p->curr.line = p->lexer->line;
  p->curr.col = p->lexer->col;
}

bool parser_check(Parser *p, TokenType kind) { return p->curr.kind == kind; }

bool parser_is_at_end(Parser *p) { return p->curr.kind == TOKEN_EOF; }

bool parser_match(Parser *p, TokenType kind) {
  if (parser_check(p, kind)) {
    parser_advance(p);
    return true;
  }
  return false;
}

void parser_expect(Parser *p, TokenType kind, const char *msg) {
  if (parser_check(p, kind)) {
    parser_advance(p);
  } else {
    parser_error_at_current(p, msg);
  }
}

void parser_error_at_current(Parser *p, const char *msg) {
  p->err_flag = true;
  fprintf(stderr, "[line %d, col %d] error: %s\n", p->curr.line, p->curr.col,
          msg);
}

ASTNode *parse_program(Parser *p) {
  ASTNode *program = ast_new_program();
  while (!parser_is_at_end(p)) {
    ASTNode *stmt = parse_statement(p);
    if (stmt != NULL) {
      ast_add_statement(program, stmt);
    }
  }
  return program;
}

ASTNode *parse_statement(Parser *p) {
  if (parser_check(p, TOKEN_ASSIGN)) {
    TokenType keyword = p->curr.kind;
    parser_advance(p);

    char *name = strndup(p->curr.start, p->curr.length);
    parser_expect(p, TOKEN_INDENT, "expected identifier");
    parser_expect(p, TOKEN_EQUAL, "expected '='");
    ASTNode *value = parse_expression(p);
    parser_expect(p, TOKEN_SEMICOLON, "expected ';'");

    return ast_new_var_decl(keyword, name, value);

  } else if (parser_check(p, TOKEN_INDENT)) {
    char *name = strndup(p->curr.start, p->curr.length);
    parser_advance(p);
    parser_expect(p, TOKEN_EQUAL, "expected '='");
    ASTNode *value = parse_expression(p);
    parser_expect(p, TOKEN_SEMICOLON, "expected ';'");

    return ast_new_assign(name, value);

  } else {
    parser_error_at_current(p, "expected statement");
    parser_advance(p);
    return NULL;
  }
}

// expression = term { operator term }
// operator   = "+" | "-" | "*" | "/"
//
// for proper precedence you'd split into:
//   expression = term { ("+" | "-") term }
//   term       = factor { ("*" | "/") factor }
// but your EBNF is flat, so this matches it exactly
ASTNode *parse_expression(Parser *p) {

  ASTNode *left = parse_term(p);

  while (parser_check(p, TOKEN_PLUS) || parser_check(p, TOKEN_MINUS) ||
         parser_check(p, TOKEN_MULTIPLY) || parser_check(p, TOKEN_DIVIDE)) {

    TokenType op = p->curr.kind;
    parser_advance(p);
    ASTNode *right = parse_term(p);
    left = ast_new_binop(op, left, right);
  }

  return left;
}

// term = number | identifier
ASTNode *parse_term(Parser *p) {
  if (parser_check(p, TOKEN_INT)) {
    int value = atoi(p->curr.start);
    parser_advance(p);
    return ast_new_int_lit(value);
  } else if (parser_check(p, TOKEN_INDENT)) {
    char *name = strndup(p->curr.start, p->curr.length);
    parser_advance(p);
    return ast_new_ident(name);
  } else {
    parser_error_at_current(p, "expected number or identifier");
    return NULL;
  }
}

ASTNode *parse_factor(Parser *p) { parse_term(p); }
