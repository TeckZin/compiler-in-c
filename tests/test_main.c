int run_lexer_tests(void);
int run_parser_tests(void);
int run_ast_tests(void);
int run_semantic_tests(void);

int main(void) {
  int failed = 0;
  failed += run_lexer_tests();
  failed += run_parser_tests();
  failed += run_ast_tests();
  failed += run_semantic_tests();
  return failed ? 1 : 0;
}
