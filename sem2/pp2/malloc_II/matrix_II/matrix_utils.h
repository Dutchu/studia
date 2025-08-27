#ifndef MALLOC_II_MATRIX_UTILS_H
#define MALLOC_II_MATRIX_UTILS_H

struct matrix_t {
    int **ptr;
    int width;
    int height;
};

struct matrix_t* matrix_create_struct(int width, int height);

void matrix_destroy_struct(struct matrix_t **m);

int matrix_read(struct matrix_t *m);

struct matrix_t* matrix_transpose(const struct matrix_t *m);

int matrix_save_b(const struct matrix_t *m, const char *filename);

int matrix_save_t(const struct matrix_t *m, const char *filename);

#endif 
