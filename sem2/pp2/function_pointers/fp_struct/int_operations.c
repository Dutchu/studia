#include <stdlib.h>
#include <stdio.h>

void* add_int(const void *left, const void *right) {
    if (!left || !right) {
        return NULL;
    }
    int* res = (int*)malloc(sizeof(int));
    if (!res) {
        return NULL;
    }
    const int* a = (const int*)left;
    const int* b = (const int*)right;
    *res = *a + *b;
    return res;
}

void* sub_int(const void *left, const void *right) {
    if (!left || !right) {
        return NULL;
    }
    int* res = (int*)malloc(sizeof(int));
    if (!res) {
        return NULL;
    }
    const int* a = (const int*)left;
    const int* b = (const int*)right;
    *res = *a - *b;
    return res;
}

void* div_int(const void *left, const void *right) {
    if (!left || !right) {
        return NULL;
    }
    const int* b = (const int*)right;
    if (*b == 0) {
        return NULL;
    }
    int* res = (int*)malloc(sizeof(int));
    if (!res) {
        return NULL;
    }
    const int* a = (const int*)left;
    *res = *a / *b;
    return res;
}

void* mul_int(const void *left, const void *right) {
    if (!left || !right) {
        return NULL;
    }
    int* res = (int*)malloc(sizeof(int));
    if (!res) {
        return NULL;
    }
    const int* a = (const int*)left;
    const int* b = (const int*)right;
    *res = *a * *b;
    return res;
}

int read_int(void *a, void *b) {
    if (!a || !b) {
        return 1;
    }
    int* pa = (int*)a;
    int* pb = (int*)b;
    int r = scanf("%d %d", pa, pb);
    if (r != 2) {
        return 1;
    }
    return 0;
}

void show_int(const void *a) {
    if (!a) {
        return;
    }
    const int* pa = (const int*)a;
    printf("%d\n", *pa);
}

int is_smaller_int(const void *a, const void *b) {
    if (!a || !b) {
        return -2;
    }
    const int* pa = (const int*)a;
    const int* pb = (const int*)b;
    if (*pa < *pb) {
        return 1;
    }
    return 0;
}

