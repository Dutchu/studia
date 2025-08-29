/* Generic sort runner with interactive IO */

#include <stdio.h>
#include <stdlib.h>
#include "comparators.h"

int main(void) {
    int type_value = 0;
    printf("Enter data type: ");
    if (scanf("%d", &type_value) != 1) {
        printf("Incorrect input\n");
        return 1;
    }
    if (!(type_value == 0 || type_value == 1 || type_value == 2)) {
        printf("Incorrect input\n");
        return 1;
    }

    int n = 0;
    printf("Enter array size: ");
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input\n");
        return 1;
    }
    if (n <= 0) {
        printf("Incorrect input data\n");
        return 2;
    }

    if (type_value == 0) {
        /* int */
        int *arr = (int *)malloc((size_t)n * sizeof(int));
        if (!arr) {
            printf("Failed to allocate memory\n");
            return 8;
        }
        printf("Enter ints: ");
        int i = 0;
        while (i < n) {
            if (scanf("%d", arr + i) != 1) {
                printf("Incorrect input\n");
                free(arr);
                return 1;
            }
            i++;
        }
        if (sort(arr, n, sizeof(int), comp_int) != 0) {
            free(arr);
            return 1;
        }
        i = 0;
        while (i < n) {
            printf("%d ", *(arr + i));
            i++;
        }
        printf("\n");
        free(arr);
    } else if (type_value == 1) {
        /* double */
        double *arr = (double *)malloc((size_t)n * sizeof(double));
        if (!arr) {
            printf("Failed to allocate memory\n");
            return 8;
        }
        printf("Enter doubles: ");
        int i = 0;
        while (i < n) {
            if (scanf("%lf", arr + i) != 1) {
                printf("Incorrect input\n");
                free(arr);
                return 1;
            }
            i++;
        }
        if (sort(arr, n, sizeof(double), comp_double) != 0) {
            free(arr);
            return 1;
        }
        i = 0;
        while (i < n) {
            printf("%.6lf ", *(arr + i));
            i++;
        }
        printf("\n");
        free(arr);
    } else {
        /* point_t */
        struct point_t *arr = (struct point_t *)malloc((size_t)n * sizeof(struct point_t));
        if (!arr) {
            printf("Failed to allocate memory\n");
            return 8;
        }
        printf("Enter points: ");
        int i = 0;
        while (i < n) {
            struct point_t *p = arr + i;
            if (scanf("%lf %lf", &(p->x), &(p->y)) != 2) {
                printf("Incorrect input\n");
                free(arr);
                return 1;
            }
            i++;
        }
        if (sort(arr, n, sizeof(struct point_t), comp_point) != 0) {
            free(arr);
            return 1;
        }
        i = 0;
        while (i < n) {
            struct point_t *p = arr + i;
            printf("%.6lf %.6lf\n", p->x, p->y);
            i++;
        }
        free(arr);
    }

    return 0;
}
