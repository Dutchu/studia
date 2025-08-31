#pragma once

struct matrix_t {
    int rows;
    int cols;
    int *data;
};

int load_matrix(const char *filename, struct matrix_t *out, int *err_code);
void destroy_matrix(struct matrix_t *m);

int add_m(const struct matrix_t *a, const struct matrix_t *b, struct matrix_t *out);
int sub_m(const struct matrix_t *a, const struct matrix_t *b, struct matrix_t *out);
int mul_m(const struct matrix_t *a, const struct matrix_t *b, struct matrix_t *out);

