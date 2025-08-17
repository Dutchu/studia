//
// Created by Bartek on 17.08.2025.
//

#include <stdio.h>
#include "vector.h"

int vector_create_struct(struct vector_t **a, int N) {
    printf("Creating vector with address %p, size: %d\n", *a, N);
    return 0;
}

void vector_destroy_struct(struct vector_t **a) {
    printf("Destroying vector with address %p\n", *a);
}

int vector_create(struct vector_t *a, int N) {
    printf("Creating vector buffer with address %p, size: %d\n", a, N);
    return 0;
}

void vector_destroy(struct vector_t *a) {
    printf("Destroying vector buffer with address %p\n", a);
}

void vector_display(const struct vector_t *a) {
    printf("Displaying vector buffer with address %p\n", a);
}

int vector_push_back(struct vector_t *a, int value) {
    printf("Pushing item [%d], to a vector buffer with address %p\n", value, a);
    return 0;
}

int vector_erase(struct vector_t *a, int value) {
    printf("Erasing item [%d], of vector with address %p\n", value, a);
    return 0;
}