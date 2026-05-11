#include "ir.h"
#include <stdio.h>
#include <stdlib.h>

IRInstr *ir_new_instr(IROp op, int dest, int src1, int src2) {
  IRInstr *instr = malloc(sizeof(IRInstr));
  instr->op = op;
  instr->dest = dest;
  instr->src1 = src1;
  instr->src2 = src2;
  return instr;
}

void ir_list_add(IRList *list, IRInstr *instr) {
  if (list->count == list->capacity) {
    list->capacity = list->capacity == 0 ? 8 : list->capacity * 2;
    list->items = realloc(list->items, sizeof(IRInstr *) * list->capacity);
  }
  list->items[list->count] = instr;
  list->count++;
}

void ir_print(IRInstr *instr) {
  printf("instr: op:%d, dest:%d, src1:%d, src2:%d\n", instr->op, instr->dest,
         instr->src1, instr->src2);
}

void ir_print_list(IRList *list) {
  if (list->items == NULL)
    return;
  printf("list instr: cap %d, count %d\n", list->capacity, list->count);
  for (int i = 0; i < list->count; i++) {
    ir_print(list->items[i]);
  }
}

void ir_free(IRInstr *instr) { free(instr); }

void ir_free_list(IRList *list) {
  if (list->items == NULL)
    return;

  for (int i = 0; i < list->count; i++) {
    ir_free(list->items[i]);
  }
  free(list->items);
  free(list);
}
