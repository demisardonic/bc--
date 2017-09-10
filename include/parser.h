#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#include "shunting.h"

void parse(shunting_t *, char *);
int parse_val(char *, int, int, char *);

#endif
