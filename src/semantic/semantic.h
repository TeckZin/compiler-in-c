#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "../ast/ast.h"
#include "symtable.h"
#include <stdbool.h>

typedef struct {
  SymTable *table;
  bool err_flag;
} Analyzer;

void analyzer_init(Analyzer *a, SymTable *table);

// tree walkers
void analyze_program(Analyzer *a, ASTNode *node);
void analyze_statement(Analyzer *a, ASTNode *node);
void analyze_var_decl(Analyzer *a, ASTNode *node);
void analyze_assign(Analyzer *a, ASTNode *node);
void analyze_expression(Analyzer *a, ASTNode *node);
void analyze_binop(Analyzer *a, ASTNode *node);
void analyze_int_lit(Analyzer *a, ASTNode *node);
void analyze_ident(Analyzer *a, ASTNode *node);

// errors
void analyze_error(Analyzer *a, const char *msg);

#endif
