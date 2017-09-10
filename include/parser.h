#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#include "shunting.h"

void parse(shunting_t *, const char *);
int parse_val(const char *, const int, int, char *);

#endif
