#include "../lexer/lexer.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  Lexer *lex;
  const char *c = "hello";
  lexer_init(lex, c);

  return 0;
}
