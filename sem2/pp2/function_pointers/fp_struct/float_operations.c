#include <stdlib.h>
#include <stdio.h>

void* add_float(const void *left, const void *right) {
    if (!left || !right) {
        return NULL;
    }
    float* res = (float*)malloc(sizeof(float));
    if (!res) {
        return NULL;
    }
    const float* a = (const float*)left;
    const float* b = (const float*)right;
    *res = *a + *b;
    return res;
}

void* sub_float(const void *left, const void *right) {
    if (!left || !right) {
        return NULL;
    }
    float* res = (float*)malloc(sizeof(float));
    if (!res) {
        return NULL;
    }
    const float* a = (const float*)left;
    const float* b = (const float*)right;
    *res = *a - *b;
    return res;
}

void* div_float(const void *left, const void *right) {
    if (!left || !right) {
        return NULL;
    }
    const float* b = (const float*)right;
    if (*b == 0.0f) {
        return NULL;
    }
    float* res = (float*)malloc(sizeof(float));
    if (!res) {
        return NULL;
    }
    const float* a = (const float*)left;
    *res = *a / *b;
    return res;
}

void* mul_float(const void *left, const void *right) {
    if (!left || !right) {
        return NULL;
    }
    float* res = (float*)malloc(sizeof(float));
    if (!res) {
        return NULL;
    }
    const float* a = (const float*)left;
    const float* b = (const float*)right;
    *res = *a * *b;
    return res;
}

int read_float(void *a, void *b) {
    if (!a || !b) {
        return 1;
    }
    float* pa = (float*)a;
    float* pb = (float*)b;
    int r = scanf("%f %f", pa, pb);
    if (r != 2) {
        return 1;
    }
    return 0;
}

void show_float(const void *a) {
    if (!a) {
        return;
    }
    const float* pa = (const float*)a;
    printf("%f\n", *pa);
}

int is_smaller_float(const void *a, const void *b) {
    if (!a || !b) {
        return -2;
    }
    const float* pa = (const float*)a;
    const float* pb = (const float*)b;
    if (*pa < *pb) {
        return 1;
    }
    return 0;
}

