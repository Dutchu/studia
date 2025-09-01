#ifndef MY_IO_H
#define MY_IO_H

#include <stdarg.h>

struct point_t {
    int x;
    int y;
};

int my_printf(char *format, ...);
int my_scanf(char *format, ...);

#endif // MY_IO_H
