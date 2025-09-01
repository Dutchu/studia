#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stddef.h>

typedef void* (*binary_op_t)(const void*, const void*);
typedef int (*read_func_t)(void*, void*);
typedef void (*show_func_t)(const void*);

struct operations_t {
    binary_op_t add;
    binary_op_t sub;
    binary_op_t div;
    binary_op_t mul;
    read_func_t read;
    show_func_t show;
};

void* find_extremum(const void *a,
                    const void *b,
                    const struct operations_t *op,
                    int(* comp)(const void *, const void *));

#endif

