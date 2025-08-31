#include "matrix_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_txt_matrix(const char *filename, struct matrix_t *out, int *err_code) {
    FILE *f = fopen(filename, "rt");
    if (f == NULL) { if (err_code) *err_code = 2; return -1; }
    int r = 0, c = 0;
    if (fscanf(f, "%d %d", &r, &c) != 2) { fclose(f); if (err_code) *err_code = 3; return -1; }
    if (r < 1 || c < 1) { fclose(f); if (err_code) *err_code = 3; return -1; }
    long long total = (long long)r * (long long)c;
    if (total <= 0) { fclose(f); if (err_code) *err_code = 3; return -1; }
    int *data = (int*)malloc((size_t)total * sizeof(int));
    if (data == NULL) { fclose(f); if (err_code) *err_code = 4; return -1; }
    long long i = 0;
    while (i < total) {
        if (fscanf(f, "%d", data + i) != 1) {
            free(data);
            fclose(f);
            if (err_code) *err_code = 3;
            return -1;
        }
        i = i + 1;
    }
    fclose(f);
    out->rows = r;
    out->cols = c;
    out->data = data;
    return 0;
}

static int read_bin_matrix(const char *filename, struct matrix_t *out, int *err_code) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) { if (err_code) *err_code = 2; return -1; }
    int r = 0, c = 0;
    if (fread(&r, sizeof(int), 1, f) != 1) { fclose(f); if (err_code) *err_code = 3; return -1; }
    if (fread(&c, sizeof(int), 1, f) != 1) { fclose(f); if (err_code) *err_code = 3; return -1; }
    if (r < 1 || c < 1) { fclose(f); if (err_code) *err_code = 3; return -1; }
    long long total = (long long)r * (long long)c;
    if (total <= 0) { fclose(f); if (err_code) *err_code = 3; return -1; }
    int *data = (int*)malloc((size_t)total * sizeof(int));
    if (data == NULL) { fclose(f); if (err_code) *err_code = 4; return -1; }
    if (fread(data, sizeof(int), (size_t)total, f) != (size_t)total) {
        free(data);
        fclose(f);
        if (err_code) *err_code = 3;
        return -1;
    }
    /* check no extra data */
    int extra;
    size_t more = fread(&extra, sizeof(int), 1, f);
    if (more != 0) {
        free(data);
        fclose(f);
        if (err_code) *err_code = 3;
        return -1;
    }
    fclose(f);
    out->rows = r;
    out->cols = c;
    out->data = data;
    return 0;
}

int load_matrix(const char *filename, struct matrix_t *out, int *err_code) {
    const char *dot = strrchr(filename, '.');
    if (dot == NULL) { if (err_code) *err_code = 7; return -1; }
    if (strcmp(dot, ".txt") == 0) {
        return read_txt_matrix(filename, out, err_code);
    } else if (strcmp(dot, ".bin") == 0) {
        return read_bin_matrix(filename, out, err_code);
    } else {
        if (err_code) *err_code = 7;
        return -1;
    }
}

void destroy_matrix(struct matrix_t *m) {
    if (m == NULL) return;
    if (m->data != NULL) {
        free(m->data);
        m->data = NULL;
    }
    m->rows = 0;
    m->cols = 0;
}

int add_m(const struct matrix_t *a, const struct matrix_t *b, struct matrix_t *out) {
    if (a->rows != b->rows || a->cols != b->cols) return -1;
    long long total = (long long)a->rows * (long long)a->cols;
    int *data = (int*)malloc((size_t)total * sizeof(int));
    if (data == NULL) return -2;
    long long i = 0;
    while (i < total) {
        *(data + i) = *(a->data + i) + *(b->data + i);
        i = i + 1;
    }
    out->rows = a->rows;
    out->cols = a->cols;
    out->data = data;
    return 0;
}

int sub_m(const struct matrix_t *a, const struct matrix_t *b, struct matrix_t *out) {
    if (a->rows != b->rows || a->cols != b->cols) return -1;
    long long total = (long long)a->rows * (long long)a->cols;
    int *data = (int*)malloc((size_t)total * sizeof(int));
    if (data == NULL) return -2;
    long long i = 0;
    while (i < total) {
        *(data + i) = *(a->data + i) - *(b->data + i);
        i = i + 1;
    }
    out->rows = a->rows;
    out->cols = a->cols;
    out->data = data;
    return 0;
}

int mul_m(const struct matrix_t *a, const struct matrix_t *b, struct matrix_t *out) {
    if (a->cols != b->rows) return -1;
    long long total = (long long)a->rows * (long long)b->cols;
    int *data = (int*)malloc((size_t)total * sizeof(int));
    if (data == NULL) return -2;
    int i = 0;
    while (i < a->rows) {
        int j = 0;
        while (j < b->cols) {
            long long sum = 0;
            int k = 0;
            while (k < a->cols) {
                long long ia = (long long)i * a->cols + k;
                long long ib = (long long)k * b->cols + j;
                sum += (long long)(*(a->data + ia)) * (long long)(*(b->data + ib));
                k = k + 1;
            }
            *(data + ((long long)i * b->cols + j)) = (int)sum;
            j = j + 1;
        }
        i = i + 1;
    }
    out->rows = a->rows;
    out->cols = b->cols;
    out->data = data;
    return 0;
}

