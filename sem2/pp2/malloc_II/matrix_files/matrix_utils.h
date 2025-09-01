#pragma once

struct matrix_t {
    int **ptr;     /* row pointers (2D view) */
    int width;     /* number of columns */
    int height;    /* number of rows */
};

/* Loader matching .txt/.bin (err_code: 2 open, 3 corrupted, 4 alloc, 7 format) */
int load_matrix(const char *filename, struct matrix_t *out, int *err_code);
struct matrix_t *matrix_load_b(const char *filename, int *err_code);
struct matrix_t *matrix_load_t(const char *filename, int *err_code);

/* Basic lifecycle */
int matrix_create(struct matrix_t *m, int width, int height);
void matrix_destroy(struct matrix_t *m);
struct matrix_t *matrix_create_struct(int width, int height);
void matrix_destroy_struct(struct matrix_t **pm);

/* Ops (0 ok, nonzero on error) */
int add_m(const struct matrix_t *a, const struct matrix_t *b, struct matrix_t *out);
int sub_m(const struct matrix_t *a, const struct matrix_t *b, struct matrix_t *out);
int mul_m(const struct matrix_t *a, const struct matrix_t *b, struct matrix_t *out);

/* 5.4 helpers */
int matrix_read(struct matrix_t *m);
void matrix_display(const struct matrix_t *m);

/* 5.5 helpers */
struct matrix_t* matrix_transpose(const struct matrix_t *m);
int matrix_save_b(const struct matrix_t *m, const char *filename);
int matrix_save_t(const struct matrix_t *m, const char *filename);

/* 5.6 aliases: return new struct on success */
struct matrix_t* matrix_add(const struct matrix_t *m1, const struct matrix_t *m2);
struct matrix_t* matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2);
struct matrix_t* matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2);

void destroy_matrix(struct matrix_t *m); /* legacy alias */

/* Copy helper */
struct matrix_t* matrix_copy(const struct matrix_t *copy);
