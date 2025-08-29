#ifndef COMPLEX_OPERATIONS_H
#define COMPLEX_OPERATIONS_H

struct complex_t {
    float re;
    float im;
};

void* add_complex(const void *left, const void *right);
void* sub_complex(const void *left, const void *right);
void* div_complex(const void *left, const void *right);
void* mul_complex(const void *left, const void *right);

int read_complex(void *a, void *b);
void show_complex(const void *a);

int is_smaller_complex(const void *a, const void *b);

#endif

