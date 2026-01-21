#ifndef LEXER_H
#define LEXER_H

typedef enum {
  TOKEN_EOF = -1,
  TOKEN_NEW_LINE = 0,
  TOKEN_INDENT = 2,
  TOKEN_ASSIGN,
  TOKEN_INT,
  TOKEN_STRING,

  // keywords
  TOKEN_IF = 101,
  TOKEN_WHILE,
  TOKEN_RETURN,
  TOKEN_EQUAL,
  TOKEN_NOT_EQUAL,
  TOKEN_SEMICOLON,
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_LEFT_BRACE,
  TOKEN_RIGHT_BRACE,

  // ops
  TOKEN_PLUS = 201,
  TOKEN_MINUS,
  TOKEN_MULTIPLY,
  TOKEN_DIVIDE,
} TokenType;

typedef struct {
  const char *src;
  int length;
  int pos;
  char current;
  int line;
  int col;
  const char *filename;

} Lexer;

typedef struct {
  TokenType kind;
  const char *start;
  int length;
  int line;
  int col;
} Token;

void lexer_init(Lexer *l, const char *src);

char next_char(Lexer *l);
char peek(Lexer *l);
void abort_token(Lexer *l, char *msg);
TokenType get_token(Lexer *l);
void skip_white_space(Lexer *l);
bool is_digit(char s);

#endif
