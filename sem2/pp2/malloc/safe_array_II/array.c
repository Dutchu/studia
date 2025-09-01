//
// Created by Bartek on 21.08.2025.
//

#include <stddef.h>
#include <malloc.h>
#include "array.h"
#include "tested_declarations.h"
#include "rdebug.h"

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
    if (a == NULL || a->ptr == NULL || a->size < 1 || a->capacity < 1 || a->size > a->capacity) return;
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

/**
 * @brief Performs a deep copy of one array structure into another.
 *
 * This function creates a new, independent copy of the source array.
 * It allocates separate memory for the data, ensuring that modifications
 * to the destination array do not affect the source array.
 *
 * @param src A constant pointer to the source array_t structure.
 * @param dest A pointer to the destination array_t structure.
 * @return 0 on success.
 * @return 1 for invalid input (e.g., NULL pointers, corrupted source data, or src == dest).
 * @return 2 if memory allocation for the destination array fails.
 */
int array_copy(const struct array_t *src, struct array_t *dest) {
    if (src == NULL || dest == NULL || src == dest || src->ptr == NULL || src->size < 0 || src->capacity <= 0 || src->size > src->capacity) {
        return 1;
    }

    if (array_create(dest, src->capacity) != 0) {
        return 2;
    }

    for (int i = 0; i < src->size; ++i) {
        *(dest->ptr + i) = *(src->ptr + i);
    }

    dest->size = src->size;
    return 0;
}

/**
 * @brief Separates an array's elements into two new arrays: one for odd
 * numbers and one for even numbers.
 *
 * The capacity of the new odd and even arrays is set to be exactly the
 * number of elements they contain (size == capacity). On allocation failure,
 * it ensures no memory is leaked.
 *
 * @param a A constant pointer to the source array to be separated.
 * @param odd A pointer to the array_t structure for odd numbers.
 * @param even A pointer to the array_t structure for even numbers.
 * @return A bitmask on success: 1 if odd was filled, 2 if even was filled, 3 if both.
 * @return -1 for invalid input (e.g., NULL pointers, empty source array, or aliased pointers).
 * @return 0 if memory allocation fails for either of the new arrays.
 */


/**
 * @brief Test memory availability before allocating arrays
 */
int can_allocate_memory(size_t size1, size_t size2) {
    void *test1 = malloc(size1);
    if (test1 == NULL) return 0;

    void *test2 = malloc(size2);
    if (test2 == NULL) {
        free(test1);
        return 0;
    }

    free(test1);
    free(test2);
    return 1;
}

/**
 * @brief Separates an array's elements into two new arrays: one for odd
 * numbers and one for even numbers.
 */
int array_separate(const struct array_t *a, struct array_t *odd, struct array_t *even) {
    if (a == NULL || odd == NULL || even == NULL || odd == even || a == odd || a == even ||
        a->ptr == NULL || a->size <= 0 || a->capacity <= 0 || a->size > a->capacity) {
        return -1;
    }

    int odd_count = 0;
    int even_count = 0;
    for (int i = 0; i < a->size; ++i) {
        if (*(a->ptr + i) % 2 == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }

    if (odd_count == 0 && even_count > 0) {
        if (array_create(even, even_count) != 0) return 0;
        int even_idx = 0;
        for (int i = 0; i < a->size; ++i) {
            int value = *(a->ptr + i);
            if (value % 2 == 0) {
                *(even->ptr + even_idx++) = value;
            }
        }
        even->size = even_count;
        odd->ptr = NULL; odd->size = 0; odd->capacity = 0;
        return 2;
    }

    if (even_count == 0 && odd_count > 0) {
        if (array_create(odd, odd_count) != 0) return 0;
        int odd_idx = 0;
        for (int i = 0; i < a->size; ++i) {
            int value = *(a->ptr + i);
            if (value % 2 != 0) {
                *(odd->ptr + odd_idx++) = value;
            }
        }
        odd->size = odd_count;
        even->ptr = NULL; even->size = 0; even->capacity = 0;
        return 1;
    }

    // Check if we can allocate both arrays before actually doing it
    size_t odd_bytes = odd_count * sizeof(int);
    size_t even_bytes = even_count * sizeof(int);

    if (!can_allocate_memory(odd_bytes, even_bytes)) {
        return 0;  // Memory allocation would fail
    }

    if (array_create(odd, odd_count) != 0) {
        return 0;
    }

    if (array_create(even, even_count) != 0) {
        array_destroy(odd);
        return 0;
    }

    int odd_idx = 0;
    int even_idx = 0;
    for (int i = 0; i < a->size; ++i) {
        int value = *(a->ptr + i);
        if (value % 2 == 0) {
            *(even->ptr + even_idx) = value;
            even_idx++;
        } else {
            *(odd->ptr + odd_idx) = value;
            odd_idx++;
        }
    }

    odd->size = odd_count;
    even->size = even_count;

    return 3;
}

int is_valid(struct array_t *a) {
    if (a == NULL) return 0;
    if (a->size < 0 || a->capacity < 1) return 0;
    if (a->size > a->capacity) return 0;
    if (a->capacity >= 1 && a->ptr == NULL) return 0;

    return 1;
}

