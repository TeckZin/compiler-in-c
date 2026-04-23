#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../src/semantic/semantic.h"
#include "../src/semantic/symtable.h"
#include "../src/ast/ast.h"
#include "../src/lexer/lexer.h"

static int tests_run = 0;
static int tests_failed = 0;

#define EXPECT_TRUE(cond) do { tests_run++; if (!(cond)) { tests_failed++; fprintf(stderr, "[FAIL] %s:%d: %s\n", __FILE__, __LINE__, #cond); } } while (0)
#define EXPECT_FALSE(cond) EXPECT_TRUE(!(cond))

static ASTNode *make_program_decl_then_use(void) {
  ASTNode *program = ast_new_program();
  ast_add_statement(program, ast_new_var_decl(TOKEN_LET, "x", ast_new_int_lit(1)));
  ast_add_statement(program, ast_new_assign("x", ast_new_binop(TOKEN_PLUS, ast_new_ident("x"), ast_new_int_lit(2))));
  return program;
}

static ASTNode *make_program_undeclared_assign(void) {
  ASTNode *program = ast_new_program();
  ast_add_statement(program, ast_new_assign("x", ast_new_int_lit(1)));
  return program;
}

static ASTNode *make_program_undeclared_ident(void) {
  ASTNode *program = ast_new_program();
  ast_add_statement(program, ast_new_var_decl(TOKEN_LET, "x", ast_new_binop(TOKEN_PLUS, ast_new_ident("y"), ast_new_int_lit(1))));
  return program;
}

static void test_symtable_basic(void) {
  SymTable table;
  bool added_again;
  symtable_init(&table);
  EXPECT_FALSE(symtable_lookup(&table, "x"));
  EXPECT_TRUE(symtable_add(&table, "x"));
  EXPECT_TRUE(symtable_lookup(&table, "x"));
  added_again = symtable_add(&table, "x");
  EXPECT_FALSE(added_again);
  symtable_free(&table);
}

static void test_analyzer_accepts_decl_then_use(void) {
  SymTable table;
  Analyzer a;
  ASTNode *program = make_program_decl_then_use();
  symtable_init(&table);
  analyzer_init(&a, &table);
  analyze_program(&a, program);
  EXPECT_FALSE(a.err_flag);
  EXPECT_TRUE(symtable_lookup(&table, "x"));
  ast_free(program);
  symtable_free(&table);
}

static void test_analyzer_rejects_undeclared_assign(void) {
  SymTable table;
  Analyzer a;
  ASTNode *program = make_program_undeclared_assign();
  symtable_init(&table);
  analyzer_init(&a, &table);
  analyze_program(&a, program);
  EXPECT_TRUE(a.err_flag);
  ast_free(program);
  symtable_free(&table);
}

static void test_analyzer_rejects_undeclared_ident(void) {
  SymTable table;
  Analyzer a;
  ASTNode *program = make_program_undeclared_ident();
  symtable_init(&table);
  analyzer_init(&a, &table);
  analyze_program(&a, program);
  EXPECT_TRUE(a.err_flag);
  ast_free(program);
  symtable_free(&table);
}

int run_semantic_tests(void) {
  tests_run = 0;
  tests_failed = 0;
  test_symtable_basic();
  test_analyzer_accepts_decl_then_use();
  test_analyzer_rejects_undeclared_assign();
  test_analyzer_rejects_undeclared_ident();
  if (tests_failed == 0) {
    printf("semantic ok\n");
    return 0;
  }
  printf("semantic failed\n");
  return 1;
}

#ifdef TEST_SEMANTIC_STANDALONE
int main(void) {
  return run_semantic_tests();
}
#endif
