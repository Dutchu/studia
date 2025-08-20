//
// Created by Bartek on 17.08.2025.
//

#include "vector.h"
#include <stdio.h>

#define SIZE 8
#define VALUE 42

int main() {
    struct vector_t *p_vector = NULL;

    printf("Hello world, from Vector!\n");

    vector_create_struct(&p_vector, SIZE);

    vector_push_back(p_vector, VALUE);

    vector_display(p_vector);

    vector_destroy_struct(&p_vector);

    return 0;
}