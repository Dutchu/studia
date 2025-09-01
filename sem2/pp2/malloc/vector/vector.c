//
// Created by Bartek on 17.08.2025.
//

#include <stddef.h>
#include <malloc.h>
#include "vector.h"

int is_valid(struct vector_t *a);

int vector_create_struct(struct vector_t **a, int N) {
    if (a == NULL) return 1;
    if (N < 1) return 1;

    struct vector_t *v = malloc(sizeof(struct vector_t));
    if (v == NULL) return 2;

    if (vector_create(v, N) != 0) {
        free(v);
        return 2;
    }

    *a = v;

    return 0;
}

void vector_destroy_struct(struct vector_t **a) {
    if (a == NULL || *a == NULL) return;

    vector_destroy(*a);

    free(*a);
    (*a) = NULL;
}

int vector_create(struct vector_t *a, int N) {
    if (a == NULL) return 1;
    if (N < 1) return 1;

    a->ptr = malloc(N * sizeof(int));
    if (a->ptr == NULL) return 2;

    (a)->size = 0;
    (a)->capacity = N;

    return 0;
}

void vector_destroy(struct vector_t *a) {
    if (a == NULL) return;

    free(a->ptr);
    a->ptr = NULL;
}

void vector_display(const struct vector_t *a) {
    if (a == NULL ||  a->ptr == NULL || a->size < 1 || a->capacity < 1 || a->size > a->capacity) return;
    for (int i = 0; i < a->size; i++) {
        printf("%d ", *(a->ptr + i));
    }
    printf("\n");
}

int vector_push_back(struct vector_t *a, int value) {
    if (!is_valid(a)) return 1;

    if (a->size == a->capacity) {

        int new_capacity = 2 * a->capacity;
        int *new_vector = realloc(a->ptr, 2 * a->capacity * sizeof(int));

        if (new_vector == NULL) return 2;

        a->ptr = new_vector;
        a->capacity = new_capacity;
    }

    *(a->ptr + a->size) = value;
    a->size++;

    return 0;
}

int vector_erase(struct vector_t *a, int value) {
    if (!is_valid(a)) return -1;

    float threshold = 0.25f;
    int *values = a->ptr;
    int current;
    int count = 0;

    for (int i = 0; i < a->size;) {
        current = *(values + i);
        if (current == value) {
            for (int j = i; j < a->size - 1; j++) {
                *(values + j) = *(values + j + 1);
            }
            a->size--;
            count++;
        } else {
            i++;
        }
    }


    float occupied = (float) a->size / a->capacity;

    if (occupied < threshold) {
        a->capacity = a->capacity / 2;
    }
    if (a->capacity < 1) a->capacity = 1;

    return count;
}

int is_valid(struct vector_t *a) {
    if (a == NULL) return 0;
    if (a->size < 0 || a->capacity < 1) return 0;
    if (a->size > a->capacity) return 0;
    if (a->capacity >= 1 && a->ptr == NULL) return 0;

    return 1;
}
