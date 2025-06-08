#include <stdlib.h>
#include <stdio.h>
#include "circular_buffer.h"

int circular_buffer_create(struct circular_buffer_t *a, int N) {
    if (a == NULL || N < 1) {
        return 1;
    }

    a->ptr = malloc(N * sizeof(*(a->ptr)));
    if (a->ptr == NULL) {
        return 2;
    }

    a->capacity = N;
    a->begin = 0;
    a->end = 0;
    a->full = 0;

    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N) {
    if (cb == NULL || N < 1) {
        return 1;
    }

    *cb = malloc(sizeof(struct circular_buffer_t));
    if (*cb == NULL) {
        return 2;
    }

    int result = circular_buffer_create(*cb, N);
    if (result != 0) {
        free(*cb);
        *cb = NULL;
        return result;
    }

    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a) {
    if (a == NULL) {
        return;
    }

    free(a->ptr);

    free(a);
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a) {
    if (a == NULL || *a == NULL) {
        return;
    }

    circular_buffer_destroy(*a);

    *a = NULL;
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    if (cb == NULL) {
        return 1;
    }

    *(cb->ptr + (cb->end % cb->capacity)) = value;
    cb->end++;

    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code) {
    return 0;
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code) {
    return 0;
}

int circular_buffer_empty(const struct circular_buffer_t *a) {
    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *a) {
    if (a == NULL) {
        return -1;
    }

    if (a->end == a->capacity) {
        return 1;
    } else {
        return 0;
    }
}

void circular_buffer_display(const struct circular_buffer_t *a) {
    if (a == NULL) {
        return;
    }
    for (int i = 0; i < a->capacity; i++) {
        printf("%d ", *(a->ptr + i));
    }
    printf("\n");
}