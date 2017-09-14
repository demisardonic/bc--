#ifndef COMMAND_H
#define COMMAND_H

#include <stdint.h>

#include "history.h"
#include "shunting.h"

void handle(const char *, shunting_t *, history_t *, uint32_t *);

#endif
