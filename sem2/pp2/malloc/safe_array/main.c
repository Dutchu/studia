//
// Created by Bartek on 21.08.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int main() {
    struct array_t *array;
    array = malloc(10 * sizeof(int));

    array->capacity = 10;
    array->size = 5;
    int arr[] = {1, 2, 3, 4, 5};
    array->ptr = arr;

    printf("Hello from Safe Array:\n");

    for (int i = 0; i < array->size; ++i) {
        printf("%d ", *(array->ptr + i));
    }

    array_create(array, 10);

    array_push_back(array, 1);

    array_display(array);

    array_destroy(array);

    free(array);

    exit(0);
}