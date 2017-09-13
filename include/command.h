#ifndef COMMAND_H
#define COMMAND_H

#include "history.h"
#include "shunting.h"

void handle(const char *, shunting_t *, history_t *);

#endif
