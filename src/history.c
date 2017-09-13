#include <stdlib.h>

#include "history.h"
#include "util.h"

void history_init(history_t *history){
  history->lines = (char **) malloc(sizeof(char *) * DEFAULT_LENGTH);
  history->vals = (double *) malloc(sizeof(double) * DEFAULT_LENGTH);
  history->size = 0;
  history->length = DEFAULT_LENGTH;
}

void history_delete(history_t *history){
  while(--history->size >= 0){
    free(history->lines[history->size]);
  }
  free(history->lines);
  free(history->vals);
}
