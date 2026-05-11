#ifndef IR_H
#define IR_H

#include <stdio.h>
typedef enum {
  IR_MOV,
  IR_ADD,
  IR_SUB,
  IR_MUL,
  IR_DIV

} IROp;

typedef struct {
  IROp op;
  int dest;
  int src1;
  int src2;

} IRInstr;

typedef struct {
  IRInstr **items;
  int count;
  int capacity;
} IRList;

IRInstr *ir_new_instr(IROp op, int dest, int src1, int src2);

void ir_list_add(IRList *list, IRInstr *instr);

void ir_print_to_asm(IRInstr *instr, FILE *output);

void ir_print(IRInstr *instr);

void ir_print_list(IRList *list);

void ir_free(IRInstr *instr);

void ir_free_list(IRList *list);
#endif
