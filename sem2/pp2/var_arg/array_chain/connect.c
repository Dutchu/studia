#include <stdlib.h>
#include <stdarg.h>
#include "data_type.h"
#ifdef INSIDE_DANTE
#include "tested_declarations.h"
#endif

void *connect(enum data_type_t type, int arrays_count, ...) {
    if (arrays_count < 2) return NULL;
    if (type < data_type_short || type > data_type_long) return NULL;

    va_list ap;
    size_t total = 0u;

    // First pass: compute total number of elements (without sentinels)
    va_start(ap, arrays_count);
    switch (type) {
        case data_type_short: {
            for (int i = 0; i < arrays_count; ++i) {
                short *arr = va_arg(ap, short *);
                if (arr == NULL) { va_end(ap); return NULL; }
                short *p = arr;
                while (*p != (short)-1) { ++total; ++p; }
            }
            break;
        }
        case data_type_int: {
            for (int i = 0; i < arrays_count; ++i) {
                int *arr = va_arg(ap, int *);
                if (arr == NULL) { va_end(ap); return NULL; }
                int *p = arr;
                while (*p != -1) { ++total; ++p; }
            }
            break;
        }
        case data_type_float: {
            for (int i = 0; i < arrays_count; ++i) {
                float *arr = va_arg(ap, float *);
                if (arr == NULL) { va_end(ap); return NULL; }
                float *p = arr;
                while (*p != -1.0f) { ++total; ++p; }
            }
            break;
        }
        case data_type_double: {
            for (int i = 0; i < arrays_count; ++i) {
                double *arr = va_arg(ap, double *);
                if (arr == NULL) { va_end(ap); return NULL; }
                double *p = arr;
                while (*p != -1.0) { ++total; ++p; }
            }
            break;
        }
        case data_type_long: {
            for (int i = 0; i < arrays_count; ++i) {
                long *arr = va_arg(ap, long *);
                if (arr == NULL) { va_end(ap); return NULL; }
                long *p = arr;
                while (*p != (long)-1) { ++total; ++p; }
            }
            break;
        }
        default: {
            va_end(ap);
            return NULL;
        }
    }
    va_end(ap);

    // Allocate output buffer (+1 for trailing sentinel)
    size_t out_elems = total + 1u;
    void *out = NULL;
    switch (type) {
        case data_type_short: out = malloc(out_elems * sizeof(short)); break;
        case data_type_int: out = malloc(out_elems * sizeof(int)); break;
        case data_type_float: out = malloc(out_elems * sizeof(float)); break;
        case data_type_double: out = malloc(out_elems * sizeof(double)); break;
        case data_type_long: out = malloc(out_elems * sizeof(long)); break;
        default: return NULL;
    }
    if (out == NULL) return NULL;

    // Second pass: copy elements
    va_start(ap, arrays_count);
    switch (type) {
        case data_type_short: {
            short *dst = (short *)out;
            for (int i = 0; i < arrays_count; ++i) {
                short *arr = va_arg(ap, short *);
                short *p = arr;
                while (*p != (short)-1) { *dst = *p; ++dst; ++p; }
            }
            *dst = (short)-1;
            break;
        }
        case data_type_int: {
            int *dst = (int *)out;
            for (int i = 0; i < arrays_count; ++i) {
                int *arr = va_arg(ap, int *);
                int *p = arr;
                while (*p != -1) { *dst = *p; ++dst; ++p; }
            }
            *dst = -1;
            break;
        }
        case data_type_float: {
            float *dst = (float *)out;
            for (int i = 0; i < arrays_count; ++i) {
                float *arr = va_arg(ap, float *);
                float *p = arr;
                while (*p != -1.0f) { *dst = *p; ++dst; ++p; }
            }
            *dst = -1.0f;
            break;
        }
        case data_type_double: {
            double *dst = (double *)out;
            for (int i = 0; i < arrays_count; ++i) {
                double *arr = va_arg(ap, double *);
                double *p = arr;
                while (*p != -1.0) { *dst = *p; ++dst; ++p; }
            }
            *dst = -1.0;
            break;
        }
        case data_type_long: {
            long *dst = (long *)out;
            for (int i = 0; i < arrays_count; ++i) {
                long *arr = va_arg(ap, long *);
                long *p = arr;
                while (*p != (long)-1) { *dst = *p; ++dst; ++p; }
            }
            *dst = (long)-1;
            break;
        }
        default: {
            va_end(ap);
            free(out);
            return NULL;
        }
    }
    va_end(ap);

    return out;
}
