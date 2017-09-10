#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "shunting.h"

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

double pop_math(shunting_t *yard){
  if(size_op(yard)){
    char op = pop_op(yard);
    if(op == '+'){
      return pop_val(yard) + pop_val(yard);
    }else if(op == '-'){
      return pop_val(yard) - pop_val(yard);
    }else if(op == '*'){
      return pop_val(yard) * pop_val(yard);
    }else if(op == '/'){
      double temp = pop_val(yard);
      return pop_val(yard) / temp;
    }else if(op == '%'){
      double temp = pop_val(yard);
      return (int) pop_val(yard) % (int) temp;
    }else if(op == '^'){
      double temp = pop_val(yard);
      return pow(pop_val(yard), temp);
    }
  }
  return 0;
}

void parse(shunting_t *yard, const char *line){
  int pos = 0;
  int len = strlen(line);
  char cur;
  char token[256];
  
  while(pos<len){
    cur = line[pos];
    if(is_val(cur)){
      //Handle values (ie doubles)
      memset(token, 0, 256);
      pos = parse_val(line, len, pos, token);
      if(!strcmp(".", token)){
	fprintf(stderr, "Found invalid single period.\n");
	exit(-1);
      }
      push_val(yard, atof(token));
    }else if(is_op(cur)){
      while(size_op(yard) && op_to_pres(peak_op(yard)) >= op_to_pres(cur)){
	push_val(yard, pop_math(yard));
      }
      push_op(yard, cur);
      pos++;
    }else if(cur == '('){
      push_op(yard, cur);
      pos++;
    }else if(cur == ')'){
      while(size_op(yard) && peak_op(yard) != '('){
	push_val(yard, pop_math(yard));
      }
      pos++;
      pop_op(yard);
    }else{
      //Should be handled better, just ignores other characters in the input line
      pos++;
    }
  }

  while(size_op(yard)){
    push_val(yard, pop_math(yard));
  }
}

int parse_val(const char *line, const int len, int pos, char *token){
  int token_pos = 0;
  char cur = line[pos];

  int has_seen_period = 0;
  while(pos < len && is_val(cur)){
    if(cur == '.' && !has_seen_period){
      has_seen_period = 1;
    }else if(cur == '.'){
      fprintf(stderr, "Value parsing ran into second '.'\n");
      exit(-1);
    }
    token[token_pos++] = cur;
    cur = line[++pos];
  }
  token[token_pos] = 0;
  return pos;
}
