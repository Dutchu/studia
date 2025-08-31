/* Matrix expression evaluator without using the [] operator */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_utils.h"

static void skip_spaces(const char **pp) {
    const char *p = *pp;
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') {
        p = p + 1;
    }
    *pp = p;
}

static int parse_factor(const char **pp, struct matrix_t *out, int *err_code) {
    const char *p = *pp;
    skip_spaces(&p);
    if (*p == '\0') return -1;
    const char *start = p;
    while (*p != '\0' && *p != '+' && *p != '-' && *p != '*') {
        p = p + 1;
    }
    char saved = *p;
    char *mutable_end = (char*)p;
    *mutable_end = '\0';
    int rc = load_matrix(start, out, err_code);
    *mutable_end = saved;
    if (rc != 0) return -1;
    if (saved != '\0') p = p + 1;
    *pp = p;
    return 0;
}

static int parse_product(const char **pp, struct matrix_t *out, int *err_code) {
    struct matrix_t acc;
    acc.data = NULL;
    acc.rows = 0;
    acc.cols = 0;
    const char *p = *pp;
    if (parse_factor(&p, &acc, err_code) != 0) return -1;
    for (;;) {
        const char *q = p;
        skip_spaces(&q);
        if (*q != '*') break;
        q = q + 1;
        struct matrix_t rhs;
        rhs.data = NULL;
        rhs.rows = 0;
        rhs.cols = 0;
        if (parse_factor(&q, &rhs, err_code) != 0) {
            destroy_matrix(&acc);
            return -1;
        }
        struct matrix_t tmp;
        tmp.data = NULL;
        tmp.rows = 0;
        tmp.cols = 0;
        if (mul_m(&acc, &rhs, &tmp) != 0) {
            destroy_matrix(&acc);
            destroy_matrix(&rhs);
            *err_code = 1;
            return -1;
        }
        destroy_matrix(&acc);
        destroy_matrix(&rhs);
        acc = tmp;
        p = q;
    }
    *out = acc;
    *pp = p;
    return 0;
}

int main(void) {
    char *expr = (char*)malloc(501u);
    if (expr == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj wyrażenie: ");
    if (scanf("%500s", expr) != 1) {
        free(expr);
        return 0;
    }

    const char *p = expr;
    int err_code = 0;
    struct matrix_t total;
    total.data = NULL;
    total.rows = 0;
    total.cols = 0;

    if (parse_product(&p, &total, &err_code) != 0) {
        free(expr);
        if (err_code == 2) { printf("Couldn't open file\n"); return 4; }
        if (err_code == 3) { printf("File corrupted\n"); return 6; }
        if (err_code == 4) { printf("Failed to allocate memory\n"); return 8; }
        if (err_code == 7) { printf("Unsupported file format\n"); return 7; }
        printf("Illegal operation\n");
        return 1;
    }

    for (;;) {
        skip_spaces(&p);
        char op = *p;
        if (op != '+' && op != '-') break;
        p = p + 1;

        struct matrix_t block;
        block.data = NULL;
        block.rows = 0;
        block.cols = 0;
        if (parse_product(&p, &block, &err_code) != 0) {
            destroy_matrix(&total);
            free(expr);
            if (err_code == 2) { printf("Couldn't open file\n"); return 4; }
            if (err_code == 3) { printf("File corrupted\n"); return 6; }
            if (err_code == 4) { printf("Failed to allocate memory\n"); return 8; }
            if (err_code == 7) { printf("Unsupported file format\n"); return 7; }
            printf("Illegal operation\n");
            return 1;
        }

        struct matrix_t tmp;
        tmp.data = NULL;
        tmp.rows = 0;
        tmp.cols = 0;
        int rc = (op == '+') ? add_m(&total, &block, &tmp) : sub_m(&total, &block, &tmp);
        if (rc != 0) {
            destroy_matrix(&total);
            destroy_matrix(&block);
            free(expr);
            printf("Illegal operation\n");
            return 1;
        }
        destroy_matrix(&total);
        destroy_matrix(&block);
        total = tmp;
    }

    /* print result */
    if (total.data != NULL) {
        int i = 0;
        while (i < total.rows) {
            int j = 0;
            while (j < total.cols) {
                long idx = (long)i * total.cols + j;
                int val = *(total.data + idx);
                if (j > 0) printf(" ");
                printf("%d", val);
                j = j + 1;
            }
            printf("\n");
            i = i + 1;
        }
    }

    destroy_matrix(&total);
    free(expr);
    return 0;
}
