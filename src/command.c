#include <stdio.h>
#include <string.h>

#include "command.h"
#include "history.h"
#include "shunting.h"

void handle(const char *line, shunting_t *yard, history_t *history){
  if(!strcmp("`printVal", line)){
    print_val_stack(yard);
  }else if(!strcmp("`printOp", line)){
    print_op_stack(yard);
  }
}
