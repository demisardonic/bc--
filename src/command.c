#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "command.h"
#include "history.h"
#include "shunting.h"
#include "util.h"

void handle(const char *line, shunting_t *yard, history_t *history, uint32_t *debug_value){
  if(!strcmp("`printVal", line)){
    print_val_stack(yard);
  }else if(!strcmp("`printOp", line)){
    print_op_stack(yard);
  }else if(!strcmp("`debug", line)){
    *debug_value ^= DEBUG_INFO;
    if(HAS_BIT(*debug_value, DEBUG_INFO)){
      printw("Debug activated.");
    }else{
      printw("Debug deactivated.");
      clear_line(20);
      clear_line(21);
    }
  }
}
