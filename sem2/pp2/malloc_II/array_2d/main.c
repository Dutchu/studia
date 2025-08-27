#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

int read_row(int *row_ptr, int width);

int **create_array_2d(int width, int height);

void display_array_2d(int **ptr, int width, int height);

void destroy_array_2d(int **ptr, int height);

void destroy(int **arr, int how_many);

int main(void) {
    int width = 0, height = 0;
    int **arr_2d;

    printf("Podaj szerokość i wysokość: ");
    if (scanf("%d %d", &width, &height) != 2) {
        printf("incorrect input\n");
        return 1;
    }

    if (height < 1 || width < 1) {
        printf("incorrect input data");
        return 2;
    }

    if ((arr_2d = create_array_2d(width, height)) == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj liczby: \n");
    // Wczytywanie danych od użytkownika
    for (int i = 0; i < height; ++i) {
        if (read_row(*(arr_2d + i), width) != 0) {
            printf("incorrect input\n");
            destroy_array_2d(arr_2d, height);
            return 1;
        }
    }


    display_array_2d(arr_2d, width, height);

    destroy_array_2d(arr_2d, height);
    return 0;
}

int **create_array_2d(int width, int height) {
    if (width < 1 || height < 1) return NULL;

    int **arr_2d = malloc(sizeof(int *) * height);
    if (arr_2d == NULL) {
        return NULL;
    }

    for (int row = 0; row < height; row++) {
        int *p_row = malloc(sizeof(int) * width);
        if (p_row == NULL) {
            for (int j = 0; j < row; ++j) {
                free(*(arr_2d + j));
            }
            free(arr_2d);
            return NULL;
        }
        *(arr_2d + row) = p_row;
    }

    return arr_2d;
}

void display_array_2d(int **ptr, int width, int height) {
    if (ptr == NULL) return;
    if (height < 1 || width < 1) return;

    int curr;
    for (int row = 0; row < height; row++) {
        if (*(ptr + row) == NULL) continue;

        for (int col = 0; col < width; col++) {
            curr = *(*(ptr + row) + col);
            if (curr < 10) {
                printf("  %d ", curr);
            } else if (curr == 100) {
                printf("%d", curr);
            } else {
                printf(" %d ", curr);
            }
        }
        printf("\n");
    }
}

void destroy_array_2d(int **ptr, int height) {
    if (ptr == NULL) return;
    if (height < 1) return;

    for (int i = 0; i < height; i++) {
        free(*(ptr + i));
        *(ptr + i) = NULL;
    }
    free(ptr);
}

int read_row(int *row_ptr, int width) {
    for (int i = 0; i < width; ++i) {
        if (scanf("%d", row_ptr + i) != 1) {
            return 1; // Błąd wczytywania
        }
    }
    return 0; // Sukces
}