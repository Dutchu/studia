// Solution for array_chain
// - Reads a data type (0..4) and number of arrays (2..4)
// - Reads each array (exact size), appends sentinel -1, and concatenates using a variadic function
// - No use of [] operator anywhere

#include <stdio.h>
#include <stdlib.h>
#include "data_type.h"
#include "connect.h"
#ifdef INSIDE_DANTE
#include "tested_declarations.h"
#endif

static size_t type_sizeof(data_type_t t) {
    switch (t) {
        case data_type_short: return sizeof(short);
        case data_type_int: return sizeof(int);
        case data_type_float: return sizeof(float);
        case data_type_double: return sizeof(double);
        case data_type_long: return sizeof(long);
        default: return 0u;
    }
}

int main(void) {
    printf("Podaj typ danych do wprowadzenia: ");
    fflush(stdout);

    int type_num = -1;
    if (scanf("%d", &type_num) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    if (type_num < 0 || type_num > 4) {
        printf("Incorrect input data\n");
        return 2;
    }

    data_type_t type = (data_type_t)type_num;

    printf("Podaj liczbe tablic do wprowadzenia: ");
    fflush(stdout);

    int arrays_count = 0;
    if (scanf("%d", &arrays_count) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    if (arrays_count < 2 || arrays_count > 4) {
        printf("Incorrect input data\n");
        return 2;
    }

    void **arrays = (void **)malloc((size_t)arrays_count * sizeof(void *));
    if (arrays == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    size_t total_elems = 0u;

    for (int i = 0; i < arrays_count; ++i) {
        printf("Podaj liczbe elementow: ");
        fflush(stdout);

        int count = 0;
        if (scanf("%d", &count) != 1) {
            // cleanup allocated arrays so far
            for (int k = 0; k < i; ++k) {
                void *ptr = *(arrays + k);
                free(ptr);
            }
            free(arrays);
            printf("Incorrect input\n");
            return 1;
        }

        if (count < 1) {
            for (int k = 0; k < i; ++k) {
                void *ptr = *(arrays + k);
                free(ptr);
            }
            free(arrays);
            printf("Incorrect input data\n");
            return 2;
        }

        size_t tsize = type_sizeof(type);
        if (tsize == 0u) {
            for (int k = 0; k < i; ++k) {
                void *ptr = *(arrays + k);
                free(ptr);
            }
            free(arrays);
            printf("Incorrect input data\n");
            return 2;
        }

        // allocate count + 1 to store sentinel -1
        void *arr = malloc(((size_t)count + 1u) * tsize);
        if (arr == NULL) {
            for (int k = 0; k < i; ++k) {
                void *ptr = *(arrays + k);
                free(ptr);
            }
            free(arrays);
            printf("Failed to allocate memory\n");
            return 8;
        }

        printf("Podaj liczby: ");
        fflush(stdout);

        // Read elements according to type and store sentinel at the end
        int ok = 1;
        switch (type) {
            case data_type_short: {
                short *base = (short *)arr;
                short *p = base;
                size_t eff = (size_t)count;
                for (int j = 0; j < count; ++j) {
                    if (scanf("%hd", p) != 1) { ok = 0; break; }
                    if (eff == (size_t)count && *p == (short)-1) {
                        eff = (size_t)j;
                    }
                    ++p;
                }
                if (ok) { *(base + eff) = (short)-1; total_elems += eff; }
                break;
            }
            case data_type_int: {
                int *base = (int *)arr;
                int *p = base;
                size_t eff = (size_t)count;
                for (int j = 0; j < count; ++j) {
                    if (scanf("%d", p) != 1) { ok = 0; break; }
                    if (eff == (size_t)count && *p == -1) {
                        eff = (size_t)j;
                    }
                    ++p;
                }
                if (ok) { *(base + eff) = -1; total_elems += eff; }
                break;
            }
            case data_type_float: {
                float *base = (float *)arr;
                float *p = base;
                size_t eff = (size_t)count;
                for (int j = 0; j < count; ++j) {
                    if (scanf("%f", p) != 1) { ok = 0; break; }
                    if (eff == (size_t)count && *p == -1.0f) {
                        eff = (size_t)j;
                    }
                    ++p;
                }
                if (ok) { *(base + eff) = -1.0f; total_elems += eff; }
                break;
            }
            case data_type_double: {
                double *base = (double *)arr;
                double *p = base;
                size_t eff = (size_t)count;
                for (int j = 0; j < count; ++j) {
                    if (scanf("%lf", p) != 1) { ok = 0; break; }
                    if (eff == (size_t)count && *p == -1.0) {
                        eff = (size_t)j;
                    }
                    ++p;
                }
                if (ok) { *(base + eff) = -1.0; total_elems += eff; }
                break;
            }
            case data_type_long: {
                long *base = (long *)arr;
                long *p = base;
                size_t eff = (size_t)count;
                for (int j = 0; j < count; ++j) {
                    if (scanf("%ld", p) != 1) { ok = 0; break; }
                    if (eff == (size_t)count && *p == (long)-1) {
                        eff = (size_t)j;
                    }
                    ++p;
                }
                if (ok) { *(base + eff) = (long)-1; total_elems += eff; }
                break;
            }
            default:
                ok = 0;
                break;
        }

        if (!ok) {
            for (int k = 0; k < i; ++k) {
                void *ptr = *(arrays + k);
                free(ptr);
            }
            free(arr);
            free(arrays);
            printf("Incorrect input\n");
            return 1;
        }

        *(arrays + i) = arr;
    }

    // Dispatch to variadic connector (2..4 arrays)
    void *result = NULL;
    void *a0 = *(arrays + 0);
    void *a1 = *(arrays + 1);
    void *a2 = (arrays_count >= 3) ? *(arrays + 2) : NULL;
    void *a3 = (arrays_count >= 4) ? *(arrays + 3) : NULL;

    switch (type) {
        case data_type_short:
            if (arrays_count == 2) result = connect(type, 2, (short *)a0, (short *)a1);
            else if (arrays_count == 3) result = connect(type, 3, (short *)a0, (short *)a1, (short *)a2);
            else result = connect(type, 4, (short *)a0, (short *)a1, (short *)a2, (short *)a3);
            break;
        case data_type_int:
            if (arrays_count == 2) result = connect(type, 2, (int *)a0, (int *)a1);
            else if (arrays_count == 3) result = connect(type, 3, (int *)a0, (int *)a1, (int *)a2);
            else result = connect(type, 4, (int *)a0, (int *)a1, (int *)a2, (int *)a3);
            break;
        case data_type_float:
            if (arrays_count == 2) result = connect(type, 2, (float *)a0, (float *)a1);
            else if (arrays_count == 3) result = connect(type, 3, (float *)a0, (float *)a1, (float *)a2);
            else result = connect(type, 4, (float *)a0, (float *)a1, (float *)a2, (float *)a3);
            break;
        case data_type_double:
            if (arrays_count == 2) result = connect(type, 2, (double *)a0, (double *)a1);
            else if (arrays_count == 3) result = connect(type, 3, (double *)a0, (double *)a1, (double *)a2);
            else result = connect(type, 4, (double *)a0, (double *)a1, (double *)a2, (double *)a3);
            break;
        case data_type_long:
            if (arrays_count == 2) result = connect(type, 2, (long *)a0, (long *)a1);
            else if (arrays_count == 3) result = connect(type, 3, (long *)a0, (long *)a1, (long *)a2);
            else result = connect(type, 4, (long *)a0, (long *)a1, (long *)a2, (long *)a3);
            break;
        default:
            result = NULL;
            break;
    }

    if (result == NULL) {
        for (int k = 0; k < arrays_count; ++k) {
            void *ptr = *(arrays + k);
            free(ptr);
        }
        free(arrays);
        printf("Failed to allocate memory\n");
        return 8;
    }

    // Print result
    size_t printed = 0u;
    switch (type) {
        case data_type_short: {
            short *p = (short *)result;
            while (printed < total_elems) {
                if (printed) printf(" ");
                printf("%hd", *p);
                ++p; ++printed;
            }
            break;
        }
        case data_type_int: {
            int *p = (int *)result;
            while (printed < total_elems) {
                if (printed) printf(" ");
                printf("%d", *p);
                ++p; ++printed;
            }
            break;
        }
        case data_type_float: {
            float *p = (float *)result;
            while (printed < total_elems) {
                if (printed) printf(" ");
                printf("%f", *p);
                ++p; ++printed;
            }
            break;
        }
        case data_type_double: {
            double *p = (double *)result;
            while (printed < total_elems) {
                if (printed) printf(" ");
                printf("%f", *p);
                ++p; ++printed;
            }
            break;
        }
        case data_type_long: {
            long *p = (long *)result;
            while (printed < total_elems) {
                if (printed) printf(" ");
                printf("%ld", *p);
                ++p; ++printed;
            }
            break;
        }
        default:
            break;
    }
    printf("\n");

    // Cleanup
    for (int k = 0; k < arrays_count; ++k) {
        void *ptr = *(arrays + k);
        free(ptr);
    }
    free(arrays);
    free(result);

    return 0;
}
