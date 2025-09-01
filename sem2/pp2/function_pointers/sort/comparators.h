// Declarations for generic sort and comparators

#ifndef SORT_COMPARATORS_H
#define SORT_COMPARATORS_H

#include <stddef.h>

struct point_t {
    double x;
    double y;
};

int comp_int(const void *ptr1, const void *ptr2);
int comp_double(const void *ptr1, const void *ptr2);
int comp_point(const void *ptr1, const void *ptr2);

int sort(void *base, int count, size_t elem_size,
         int (*comparator)(const void *, const void *));

#endif // SORT_COMPARATORS_H

