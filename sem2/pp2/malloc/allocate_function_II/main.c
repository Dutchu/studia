//
// Created by Bartek on 22.08.2025.
//

#include <stdio.h>
#include <stdlib.h>

int create_array_int(int **ptr, int N) {
    if (ptr == NULL || N <= 0) {
        return 1;
    }

    *ptr = (int *)malloc(N * sizeof(int));
    if (*ptr == NULL) {
        return 2;
    }

    return 0;
}

void destroy_array_int(int **ptr) {
    if (ptr != NULL && *ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}

int main() {
    int *array = NULL;
    int size;

    printf("Podaj rozmiar tablicy: ");
    if (scanf("%d", &size) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    if (size <= 0) {
        printf("Incorrect input data\n");
        return 2;
    }

    int create_result = create_array_int(&array, size);
    if (create_result != 0) {
        if (create_result == 1) {
            printf("Incorrect input data\n");
            return 2;
        }
        if (create_result == 2) {
            printf("Failed to allocate memory\n");
            return 8;
        }
    }

    printf("Podaj liczby: ");
    for (int i = 0; i < size; ++i) {
        if (scanf("%d", array + i) != 1) {
            printf("Incorrect input\n");
            destroy_array_int(&array);
            return 1;
        }
    }

    for (int i = size - 1; i >= 0; --i) {
        printf("%d", *(array + i));
        if (i > 0) {
            printf(" ");
        }
    }
    printf("\n");

    destroy_array_int(&array);

    return 0;
}