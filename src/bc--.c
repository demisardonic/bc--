#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "shunting.h"

int main(int argv, char **argc){
  shunting_t yard;
  char *line = NULL;
  size_t size;

  shunting_init(&yard);
  
  while(getline(&line, &size, stdin) > 1){
    parse(&yard, line);
    if(size_val(&yard)){
      printf("%lf\n", pop_val(&yard));
    }
  }
  
  free(line);
  shunting_delete(&yard);
  return 0;
}

