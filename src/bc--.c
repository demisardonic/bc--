#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "command.h"
#include "history.h"
#include "parser.h"
#include "shunting.h"
#include "util.h"

void draw_newest_history(const history_t *history){
  int height, cur_x;
  getmaxyx(stdscr, height, cur_x);
  cur_x = 0;
  clear();
  int history_from = history->size - (height / 2);
  int cur_y = 0;

  while(history_from < history->size){
    mvprintw(cur_y++, cur_x, history->lines[history_from]);
    mvprintw(cur_y++, cur_x, "%lf", history->vals[history_from]);
    move(cur_y, cur_x);    
  }
}

int main(int argv, char **argc){
  shunting_t yard;
  history_t history;
  char line[256];
  int line_size;
  int key, cur_y, cur_x;
  int max_width, max_height;

  getmaxyx(stdscr, max_height, max_width);

  memset(line, 0, 256);
  
  shunting_init(&yard);
  history_init(&history);
  
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  cur_y = cur_x = 0;

  // Keyboard input, count the size of the input
  do{
    line_size = 0;
    do{
      key = getch();

      //TODO handle single line that goes over max width
      if(line_size > max_width){

      }
      //TODO need 256 bounds check for input line
      if(is_val(key)){
	line[line_size++] = key;
	mvaddch(cur_y, cur_x++, key);
      }else if(is_op(key)){
	line[line_size++] = key;
	mvaddch(cur_y, cur_x++, key);
      }else if(key == KEY_BACKSPACE && line_size > 0){
	line[--line_size] = '\0';
	mvaddch(cur_y, --cur_x, ' ');
	move(cur_y, cur_x);
      }
    }while(key != '\n');
    
    if(line_size > 0){
      //TODO handle more calculations than vertical space allows
      if(history.size * 2 > max_height){

      }
      
      //malloc a char * for the size of the input
      char *line_string = (char *)malloc(sizeof(char) * (line_size + 1));
      memcpy(line_string, line, line_size);
      line_string[line_size] = '\0';
      cur_x = 0;
      //store that pointer within history
      if(history.size == history.length){
	history.length *= 2;
	history.lines = (char **) realloc(history.lines, sizeof(char *) * history.length);
	history.vals = (double *) realloc(history.vals, sizeof(double) * history.length);
      }
      history.lines[history.size] = line_string;
      
      //parse that input with shunting_yard structure
      parse(&yard, line_string);
      double value = pop_val(&yard);

      history.vals[history.size] = value;
      history.size++;

      if(value == floor(value)){
	mvprintw(++cur_y, cur_x, "%d", (int) value);
      }else{
	mvprintw(++cur_y, cur_x, "%lf", value);
      }
      cur_y++;
      move(cur_y, cur_x);
    }
  }while(line_size != 0);
  
  endwin();  

  history_delete(&history);
  shunting_delete(&yard);
  return 0;
}

