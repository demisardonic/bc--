#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shunting.h"

void shunting_init(shunting_t *yard){
  yard->val_stack = malloc(sizeof(double) * DEFAULT_LENGTH);
  yard->val_size = 0;
  yard->val_length = DEFAULT_LENGTH;
  yard->op_stack = malloc(sizeof(char) * DEFAULT_LENGTH);
  yard->op_size = 0;
  yard->op_length = DEFAULT_LENGTH;
}

void shunting_delete(shunting_t *yard){
  free(yard->val_stack);
  free(yard->op_stack);
}

void push_op(shunting_t *yard, const char c){
  if(yard->op_size >= yard->op_length){
    char *new_stack = (char *)malloc(sizeof(char) * yard->op_length * 2);
    yard->op_length *= 2;
    memcpy(new_stack, yard->op_stack, yard->op_length);
    free(yard->op_stack);
    yard->op_stack = new_stack;
  }
  yard->op_stack[yard->op_size++] = c;
}

char pop_op(shunting_t *yard){
  return yard->op_stack[--yard->op_size];
}

char peak_op(const shunting_t *yard){
  return yard->op_stack[yard->op_size-1];
}

int size_op(const shunting_t *yard){
  return yard->op_size;
}

void print_op_stack(const shunting_t *yard){
  int i = yard->op_size - 1;
  printf("Operator Stack: [");
  if(i == -1){
    printf("EMPTY");
  }else{ 
    while(i >= 0){
      printf("%c, ", yard->op_stack[i]);
      i--;
    }
  }
  printf("]\n");
}

void push_val(shunting_t *yard, const double v){
  if(yard->val_size >= yard->val_length){
    double *new_stack = (double *)malloc(sizeof(double) * yard->val_length * 2);
    yard->val_length *= 2;
    memcpy(new_stack, yard->val_stack, yard->val_length);
    free(yard->val_stack);
    yard->val_stack = new_stack;
  }
  yard->val_stack[yard->val_size++] = v;
}

double pop_val(shunting_t *yard){
  return yard->val_stack[--yard->val_size];
}

double peak_val(const shunting_t *yard){
  return yard->val_stack[yard->val_size-1];
}

int size_val(const shunting_t *yard){
  return yard->val_size;
}

void print_val_stack(const shunting_t *yard){
  int i = yard->val_size - 1;
  
  printf("Value Stack: [");
  if(i == -1){
    printf("EMPTY");
  }else{
    while(i >= 0){
      double value = yard->val_stack[i];
      if(value - floor(value))
	printf("%lf, ", value);
      else
	printf("%d, ", (int) value);
      i--;
    }
  }
  printf("]\n");
}
