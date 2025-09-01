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

int matrix_save_transposed_b(const struct matrix_t *m, const char *filename);

int matrix_save_transposed_t(const struct matrix_t *m, const char *filename);

/* API expected by tests from task 5.4 */
int matrix_create(struct matrix_t *m, int width, int height);
void matrix_destroy(struct matrix_t *m);
int matrix_display(const struct matrix_t *m);

#endif //MALLOC_II_MATRIX_UTILS_H
