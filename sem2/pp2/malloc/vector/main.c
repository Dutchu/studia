//
// Created by Bartek on 17.08.2025.
//

#include "vector.h"
#include <stdio.h>

#define SIZE 8
#define VALUE 42

int main() {
    struct vector_t* p_vector;

    printf("Hello world, from Vector!");

//    int vector_create_struct(struct vector_t **a, int N);
    vector_create_struct(&p_vector, SIZE);

//    void vector_destroy_struct(struct vector_t **a);
    vector_destroy_struct(&p_vector);

//    int vector_create(struct vector_t *a, int N);
    vector_create(p_vector, SIZE);

//    void vector_destroy(struct vector_t *a);
    vector_destroy(p_vector);

//    void vector_display(const struct vector_t *a);
    vector_display(p_vector);

//    int vector_push_back(struct vector_t *a, int value);
    vector_push_back(p_vector, VALUE);

//    int vector_erase(struct vector_t *a, int value);
    vector_erase(p_vector, VALUE);
}