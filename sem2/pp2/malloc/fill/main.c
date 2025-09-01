//
// Created by Bartek on 07.06.2025.
//

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main() {

    int *ptr = malloc(SIZE * sizeof(*ptr));
    if (ptr == NULL) {
        printf("Failed to allocate memory");
        exit(8);
    }

    for (int i = 0; i < SIZE; ++i) {
        *(ptr + i) = i;
    }

    for (int i = 0; i < SIZE; ++i) {
        printf("%d ", *(ptr+i));
    }

    free(ptr);

    return 0;
}