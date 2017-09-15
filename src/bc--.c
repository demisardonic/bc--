#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "command.h"
#include "history.h"
#include "parser.h"
#include "shunting.h"
#include "util.h"

void redraw_screen_offset(const history_t *history, int y_offset){

}

int main(int argv, char **argc){
  shunting_t yard;
  history_t history;
  char line[256];
  int line_size, y_index;
  int key;
  int x_offset, y_offset;
  int cur_history_cp;
  int max_width, max_height;
  int should_redraw;
  uint32_t debug_value;

  memset(line, 0, 256);
  
  shunting_init(&yard);
  history_init(&history);
  
  initscr();
  keypad(stdscr, TRUE);
  noecho();

  should_redraw = 0;
  y_index = 0;
  y_offset = x_offset = 0;
  getmaxyx(stdscr, max_height, max_width);
  debug_value = 0;
  
  //Keyboard input, count the size of the input
  do{
    line_size = 0;
    x_offset = 0;
    cur_history_cp = 0;
    do{
      if(should_redraw){
	clear_line(y_index);
	mvprintw(y_index, 0, line+x_offset);
	should_redraw = 0;
      }
      if(HAS_BIT(debug_value, DEBUG_INFO)){
	clear_line(20);
	clear_line(21);
	mvprintw(20,0,"y:%d yoff:%d xoff:%d line:%d", y_index,  y_offset, x_offset, line_size);
	mvprintw(21,0,"his:%d", cur_history_cp);
      }
      move(y_index, line_size);
      key = getch();
      
      //TODO need 256 bounds check for input line
      if(is_val(key) || is_op(key) || key == '`' || is_alpha(key)){
	line[line_size] = key;
	mvaddch(y_index, line_size-x_offset, key);
	line_size++;
	if(line_size > max_width){
	  x_offset++;
	  should_redraw = 1;
	}
      }else if(key == KEY_BACKSPACE && line_size > 0){
	line_size--;
	line[line_size] = '\0';
	should_redraw = 1;
	if(x_offset > 0){
	  x_offset--;
	}
      }else if (key == KEY_UP && cur_history_cp < history.size){
	cur_history_cp++;
	char *tmp = history.lines[history.size - cur_history_cp];
	strcpy(line, tmp);
	line_size = strlen(tmp);
	if(line_size > max_width){
	  x_offset = line_size - max_width;
	}
	should_redraw = 1;
      }else if (key == KEY_DOWN && cur_history_cp > 0){
	cur_history_cp--;
	if(!cur_history_cp){
	  memset(line, 0, 256);
	  line_size = 0;
	}else{	    
	  char *tmp = history.lines[history.size - cur_history_cp];
	  strcpy(line, tmp);
	  line_size = strlen(tmp);
	}
	if(line_size > max_width){
	  x_offset = line_size - max_width;
	}
	should_redraw = 1;
      }
    }while(key != '\n');
    
    if(line_size > 0){
      //TODO handle more calculations than vertical space allows
      if((history.size + y_offset) * 2 >= max_height){
	
      }
      
      //malloc a char * for the size of the input
      char *line_string = (char *)malloc(sizeof(char) * (line_size + 1));
      memcpy(line_string, line, line_size);
      line_string[line_size] = '\0';
      mvaddch(++y_index, 0, '>');
	
      //store that pointer within history
      if(history.size == history.length){
	history.length *= 2;
	history.lines = (char **) realloc(history.lines, sizeof(char *) * history.length);
	history.vals = (double *) realloc(history.vals, sizeof(double) * history.length);
      }
      history.lines[history.size] = line_string;

      double value = 0;
      if(line_string[0] != '`'){
	if(cur_history_cp){
	  if(line_string[0] != '`' && !strcmp(line_string, history.lines[history.size - cur_history_cp])){
	    value = history.vals[history.size - cur_history_cp];
	  }
	}else{
	  //parse that input with shunting_yard structure
	  parse(&yard, line_string);
	  value = pop_val(&yard);
	}

	print_val(y_index, 1, value, HAS_BIT(debug_value, DEBUG_FLOOR));
      }else{
	move(y_index, 1);
	handle(line_string, &yard, &history, &debug_value);
      }

      //store the calculated value in the last unused history index
      history.vals[history.size++] = value;

      move(++y_index, 0);
    }
  }while(line_size != 0);
  
  endwin();  

  history_delete(&history);
  shunting_delete(&yard);
  return 0;
}

