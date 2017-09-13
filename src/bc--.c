#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "command.h"
#include "parser.h"
#include "shunting.h"
#include "util.h"

void draw_newest_history(shunting_t *yard, const char **history, int size){
  int height, cur_x;
  getmaxyx(stdscr, height, cur_x);
  cur_x = 0;
  clear();
  int history_from = size - (height / 2);
  int cur_y = 0;

  while(history_from < size){
    mvprintw(cur_y++, cur_x, history[history_from]);
    parse(yard, history[history_from]);
    double value = pop_val(yard);
    if(value == floor(value)){
      mvprintw(++cur_y, cur_x, "%d", (int) value);
    }else{
      mvprintw(++cur_y, cur_x, "%lf", value);
    }
    cur_y++;
    move(cur_y, cur_x);    
  }
}

int main(int argv, char **argc){
  shunting_t yard;
  char **history;
  double *val_history;
  int history_length, history_size;
  char line[256];
  int line_size;
  int key, cur_y, cur_x;
  int max_width, max_height;

  getmaxyx(stdscr, max_height, max_width);

  memset(line, 0, 256);
  
  history_length = DEFAULT_LENGTH;
  history_size = 0;
  history = (char **)malloc(sizeof(char *) * history_length);
  val_history = (double *) malloc(sizeof(double) * history_length);
  
  shunting_init(&yard);

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
      if(history_size * 2 > max_height){

      }
      
      //malloc a char * for the size of the input
      char *line_string = (char *)malloc(sizeof(char) * (line_size + 1));
      memcpy(line_string, line, line_size);
      line_string[line_size] = '\0';
      cur_x = 0;
      //store that pointer within history
      if(history_size == history_length){
	history_length *= 2;
	history = (char **) realloc(history, sizeof(char *) * history_length);
	val_history = (double *) realloc(val_history, sizeof(double) * history_length);
      }
      history[history_size] = line_string;
      
      //parse that input with shunting_yard structure
      parse(&yard, line_string);
      double value = pop_val(&yard);

      val_history[history_size] = value;
      history_size++;

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

  //free every string in the history
  while(history_size > 0){
    free(history[--history_size]);
  }
  //free the history array;
  free(history);
  shunting_delete(&yard);
  return 0;
}

