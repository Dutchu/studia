#ifndef FLOAT_OPERATIONS_H
#define FLOAT_OPERATIONS_H

void* add_float(const void *left, const void *right);
void* sub_float(const void *left, const void *right);
void* div_float(const void *left, const void *right);
void* mul_float(const void *left, const void *right);

int read_float(void *a, void *b);
void show_float(const void *a);

int is_smaller_float(const void *a, const void *b);

#endif

