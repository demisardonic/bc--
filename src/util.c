#include <math.h>
#include <ncurses.h>
 
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

void print_val(int y, int x, double val, int force_double){
  if(force_double || val != floor(val)){
    mvprintw(y, x, "%lf", val);
  }else{
    mvprintw(y, x, "%d", (int) val);
  }
}

void clear_line(int y){
  int w,h;
  getmaxyx(stdscr, h, w);
  h = y;
  move(h, 0);
  while(--w >= 0){
    addch(' ');
  }
}
