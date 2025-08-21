//
// Created by Bartek on 21.08.2025.
//

#include <stddef.h>
#include <malloc.h>
#include "array.h"

int is_valid(struct array_t *a);

int array_create(struct array_t *a, int N) {
    if (a == NULL) return 1;
    if (N < 1) return 1;

    a->ptr = malloc(N * sizeof(int));
    if (a->ptr == NULL) return 2;

    (a)->size = 0;
    (a)->capacity = N;

    return 0;
}

int array_push_back(struct array_t *a, int value) {
    if (!is_valid(a)) return 1;

    if (a->size == a->capacity) return 2;

    *(a->ptr + a->size) = value;
    a->size++;

    return 0;
}

void array_display(const struct array_t *a) {
    if (a == NULL ||  a->ptr == NULL || a->size < 1 || a->capacity < 1 || a->size > a->capacity) return;
    for (int i = 0; i < a->size; i++) {
        printf("%d ", *(a->ptr + i));
    }
    printf("\n");
}

void array_destroy(struct array_t *a) {
    if (a == NULL) return;

    free(a->ptr);
    a->ptr = NULL;
}

int is_valid(struct array_t *a) {
    if (a == NULL) return 0;
    if (a->size < 0 || a->capacity < 1) return 0;
    if (a->size > a->capacity) return 0;
    if (a->capacity >= 1 && a->ptr == NULL) return 0;

    return 1;
}

