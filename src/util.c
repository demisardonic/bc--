#include "util.h"

int op_to_pres(char op){
  if(op == '+' || op == '-')
    return 2;
  else if(op == '*' || op == '/' || op == '%')
    return 3;
  else if(op == '^')
    return 4;
  return 0;
}

int is_val(char c){
  return (c >= '0' && c <= '9') || c == '.';
}

int is_op(char c){
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}
