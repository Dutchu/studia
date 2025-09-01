//
// Created by Bartek on 22.08.2025.
//

#include <stdio.h>
#include <stdlib.h>

float* create_array(int N) {
    if (N <= 0) {
        return NULL;
    }
    float* array = (float*)malloc(N * sizeof(float));
    return array;
}

int main() {
    int N;
    printf("Podaj rozmiar tablicy: ");
    if (scanf("%d", &N) != 1) {
        printf( "Incorrect input\n");
        return 1;
    }

    if (N <= 0) {
        printf( "Incorrect input data\n");
        return 2;
    }

    float* array = create_array(N);
    if (array == NULL) {
        printf( "Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj liczby: ");
    for (int i = 0; i < N; ++i) {
        if (scanf("%f", array + i) != 1) {
            printf( "Incorrect input\n");
            free(array);
            return 1;
        }
    }

    for (int i = N - 1; i >= 0; --i) {
        printf("%.4f ", *(array + i));
    }
    printf("\n");

    free(array);
    return 0;
}