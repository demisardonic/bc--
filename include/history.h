#ifndef HISTORY_H
#define HISTORY_H

typedef struct history{
  char **lines;
  double *vals;
  int length;
  int size;
} history_t;

void history_init(history_t *history);

void history_delete(history_t *history);

#endif
