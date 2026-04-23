#include <stdio.h>
#include <string.h>
#include "../src/parser/parser.h"
#include "../src/ast/ast.h"
#include "../src/lexer/lexer.h"

static int tests_run = 0;
static int tests_failed = 0;

#define EXPECT_TRUE(cond) do { tests_run++; if (!(cond)) { tests_failed++; fprintf(stderr, "[FAIL] %s:%d: %s\n", __FILE__, __LINE__, #cond); } } while (0)
#define EXPECT_EQ_INT(actual, expected) do { int a = (int)(actual); int e = (int)(expected); tests_run++; if (a != e) { tests_failed++; fprintf(stderr, "[FAIL] %s:%d: got %d expected %d\n", __FILE__, __LINE__, a, e); } } while (0)
#define EXPECT_STREQ(actual, expected) do { const char *a = (actual); const char *e = (expected); tests_run++; if ((a == NULL && e != NULL) || (a != NULL && e == NULL) || (a && e && strcmp(a, e) != 0)) { tests_failed++; fprintf(stderr, "[FAIL] %s:%d: got %s expected %s\n", __FILE__, __LINE__, a ? a : "(null)", e ? e : "(null)"); } } while (0)

static ASTNode *parse_src(const char *src, Parser *p, Lexer *l) {
  lexer_init(l, src);
  parser_init(p, l);
  return parse_program(p);
}

static void test_var_decl(void) {
  Parser p;
  Lexer l;
  ASTNode *root = parse_src("let x = 42;", &p, &l);
  ASTNode *stmt;
  EXPECT_TRUE(root != NULL);
  EXPECT_EQ_INT(root->kind, NODE_PROGRAM);
  EXPECT_EQ_INT(root->program.statements.count, 1);
  stmt = root->program.statements.items[0];
  EXPECT_EQ_INT(stmt->kind, NODE_VAR_DECL);
  EXPECT_EQ_INT(stmt->var_decl.keyword, TOKEN_LET);
  EXPECT_STREQ(stmt->var_decl.name, "x");
  EXPECT_TRUE(stmt->var_decl.value != NULL);
  EXPECT_EQ_INT(stmt->var_decl.value->kind, NODE_INT_LIT);
  EXPECT_EQ_INT(stmt->var_decl.value->int_lit.value, 42);
  ast_free(root);
}

static void test_assign(void) {
  Parser p;
  Lexer l;
  ASTNode *root = parse_src("x = 7;", &p, &l);
  ASTNode *stmt;
  EXPECT_TRUE(root != NULL);
  EXPECT_EQ_INT(root->kind, NODE_PROGRAM);
  EXPECT_EQ_INT(root->program.statements.count, 1);
  stmt = root->program.statements.items[0];
  EXPECT_EQ_INT(stmt->kind, NODE_ASSIGN);
  EXPECT_STREQ(stmt->assign.name, "x");
  EXPECT_TRUE(stmt->assign.value != NULL);
  EXPECT_EQ_INT(stmt->assign.value->kind, NODE_INT_LIT);
  EXPECT_EQ_INT(stmt->assign.value->int_lit.value, 7);
  ast_free(root);
}

static void test_precedence(void) {
  Parser p;
  Lexer l;
  ASTNode *root = parse_src("let x = 1 + 2 * 3;", &p, &l);
  ASTNode *stmt;
  ASTNode *expr;
  EXPECT_TRUE(root != NULL);
  EXPECT_EQ_INT(root->program.statements.count, 1);
  stmt = root->program.statements.items[0];
  EXPECT_EQ_INT(stmt->kind, NODE_VAR_DECL);
  expr = stmt->var_decl.value;
  EXPECT_TRUE(expr != NULL);
  EXPECT_EQ_INT(expr->kind, NODE_BINOP);
  EXPECT_EQ_INT(expr->binop.op, TOKEN_PLUS);
  EXPECT_EQ_INT(expr->binop.left->kind, NODE_INT_LIT);
  EXPECT_EQ_INT(expr->binop.left->int_lit.value, 1);
  EXPECT_EQ_INT(expr->binop.right->kind, NODE_BINOP);
  EXPECT_EQ_INT(expr->binop.right->binop.op, TOKEN_MULTIPLY);
  EXPECT_EQ_INT(expr->binop.right->binop.left->kind, NODE_INT_LIT);
  EXPECT_EQ_INT(expr->binop.right->binop.left->int_lit.value, 2);
  EXPECT_EQ_INT(expr->binop.right->binop.right->kind, NODE_INT_LIT);
  EXPECT_EQ_INT(expr->binop.right->binop.right->int_lit.value, 3);
  ast_free(root);
}

static void test_multiple_statements(void) {
  Parser p;
  Lexer l;
  ASTNode *root = parse_src("let x = 1; x = x + 2;", &p, &l);
  EXPECT_TRUE(root != NULL);
  EXPECT_EQ_INT(root->kind, NODE_PROGRAM);
  EXPECT_EQ_INT(root->program.statements.count, 2);
  EXPECT_EQ_INT(root->program.statements.items[0]->kind, NODE_VAR_DECL);
  EXPECT_EQ_INT(root->program.statements.items[1]->kind, NODE_ASSIGN);
  ast_free(root);
}

static void test_error_flag(void) {
  Parser p;
  Lexer l;
  ASTNode *root = parse_src("let = 1;", &p, &l);
  EXPECT_TRUE(p.err_flag);
  if (root != NULL) ast_free(root);
}

int run_parser_tests(void) {
  tests_run = 0;
  tests_failed = 0;
  test_var_decl();
  test_assign();
  test_precedence();
  test_multiple_statements();
  test_error_flag();
  if (tests_failed == 0) {
    printf("parser ok\n");
    return 0;
  }
  printf("parser failed\n");
  return 1;
}

#ifdef TEST_PARSER_STANDALONE
int main(void) {
  return run_parser_tests();
}
#endif
