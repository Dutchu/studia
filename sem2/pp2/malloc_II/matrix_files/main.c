/* Matrix expression evaluator without using the [] operator */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_utils.h"

/* no aux structures; keep heap usage minimal */

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
    *pp = p;
    return 0;
}

static int parse_product(const char **pp, struct matrix_t *out, int *err_code) {
    struct matrix_t acc;
    acc.ptr = NULL;
    acc.height = 0;
    acc.width = 0;
    const char *p = *pp;
    if (parse_factor(&p, &acc, err_code) != 0) return -1;
    for (;;) {
        const char *q = p;
        skip_spaces(&q);
        if (*q != '*') break;
        q = q + 1;
        struct matrix_t rhs;
        rhs.ptr = NULL;
        rhs.height = 0;
        rhs.width = 0;
        if (parse_factor(&q, &rhs, err_code) != 0) {
            destroy_matrix(&acc);
            return -1;
        }
        struct matrix_t tmp;
        tmp.ptr = NULL;
        tmp.height = 0;
        tmp.width = 0;
        int mrc = mul_m(&acc, &rhs, &tmp);
        if (mrc != 0) {
            destroy_matrix(&acc);
            destroy_matrix(&rhs);
            *err_code = (mrc == -2) ? 4 : 1;
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
    char *expr = (char*)malloc(501);
    if (expr == NULL) {
        printf("Failed to allocate memory\n");
        fflush(stdout);
        return 8;
    }

    printf("Podaj wyrażenie: ");
    if (scanf("%500s", expr) != 1) {
        free(expr);
        return 0;
    }
    const char *p = expr;
    /* pre-scan for unsupported extensions anywhere in the expression */
    const char *s = expr;
    for (;;) {
        skip_spaces(&s);
        if (*s == '\0') break;
        const char *ts = s;
        while (*s != '\0' && *s != '+' && *s != '-' && *s != '*') s = s + 1;
        const char *te = s;
        if (te > ts) {
            const char *dot = NULL;
            const char *q = ts;
            while (q < te) { if (*q == '.') dot = q; q = q + 1; }
            int bad = 0;
            if (dot == NULL) bad = 1;
            else {
                long diff = (long)(te - dot);
                if (diff != 4) bad = 1; /* must be .txt or .bin */
                else {
                    char c1 = *(dot + 1);
                    char c2 = *(dot + 2);
                    char c3 = *(dot + 3);
                    int is_txt = (c1 == 't' && c2 == 'x' && c3 == 't');
                    int is_bin = (c1 == 'b' && c2 == 'i' && c3 == 'n');
                    if (!(is_txt || is_bin)) bad = 1;
                }
            }
            if (bad) {
                printf("Unsupported file format\n");
                fflush(stdout);
                free(expr);
                return 7;
            }
        }
        if (*s == '\0') break;
        s = s + 1; /* skip operator */
    }
    /* pre-scan: attempt to load every file to surface file errors before ops */
    s = expr;
    for (;;) {
        skip_spaces(&s);
        if (*s == '\0') break;
        const char *ts = s;
        while (*s != '\0' && *s != '+' && *s != '-' && *s != '*') s = s + 1;
        const char *te = s;
        if (te > ts) {
            char saved = *te;
            char *mut = (char*)te;
            *mut = '\0';
            struct matrix_t tmp; tmp.ptr = NULL; tmp.width = 0; tmp.height = 0;
            int pre_err = 0;
            int rc = load_matrix(ts, &tmp, &pre_err);
            *mut = saved;
            if (rc != 0) {
                if (pre_err == 2) { printf("Couldn't open file\n"); fflush(stdout); free(expr); return 4; }
                if (pre_err == 3) { printf("File corrupted\n"); fflush(stdout); free(expr); return 6; }
                if (pre_err == 4) { printf("Failed to allocate memory\n"); fflush(stdout); free(expr); return 8; }
                if (pre_err == 7) { printf("Unsupported file format\n"); fflush(stdout); free(expr); return 7; }
                printf("Illegal operation\n"); fflush(stdout); free(expr); return 1;
            }
            destroy_matrix(&tmp);
        }
        if (*s == '\0') break;
        s = s + 1;
    }
    int err_code = 0;
    struct matrix_t total;
    total.ptr = NULL;
    total.height = 0;
    total.width = 0;

    if (parse_product(&p, &total, &err_code) != 0) {
        free(expr);
        if (err_code == 2) { printf("Couldn't open file\n"); fflush(stdout); return 4; }
        if (err_code == 3) { printf("File corrupted\n"); fflush(stdout); return 6; }
        if (err_code == 4) { printf("Failed to allocate memory\n"); fflush(stdout); return 8; }
        if (err_code == 7) { printf("Unsupported file format\n"); fflush(stdout); return 7; }
        printf("Illegal operation\n");
        fflush(stdout);
        return 1;
    }

    for (;;) {
        skip_spaces(&p);
        char op = *p;
        if (op != '+' && op != '-') break;
        p = p + 1;

        struct matrix_t block;
        block.ptr = NULL;
        block.height = 0;
        block.width = 0;
        if (parse_product(&p, &block, &err_code) != 0) {
            destroy_matrix(&total);
            free(expr);
            if (err_code == 2) { printf("Couldn't open file\n"); fflush(stdout); return 4; }
            if (err_code == 3) { printf("File corrupted\n"); fflush(stdout); return 6; }
            if (err_code == 4) { printf("Failed to allocate memory\n"); fflush(stdout); return 8; }
            if (err_code == 7) { printf("Unsupported file format\n"); fflush(stdout); return 7; }
            printf("Illegal operation\n");
            fflush(stdout);
            return 1;
        }

        struct matrix_t tmp;
        tmp.ptr = NULL;
        tmp.height = 0;
        tmp.width = 0;
        int rc = (op == '+') ? add_m(&total, &block, &tmp) : sub_m(&total, &block, &tmp);
        if (rc != 0) {
            destroy_matrix(&total);
            destroy_matrix(&block);
            free(expr);
            if (rc == -2) { printf("Failed to allocate memory\n"); fflush(stdout); return 8; }
            printf("Illegal operation\n");
            fflush(stdout);
            return 1;
        }
        destroy_matrix(&total);
        destroy_matrix(&block);
        total = tmp;
    }

    /* print result */
    if (total.ptr != NULL) {
        int i = 0;
        while (i < total.height) {
            int j = 0;
            int *row = *(total.ptr + i);
            while (j < total.width) {
                int val = *(row + j);
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
