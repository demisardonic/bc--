#ifndef SHUNTING_H
#define SHUNTING_H

#define DEFAULT_LENGTH 10

typedef struct shunting{
  double *val_stack;
  int val_size;
  int val_length;
  char *op_stack;
  int op_size;
  int op_length;
} shunting_t;

void shunting_init(shunting_t *);
void shunting_delete(shunting_t *);
void push_op(shunting_t *, const char);
char pop_op(shunting_t *);
char peak_op(const shunting_t *);
int size_op(const shunting_t *);
void print_op_stack(const shunting_t *);
void push_val(shunting_t *, const double);
double pop_val(shunting_t *);
double peak_val(const shunting_t *);
int size_val(const shunting_t *);
void print_val_stack(const shunting_t *);
  
#endif
