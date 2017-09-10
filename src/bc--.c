#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "command.h"
#include "parser.h"
#include "shunting.h"

int main(int argv, char **argc){
  shunting_t yard;
  char *line = NULL;
  size_t size;

  shunting_init(&yard);
  
  while(getline(&line, &size, stdin) > 1){
    size = strlen(line);
    line[--size] = 0;
    if(line[0] == '~'){
      handle(line, &yard);
    }
    parse(&yard, line);
    if(size_val(&yard)){
      double value = pop_val(&yard);
      if(value - floor(value))
	printf("%lf\n", value);
      else
	printf("%d\n", (int)value);
    }
  }
  
  free(line);
  shunting_delete(&yard);
  return 0;
}

