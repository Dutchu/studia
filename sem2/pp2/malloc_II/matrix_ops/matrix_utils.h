#ifndef MALLOC_II_MATRIX_UTILS_H
#define MALLOC_II_MATRIX_UTILS_H

struct matrix_t {
    int **ptr;
    int width;
    int height;
};

struct matrix_t *matrix_create_struct(int width, int height);

void matrix_destroy_struct(struct matrix_t **m);

struct matrix_t *matrix_copy(const struct matrix_t *m);

struct matrix_t *matrix_add(const struct matrix_t *m1, const struct matrix_t *m2);

struct matrix_t *matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2);

struct matrix_t *matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2);

struct matrix_t *matrix_load_b(const char *filename, int *err_code);

struct matrix_t *matrix_load_t(const char *filename, int *err_code);

int matrix_read(struct matrix_t *m);

void matrix_display(const struct matrix_t *m);

int matrix_save_b(const struct matrix_t *m, const char *filename);

int matrix_save_t(const struct matrix_t *m, const char *filename);


#endif //MALLOC_II_MATRIX_UTILS_H
