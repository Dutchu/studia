#include <stddef.h>
#include "comparators.h"

static void byte_swap(unsigned char *a, unsigned char *b, size_t size) {
    size_t i = 0;
    while (i < size) {
        unsigned char tmp = *(a + i);
        *(a + i) = *(b + i);
        *(b + i) = tmp;
        i++;
    }
}

int sort(void *base, int count, size_t elem_size,
         int (*comparator)(const void *, const void *)) {
    if (!base || count < 0 || elem_size == 0 || !comparator) {
        return 1;
    }
    if (count <= 1) {
        return 0;
    }

    unsigned char *arr = (unsigned char *)base;

    int i = 0;
    while (i < count - 1) {
        int j = 0;
        while (j < count - 1 - i) {
            unsigned char *left = arr + (size_t)j * elem_size;
            unsigned char *right = arr + (size_t)(j + 1) * elem_size;
            if (comparator((const void *)left, (const void *)right) > 0) {
                byte_swap(left, right, elem_size);
            }
            j++;
        }
        i++;
    }

    return 0;
}

int comp_int(const void *ptr1, const void *ptr2) {
    if (!ptr1 || !ptr2) {
        return 0;
    }
    const int *a = (const int *)ptr1;
    const int *b = (const int *)ptr2;
    if (*a > *b) return 1;
    if (*a < *b) return -1;
    return 0;
}

int comp_double(const void *ptr1, const void *ptr2) {
    if (!ptr1 || !ptr2) {
        return 0;
    }
    const double *a = (const double *)ptr1;
    const double *b = (const double *)ptr2;
    if (*a > *b) return 1;
    if (*a < *b) return -1;
    return 0;
}

int comp_point(const void *ptr1, const void *ptr2) {
    if (!ptr1 || !ptr2) {
        return 0;
    }
    const struct point_t *p1 = (const struct point_t *)ptr1;
    const struct point_t *p2 = (const struct point_t *)ptr2;
    if (p1->x > p2->x) return 1;
    if (p1->x < p2->x) return -1;
    if (p1->y > p2->y) return 1;
    if (p1->y < p2->y) return -1;
    return 0;
}

