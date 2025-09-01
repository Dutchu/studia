#include "matrix_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int *matrix_data_ptr(const struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->height < 1) return NULL;
    return (int*)((char*)m->ptr + (size_t)m->height * sizeof(int*));
}

static int read_txt_matrix(const char *filename, struct matrix_t *out, int *err_code) {
    FILE *f = fopen(filename, "rt");
    if (f == NULL) { if (err_code) *err_code = 2; return -1; }
    /* Test generators for .txt store dimensions as rows then columns */
    int rows = 0, cols = 0;
    if (fscanf(f, "%d %d", &rows, &cols) != 2) { fclose(f); if (err_code) *err_code = 3; return -1; }
    if (rows < 1 || cols < 1) { fclose(f); if (err_code) *err_code = 3; return -1; }
    long long total = (long long)rows * (long long)cols;
    if (total <= 0) { fclose(f); if (err_code) *err_code = 3; return -1; }
    /* Our matrix uses width=cols, height=rows */
    if (matrix_create(out, cols, rows) != 0) { fclose(f); if (err_code) *err_code = 4; return -1; }
    long long i = 0;
    while (i < total) {
        int *data = matrix_data_ptr(out);
        if (data == NULL) { matrix_destroy(out); fclose(f); if (err_code) *err_code = 4; return -1; }
        if (fscanf(f, "%d", data + i) != 1) {
            matrix_destroy(out);
            fclose(f);
            if (err_code) *err_code = 3;
            return -1;
        }
        i = i + 1;
    }
    /* ensure no extra non-whitespace content present */
    int ch;
    do {
        ch = fgetc(f);
    } while (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');
    if (ch != EOF) {
        matrix_destroy(out);
        fclose(f);
        if (err_code) *err_code = 3;
        return -1;
    }
    fclose(f);
    return 0;
}

static int read_bin_matrix(const char *filename, struct matrix_t *out, int *err_code) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) { if (err_code) *err_code = 2; return -1; }
    int w = 0, h = 0;
    if (fread(&w, sizeof(int), 1, f) != 1) { fclose(f); if (err_code) *err_code = 3; return -1; }
    if (fread(&h, sizeof(int), 1, f) != 1) { fclose(f); if (err_code) *err_code = 3; return -1; }
    if (w < 1 || h < 1) { fclose(f); if (err_code) *err_code = 3; return -1; }
    long long total = (long long)w * (long long)h;
    if (total <= 0) { fclose(f); if (err_code) *err_code = 3; return -1; }
    if (matrix_create(out, w, h) != 0) { fclose(f); if (err_code) *err_code = 4; return -1; }
    int *data = matrix_data_ptr(out);
    if (data == NULL) { fclose(f); if (err_code) *err_code = 4; return -1; }
    if (fread(data, sizeof(int), (size_t)total, f) != (size_t)total) {
        matrix_destroy(out);
        fclose(f);
        if (err_code) *err_code = 3;
        return -1;
    }
    /* check no extra data */
    int extra;
    size_t more = fread(&extra, sizeof(int), 1, f);
    if (more != 0) {
        matrix_destroy(out);
        fclose(f);
        if (err_code) *err_code = 3;
        return -1;
    }
    fclose(f);
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

int matrix_create(struct matrix_t *m, int width, int height) {
    if (m == NULL || height < 1 || width < 1) return 1;
    long long total = (long long)height * (long long)width;
    m->width = width;
    m->height = height;
    m->ptr = NULL;
    size_t rows_bytes = (size_t)height * sizeof(int*);
    size_t data_bytes = (size_t)total * sizeof(int);
    void *block = malloc(rows_bytes + data_bytes);
    if (block == NULL) return 2;
    int **rows = (int**)block;
    int *data = (int*)((char*)block + rows_bytes);
    int i = 0;
    while (i < height) {
        *(rows + i) = data + (long long)i * width;
        i = i + 1;
    }
    m->ptr = rows;
    return 0;
}

void matrix_destroy(struct matrix_t *m) {
    if (m == NULL) return;
    if (m->ptr != NULL) { free(m->ptr); m->ptr = NULL; }
    m->height = 0;
    m->width = 0;
}

void destroy_matrix(struct matrix_t *m) { /* legacy alias */
    matrix_destroy(m);
}

struct matrix_t *matrix_create_struct(int width, int height) {
    struct matrix_t *m = (struct matrix_t*)malloc(sizeof(struct matrix_t));
    if (m == NULL) return NULL;
    m->ptr = NULL;
    m->width = 0;
    m->height = 0;
    int rc = matrix_create(m, width, height);
    if (rc != 0) { free(m); return NULL; }
    return m;
}

void matrix_destroy_struct(struct matrix_t **pm) {
    if (pm == NULL || *pm == NULL) return;
    matrix_destroy(*pm);
    free(*pm);
    *pm = NULL;
}

int add_m(const struct matrix_t *a, const struct matrix_t *b, struct matrix_t *out) {
    if (a->height != b->height || a->width != b->width) return -1;
    long long total = (long long)a->height * (long long)a->width;
    if (matrix_create(out, a->width, a->height) != 0) return -2;
    long long i = 0;
    while (i < total) {
        int *ao = matrix_data_ptr(a);
        int *bo = matrix_data_ptr(b);
        int *oo = matrix_data_ptr(out);
        if (ao == NULL || bo == NULL || oo == NULL) return -2;
        *(oo + i) = *(ao + i) + *(bo + i);
        i = i + 1;
    }
    return 0;
}

int sub_m(const struct matrix_t *a, const struct matrix_t *b, struct matrix_t *out) {
    if (a->height != b->height || a->width != b->width) return -1;
    long long total = (long long)a->height * (long long)a->width;
    if (matrix_create(out, a->width, a->height) != 0) return -2;
    long long i = 0;
    while (i < total) {
        int *ao = matrix_data_ptr(a);
        int *bo = matrix_data_ptr(b);
        int *oo = matrix_data_ptr(out);
        if (ao == NULL || bo == NULL || oo == NULL) return -2;
        *(oo + i) = *(ao + i) - *(bo + i);
        i = i + 1;
    }
    return 0;
}

int mul_m(const struct matrix_t *a, const struct matrix_t *b, struct matrix_t *out) {
    if (a->width != b->height) return -1;
    if (matrix_create(out, b->width, a->height) != 0) return -2;
    int i = 0;
    while (i < a->height) {
        int j = 0;
        while (j < b->width) {
            long long sum = 0;
            int k = 0;
            while (k < a->width) {
                long long ia = (long long)i * a->width + k;
                long long ib = (long long)k * b->width + j;
                int *ad = matrix_data_ptr(a);
                int *bd = matrix_data_ptr(b);
                if (ad == NULL || bd == NULL) return -2;
                sum += (long long)(*(ad + ia)) * (long long)(*(bd + ib));
                k = k + 1;
            }
            int *od = matrix_data_ptr(out);
            if (od == NULL) return -2;
            *(od + ((long long)i * b->width + j)) = (int)sum;
            j = j + 1;
        }
        i = i + 1;
    }
    return 0;
}

/* aliases expected by some unit sets */
/* removed old int-returning aliases; pointer-returning versions provided below */

struct matrix_t *matrix_load_b(const char *filename, int *err_code) {
    if (filename == NULL) { if (err_code) *err_code = 1; return NULL; }
    struct matrix_t *m = (struct matrix_t*)malloc(sizeof(struct matrix_t));
    if (m == NULL) { if (err_code) *err_code = 4; return NULL; }
    m->ptr = NULL; m->width = 0; m->height = 0;
    if (read_bin_matrix(filename, m, err_code) != 0) { free(m); return NULL; }
    if (err_code) *err_code = 0;
    return m;
}

struct matrix_t *matrix_load_t(const char *filename, int *err_code) {
    if (filename == NULL) { if (err_code) *err_code = 1; return NULL; }
    struct matrix_t *m = (struct matrix_t*)malloc(sizeof(struct matrix_t));
    if (m == NULL) { if (err_code) *err_code = 4; return NULL; }
    m->ptr = NULL; m->width = 0; m->height = 0;
    if (read_txt_matrix(filename, m, err_code) != 0) { free(m); return NULL; }
    if (err_code) *err_code = 0;
    return m;
}

int matrix_read(struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) return 1;
    long long total = (long long)m->width * (long long)m->height;
    long long i = 0;
    while (i < total) {
        int tmp;
        if (scanf("%d", &tmp) != 1) return 2;
        int *data = matrix_data_ptr(m);
        if (data == NULL) return 2;
        *(data + i) = tmp;
        i = i + 1;
    }
    return 0;
}

void matrix_display(const struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) return;
    int i = 0;
    while (i < m->height) {
        int j = 0;
        int *row = *(m->ptr + i);
        while (j < m->width) {
            if (j > 0) printf(" ");
            printf("%d", *(row + j));
            j = j + 1;
        }
        printf("\n");
        i = i + 1;
    }
}

struct matrix_t* matrix_transpose(const struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) return NULL;
    struct matrix_t *t = matrix_create_struct(m->height, m->width);
    if (t == NULL) return NULL;
    int i = 0;
    while (i < m->height) {
        int j = 0;
        while (j < m->width) {
            int *td = matrix_data_ptr(t);
            int *md = matrix_data_ptr(m);
            if (td == NULL || md == NULL) { matrix_destroy_struct(&t); return NULL; }
            *(td + (long long)j * t->width + i) = *(md + (long long)i * m->width + j);
            j = j + 1;
        }
        i = i + 1;
    }
    return t;
}

int matrix_save_b(const struct matrix_t *m, const char *filename) {
    if (m == NULL || filename == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) return 1;
    FILE *f = fopen(filename, "wb");
    if (f == NULL) return 2;
    size_t w1 = fwrite(&m->width, sizeof(int), 1, f);
    size_t w2 = fwrite(&m->height, sizeof(int), 1, f);
    long long total = (long long)m->width * (long long)m->height;
    int *data2 = matrix_data_ptr(m);
    if (data2 == NULL) { fclose(f); return 1; }
    size_t w3 = fwrite(data2, sizeof(int), (size_t)total, f);
    int ok = (w1 == 1 && w2 == 1 && w3 == (size_t)total) ? 0 : 3;
    fclose(f);
    return ok;
}

int matrix_save_t(const struct matrix_t *m, const char *filename) {
    if (m == NULL || filename == NULL || m->ptr == NULL || m->width < 1 || m->height < 1) return 1;
    FILE *f = fopen(filename, "wt");
    if (f == NULL) return 2;
    if (fprintf(f, "%d %d\n", m->width, m->height) < 0) { fclose(f); return 3; }
    int i = 0;
    while (i < m->height) {
        int j = 0;
        int *row = *(m->ptr + i);
        while (j < m->width) {
            if (j > 0) { if (fputc(' ', f) == EOF) { fclose(f); return 3; } }
            if (fprintf(f, "%d", *(row + j)) < 0) { fclose(f); return 3; }
            j = j + 1;
        }
        if (fputc('\n', f) == EOF) { fclose(f); return 3; }
        i = i + 1;
    }
    fclose(f);
    return 0;
}

struct matrix_t* matrix_copy(const struct matrix_t *copy) {
    if (copy == NULL || copy->ptr == NULL || copy->width < 1 || copy->height < 1) return NULL;
    struct matrix_t *dst = matrix_create_struct(copy->width, copy->height);
    if (dst == NULL) return NULL;
    long long total = (long long)copy->width * (long long)copy->height;
    long long i = 0;
    int *dd = matrix_data_ptr(dst);
    int *cd = matrix_data_ptr(copy);
    if (dd == NULL || cd == NULL) { matrix_destroy_struct(&dst); return NULL; }
    while (i < total) { *(dd + i) = *(cd + i); i = i + 1; }
    return dst;
}

struct matrix_t* matrix_add(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (m1 == NULL || m2 == NULL) return NULL;
    struct matrix_t tmp; tmp.ptr = NULL; tmp.width = 0; tmp.height = 0;
    int rc = add_m(m1, m2, &tmp);
    if (rc != 0) { matrix_destroy(&tmp); return NULL; }
    struct matrix_t *out = (struct matrix_t*)malloc(sizeof(struct matrix_t));
    if (out == NULL) { matrix_destroy(&tmp); return NULL; }
    out->width = tmp.width; out->height = tmp.height; out->ptr = tmp.ptr;
    return out;
}

struct matrix_t* matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (m1 == NULL || m2 == NULL) return NULL;
    struct matrix_t tmp; tmp.ptr = NULL; tmp.width = 0; tmp.height = 0;
    int rc = sub_m(m1, m2, &tmp);
    if (rc != 0) { matrix_destroy(&tmp); return NULL; }
    struct matrix_t *out = (struct matrix_t*)malloc(sizeof(struct matrix_t));
    if (out == NULL) { matrix_destroy(&tmp); return NULL; }
    out->width = tmp.width; out->height = tmp.height; out->ptr = tmp.ptr;
    return out;
}

struct matrix_t* matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2) {
    if (m1 == NULL || m2 == NULL) return NULL;
    struct matrix_t tmp; tmp.ptr = NULL; tmp.width = 0; tmp.height = 0;
    int rc = mul_m(m1, m2, &tmp);
    if (rc != 0) { matrix_destroy(&tmp); return NULL; }
    struct matrix_t *out = (struct matrix_t*)malloc(sizeof(struct matrix_t));
    if (out == NULL) { matrix_destroy(&tmp); return NULL; }
    out->width = tmp.width; out->height = tmp.height; out->ptr = tmp.ptr;
    return out;
}
