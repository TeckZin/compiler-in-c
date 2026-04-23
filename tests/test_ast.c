#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/ast/ast.h"

static int tests_run = 0;
static int tests_failed = 0;

#define EXPECT_TRUE(cond) do { tests_run++; if (!(cond)) { tests_failed++; fprintf(stderr, "[FAIL] %s:%d: %s\n", __FILE__, __LINE__, #cond); } } while (0)
#define EXPECT_EQ_INT(actual, expected) do { int a = (int)(actual); int e = (int)(expected); tests_run++; if (a != e) { tests_failed++; fprintf(stderr, "[FAIL] %s:%d: got %d expected %d\n", __FILE__, __LINE__, a, e); } } while (0)
#define EXPECT_STREQ(actual, expected) do { const char *a = (actual); const char *e = (expected); tests_run++; if ((a == NULL && e != NULL) || (a != NULL && e == NULL) || (a && e && strcmp(a, e) != 0)) { tests_failed++; fprintf(stderr, "[FAIL] %s:%d: got %s expected %s\n", __FILE__, __LINE__, a ? a : "(null)", e ? e : "(null)"); } } while (0)

static void test_int_lit(void) {
  ASTNode *n = ast_new_int_lit(42);
  EXPECT_TRUE(n != NULL);
  EXPECT_EQ_INT(n->kind, NODE_INT_LIT);
  EXPECT_EQ_INT(n->int_lit.value, 42);
  ast_free(n);
}

static void test_ident(void) {
  ASTNode *n = ast_new_ident("x");
  EXPECT_TRUE(n != NULL);
  EXPECT_EQ_INT(n->kind, NODE_IDENT);
  EXPECT_STREQ(n->ident.name, "x");
  ast_free(n);
}

static void test_binop(void) {
  ASTNode *left = ast_new_int_lit(1);
  ASTNode *right = ast_new_int_lit(2);
  ASTNode *n = ast_new_binop(TOKEN_PLUS, left, right);
  EXPECT_TRUE(n != NULL);
  EXPECT_EQ_INT(n->kind, NODE_BINOP);
  EXPECT_EQ_INT(n->binop.op, TOKEN_PLUS);
  EXPECT_TRUE(n->binop.left == left);
  EXPECT_TRUE(n->binop.right == right);
  ast_free(n);
}

static void test_var_decl(void) {
  ASTNode *value = ast_new_int_lit(10);
  ASTNode *n = ast_new_var_decl(TOKEN_LET, "x", value);
  EXPECT_TRUE(n != NULL);
  EXPECT_EQ_INT(n->kind, NODE_VAR_DECL);
  EXPECT_EQ_INT(n->var_decl.keyword, TOKEN_LET);
  EXPECT_STREQ(n->var_decl.name, "x");
  EXPECT_TRUE(n->var_decl.value == value);
  ast_free(n);
}

static void test_assign(void) {
  ASTNode *value = ast_new_int_lit(5);
  ASTNode *n = ast_new_assign("x", value);
  EXPECT_TRUE(n != NULL);
  EXPECT_EQ_INT(n->kind, NODE_ASSIGN);
  EXPECT_STREQ(n->assign.name, "x");
  EXPECT_TRUE(n->assign.value == value);
  ast_free(n);
}

static void test_program(void) {
  ASTNode *p = ast_new_program();
  ASTNode *a = ast_new_int_lit(1);
  ASTNode *b = ast_new_int_lit(2);
  EXPECT_TRUE(p != NULL);
  EXPECT_EQ_INT(p->kind, NODE_PROGRAM);
  EXPECT_EQ_INT(p->program.statements.count, 0);
  ast_add_statement(p, a);
  ast_add_statement(p, b);
  EXPECT_EQ_INT(p->program.statements.count, 2);
  EXPECT_TRUE(p->program.statements.items[0] == a);
  EXPECT_TRUE(p->program.statements.items[1] == b);
  ast_free(p);
}

int run_ast_tests(void) {
  tests_run = 0;
  tests_failed = 0;
  test_int_lit();
  test_ident();
  test_binop();
  test_var_decl();
  test_assign();
  test_program();
  if (tests_failed == 0) {
    printf("ast ok\n");
    return 0;
  }
  printf("ast failed\n");
  return 1;
}

#ifdef TEST_AST_STANDALONE
int main(void) {
  return run_ast_tests();
}
#endif
