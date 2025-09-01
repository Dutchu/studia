//
// Created by Bartek on 07.06.2025.
//

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "circular_buffer.h"

int circular_buffer_validate(const struct circular_buffer_t *cb);

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

    *cb = calloc(1,sizeof(struct circular_buffer_t));
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
    a->ptr = NULL;
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a) {
    if (a == NULL || *a == NULL) {
        return;
    }

    circular_buffer_destroy(*a);
    free(*a);
    *a = NULL;
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    if (circular_buffer_validate(cb) != 0) {
        return 1;
    }

    *(cb->ptr + cb->end) = value;

    if (cb->full) {
        cb->begin = (cb->begin + 1) % cb->capacity;
    }

    cb->end = (cb->end + 1) % cb->capacity;

    cb->full = (cb->begin == cb->end);

    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code) {
    if (circular_buffer_validate(a) != 0) {
        if (err_code) *err_code = 1;
        return -1;
    }

    if (circular_buffer_empty(a)) {
        if (err_code) *err_code = 2;
        return -1;
    }

    int result = *(a->ptr + a->begin);

    a->begin = (a->begin + 1) % a->capacity;

    a->full = 0;
    if (err_code) *err_code = 0;
    return result;
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code) {
    if (circular_buffer_validate(a) != 0) {
        if (err_code) *err_code = 1;
        return -1;
    }

    if (circular_buffer_empty(a)) {
        if (err_code) *err_code = 2;
        return -1;
    }

    a->end = (a->end - 1 + a->capacity) % a->capacity;

    int result = *(a->ptr + a->end);

    a->full = 0;
    if (err_code) *err_code = 0;

    return result;
}

int circular_buffer_empty(const struct circular_buffer_t *a) {
    if (circular_buffer_validate(a) != 0) {
        return -1;
    }

    return (!a->full && (a->end == a->begin));
}

int circular_buffer_full(const struct circular_buffer_t *a) {
    if (circular_buffer_validate(a) != 0) {
        return -1;
    }
    if (a->full) {
        return 1;
    } else {
        return 0;
    }
}

void circular_buffer_display(const struct circular_buffer_t *a) {
    if (circular_buffer_validate(a) != 0) {
        return;
    }
    if (circular_buffer_empty(a)) {
        return;
    }

    int current = a->begin;
    while (1) {

        if (current == a->end && !a->full) {
            break;
        }

        printf("%d ", *(a->ptr + current));
        current = (current + 1) % a->capacity;

        if (current == a->begin) {
            break;
        }
    }

    printf("\n");
}

int circular_buffer_validate(const struct circular_buffer_t *cb) {
    if (cb == NULL) {
        return 1;
    }

    if (cb->ptr == NULL) {
        return 1;
    }

    if (cb->capacity <= 0) {
        return 1;
    }

    if (cb->begin < 0 || cb->begin >= cb->capacity) {
        return 1;
    }

    if (cb->end < 0 || cb->end >= cb->capacity) {
        return 1;
    }

    return 0;
}