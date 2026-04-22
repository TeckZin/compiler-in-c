#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../util/util.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  Lexer *lex;
  char *string = read_file("");
  lexer_init(lex, string);
  Parser *parser;
  parser_init(parser, lex);
  ASTNode *tree = parse_program(parser);

  ast_free(tree);

  return 0;
}
