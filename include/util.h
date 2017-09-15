#ifndef UTIL_H
#define UTIL_H

#define DEFAULT_LENGTH 10

#define DEBUG_INFO  0x0001
#define DEBUG_FLOOR 0x0002
#define DEBUG_3 0x0004
#define DEBUG_4 0x0008
#define DEBUG_5 0x0010
#define DEBUG_6 0x0020
#define DEBUG_7 0x0040
#define DEBUG_8 0x0080

#define HAS_BIT(x, y) (!(~x & y))

int op_to_pres(char);
int is_val(char);
int is_op(char);
int is_alpha(char);
void print_val(int, int, double, int);
void clear_line(int);

#endif
