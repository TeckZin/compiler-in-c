#include <stdio.h>
#include "../src/lexer/lexer.h"

static int tests_run = 0;
static int tests_failed = 0;

#define EXPECT_TRUE(cond) do { tests_run++; if (!(cond)) { tests_failed++; fprintf(stderr, "[FAIL] %s:%d: %s\n", __FILE__, __LINE__, #cond); } } while (0)
#define EXPECT_EQ_INT(actual, expected) do { int a = (int)(actual); int e = (int)(expected); tests_run++; if (a != e) { tests_failed++; fprintf(stderr, "[FAIL] %s:%d: got %d expected %d\n", __FILE__, __LINE__, a, e); } } while (0)

static TokenType next_kind(Lexer *l) {
  return get_token(l);
}

static void test_helpers(void) {
  EXPECT_TRUE(is_digit('0'));
  EXPECT_TRUE(is_digit('9'));
  EXPECT_TRUE(!is_digit('a'));
  EXPECT_TRUE(is_alpha('a'));
  EXPECT_TRUE(is_alpha('Z'));
  EXPECT_TRUE(is_alpha('_'));
  EXPECT_TRUE(!is_alpha('7'));
}

static void test_keywords_and_idents(void) {
  Lexer l;
  lexer_init(&l, "let var if while return name foo_bar");
  EXPECT_EQ_INT(next_kind(&l), TOKEN_LET);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_VAR);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_IF);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_WHILE);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_RETURN);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_IDENT);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_IDENT);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_EOF);
}

static void test_literals(void) {
  Lexer l;
  lexer_init(&l, "123 \"hello\" abc");
  EXPECT_EQ_INT(next_kind(&l), TOKEN_INT);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_STRING);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_IDENT);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_EOF);
}

static void test_symbols_and_ops(void) {
  Lexer l;
  lexer_init(&l, "= != ; ( ) { } + - * /");
  EXPECT_EQ_INT(next_kind(&l), TOKEN_EQUAL);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_NOT_EQUAL);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_SEMICOLON);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_LEFT_PAREN);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_RIGHT_PAREN);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_LEFT_BRACE);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_RIGHT_BRACE);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_PLUS);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_MINUS);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_MULTIPLY);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_DIVIDE);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_EOF);
}

static void test_simple_program_stream(void) {
  Lexer l;
  TokenType k;
  lexer_init(&l, "let x = 10;\nx = x + 2;");
  EXPECT_EQ_INT(next_kind(&l), TOKEN_LET);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_IDENT);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_EQUAL);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_INT);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_SEMICOLON);
  k = next_kind(&l);
  if (k == TOKEN_NEW_LINE) k = next_kind(&l);
  EXPECT_EQ_INT(k, TOKEN_IDENT);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_EQUAL);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_IDENT);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_PLUS);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_INT);
  EXPECT_EQ_INT(next_kind(&l), TOKEN_SEMICOLON);
  k = next_kind(&l);
  if (k == TOKEN_NEW_LINE) k = next_kind(&l);
  EXPECT_EQ_INT(k, TOKEN_EOF);
}

int run_lexer_tests(void) {
  tests_run = 0;
  tests_failed = 0;
  test_helpers();
  test_keywords_and_idents();
  test_literals();
  test_symbols_and_ops();
  test_simple_program_stream();
  if (tests_failed == 0) {
    printf("lexer ok\n");
    return 0;
  }
  printf("lexer failed\n");
  return 1;
}

#ifdef TEST_LEXER_STANDALONE
int main(void) {
  return run_lexer_tests();
}
#endif
