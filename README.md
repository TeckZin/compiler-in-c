# Compiler Project

## Overview
This project implements a basic compiler pipeline in C. The system is divided into four major stages:

- Lexer: Converts source code into tokens
- Parser: Builds an Abstract Syntax Tree (AST)
- AST: Represents structured syntax
- Semantic Analyzer: Validates meaning using a symbol table

## Directory Structure
```
project/
├── src/
│   ├── lexer/
│   ├── parser/
│   ├── ast/
│   └── semantic/
├── tests/
└── README.md
```

## Build

Run from project root:

```
cc -std=c11 -Wall -Wextra   src/lexer/lexer.c   src/parser/parser.c   src/ast/ast.c   src/semantic/semantic.c   src/semantic/symtable.c   -o compiler
```

## Run

```
./compiler
```

## Notes

- Parser depends on correct token stream from lexer
- AST constructors must handle memory safely
- Semantic analyzer assumes valid AST structure

