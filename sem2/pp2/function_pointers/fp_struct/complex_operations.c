#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "complex_operations.h"

static int read_one_complex(struct complex_t* out) {
    if (!out) {
        return 1;
    }
    float re = 0.0f;
    int r1 = scanf("%f", &re);
    if (r1 != 1) {
        return 1;
    }
    char sign = 0;
    int r2 = scanf(" %c", &sign);
    if (r2 != 1) {
        return 1;
    }
    if (!(sign == '+' || sign == '-')) {
        return 1;
    }
    char ich = 0;
    int r3 = scanf(" %c", &ich);
    if (r3 != 1) {
        return 1;
    }
    if (ich != 'i') {
        return 1;
    }
    int ch = getchar();
    while (ch == ' ' || ch == '\t') {
        ch = getchar();
    }
    if (ch == '+' || ch == '-') {
        return 1;
    }
    if (ch == EOF) {
        return 1;
    }
    ungetc(ch, stdin);
    float im = 0.0f;
    int r4 = scanf("%f", &im);
    if (r4 != 1) {
        return 1;
    }
    if (sign == '-') {
        im = -im;
    }
    out->re = re;
    out->im = im;
    return 0;
}

void* add_complex(const void *left, const void *right) {
    if (!left || !right) {
        return NULL;
    }
    const struct complex_t* a = (const struct complex_t*)left;
    const struct complex_t* b = (const struct complex_t*)right;
    struct complex_t* res = (struct complex_t*)malloc(sizeof(struct complex_t));
    if (!res) {
        return NULL;
    }
    res->re = a->re + b->re;
    res->im = a->im + b->im;
    return res;
}

void* sub_complex(const void *left, const void *right) {
    if (!left || !right) {
        return NULL;
    }
    const struct complex_t* a = (const struct complex_t*)left;
    const struct complex_t* b = (const struct complex_t*)right;
    struct complex_t* res = (struct complex_t*)malloc(sizeof(struct complex_t));
    if (!res) {
        return NULL;
    }
    res->re = a->re - b->re;
    res->im = a->im - b->im;
    return res;
}

void* mul_complex(const void *left, const void *right) {
    if (!left || !right) {
        return NULL;
    }
    const struct complex_t* a = (const struct complex_t*)left;
    const struct complex_t* b = (const struct complex_t*)right;
    struct complex_t* res = (struct complex_t*)malloc(sizeof(struct complex_t));
    if (!res) {
        return NULL;
    }
    float r = a->re * b->re - a->im * b->im;
    float i = a->re * b->im + a->im * b->re;
    res->re = r;
    res->im = i;
    return res;
}

void* div_complex(const void *left, const void *right) {
    if (!left || !right) {
        return NULL;
    }
    const struct complex_t* a = (const struct complex_t*)left;
    const struct complex_t* b = (const struct complex_t*)right;
    float denom = b->re * b->re + b->im * b->im;
    if (denom == 0.0f) {
        return NULL;
    }
    struct complex_t* res = (struct complex_t*)malloc(sizeof(struct complex_t));
    if (!res) {
        return NULL;
    }
    float r = (a->re * b->re + a->im * b->im) / denom;
    float i = (a->im * b->re - a->re * b->im) / denom;
    res->re = r;
    res->im = i;
    return res;
}

int read_complex(void *a, void *b) {
    if (!a || !b) {
        return 1;
    }
    struct complex_t* pa = (struct complex_t*)a;
    struct complex_t* pb = (struct complex_t*)b;
    int r1 = read_one_complex(pa);
    if (r1 != 0) {
        return 1;
    }
    int r2 = read_one_complex(pb);
    if (r2 != 0) {
        return 1;
    }
    return 0;
}

void show_complex(const void *a) {
    if (!a) {
        return;
    }
    const struct complex_t* p = (const struct complex_t*)a;
    float re = p->re;
    float im = p->im;
    char sign = '+';
    float abs_im = im;
    if (im < 0.0f) {
        sign = '-';
        abs_im = -im;
    }
    printf("%.6f %c i%.6f\n", re, sign, abs_im);
}

int is_smaller_complex(const void *a, const void *b) {
    if (!a || !b) {
        return -2;
    }
    const struct complex_t* pa = (const struct complex_t*)a;
    const struct complex_t* pb = (const struct complex_t*)b;
    float ma = pa->re * pa->re + pa->im * pa->im;
    float mb = pb->re * pb->re + pb->im * pb->im;
    if (ma < mb) {
        return 1;
    }
    return 0;
}
