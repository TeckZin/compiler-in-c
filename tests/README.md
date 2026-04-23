# Test Suite

## Overview
This directory contains unit tests for each compiler stage:

- test_lexer.c
- test_parser.c
- test_ast.c
- test_semantic.c
- test_main.c

Each test can run independently or as part of the full suite.

## Run All Tests

```
cc -std=c11 -Wall -Wextra   tests/test_main.c   tests/test_lexer.c   tests/test_parser.c   tests/test_ast.c   tests/test_semantic.c   src/lexer/lexer.c   src/parser/parser.c   src/ast/ast.c   src/semantic/semantic.c   src/semantic/symtable.c   -o test_all

./test_all
```

## Run Individual Tests

Lexer:
```
cc -std=c11 -Wall -Wextra   tests/test_lexer.c src/lexer/lexer.c   -DTEST_LEXER_STANDALONE -o test_lexer
./test_lexer
```

Parser:
```
cc -std=c11 -Wall -Wextra   tests/test_parser.c   src/lexer/lexer.c   src/parser/parser.c   src/ast/ast.c   -DTEST_PARSER_STANDALONE -o test_parser
./test_parser
```

AST:
```
cc -std=c11 -Wall -Wextra   tests/test_ast.c src/ast/ast.c   -DTEST_AST_STANDALONE -o test_ast
./test_ast
```

Semantic:
```
cc -std=c11 -Wall -Wextra   tests/test_semantic.c   src/ast/ast.c   src/semantic/semantic.c   src/semantic/symtable.c   -DTEST_SEMANTIC_STANDALONE -o test_semantic
./test_semantic
```

## Requirements

- C11 compiler
- All source files located under src/
- Tests expect relative includes using ../src/

## Notes

- Failures indicate logic errors, not test issues
- Lexer return type must match parser expectations
- AST must properly allocate and free memory

