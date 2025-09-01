//
// Created by Bartek on 07.06.2025.
//
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main() {

    float *var = malloc(sizeof(*var));
    if (var == NULL) {
        printf("Failed to allocate memory");
        exit(8);
    }

    *var = (float) M_PI;

    printf("%f %p", *var, (void *) var);

    free(var);
}