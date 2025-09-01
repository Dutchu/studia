#ifndef INT_OPERATIONS_H
#define INT_OPERATIONS_H

void* add_int(const void *left, const void *right);
void* sub_int(const void *left, const void *right);
void* div_int(const void *left, const void *right);
void* mul_int(const void *left, const void *right);

int read_int(void *a, void *b);
void show_int(const void *a);

int is_smaller_int(const void *a, const void *b);

#endif

