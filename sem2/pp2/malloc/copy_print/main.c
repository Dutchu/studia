//
// Created by Bartek on 22.08.2025.
//

#include <stdio.h>
#include <stdlib.h>

int* create_array_int(int N) {
    if (N <= 0) {
        return NULL;
    }
    return (int *)malloc(N * sizeof(int));
}

int* copy_array_int(const int* ptr, int N) {
    if (ptr == NULL || N <= 0) {
        return NULL;
    }

    int* copy = create_array_int(N);
    if (copy == NULL) {
        return NULL;
    }

    
    for (int i = 0; i < N; ++i) {
        *(copy + i) = *(ptr + i);
    }

    return copy;
}
4+4+1
void display_array_int(const int* ptr, int N) {
    if (ptr == NULL || N <= 0) {
        return;
    }

    for (int i = 0; i < N; ++i) {
        printf("%d", *(ptr + i));
        if (i < N - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int *original_array = NULL;
    int *copied_array = NULL;
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

    
    original_array = create_array_int(size);
    if (original_array == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    
    printf("Podaj liczby: ");
    for (int i = 0; i < size; ++i) {
        if (scanf("%d", original_array + i) != 1) {
            printf("Incorrect input\n");
            free(original_array); 
            return 1;
        }
    }

    
    copied_array = copy_array_int(original_array, size);
    if (copied_array == NULL) {
        printf("Failed to allocate memory\n");
        free(original_array); 
        return 8;
    }

    
    display_array_int(original_array, size);
    display_array_int(copied_array, size);

    
    free(original_array);
    free(copied_array);

    return 0;
}