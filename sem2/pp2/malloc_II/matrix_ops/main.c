#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_utils.h"

int main(void) {
    int width, height;
    printf("Podaj szerokość i wysokość: ");
    if (scanf("%d %d", &width, &height) != 2) {
        printf("incorrect input\n");
        return 1;
    }

    if (width < 1 || height < 1) {
        printf("incorrect input data\n");
        return 2;
    }

    struct matrix_t *matrix = matrix_create_struct(width, height);
    if (matrix == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj liczby: \n");
    if (matrix_read(matrix) != 0) {
        printf("incorrect input\n");
        matrix_destroy_struct(&matrix);
        return 1;
    }

    char *filename = (char*)malloc(40 * sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory\n");
        matrix_destroy_struct(&matrix);
        return 8;
    }

    printf("Podaj sciezke do pliku:\n");
    scanf("%39s", filename);

    struct matrix_t *transposed_matrix = matrix_transpose(matrix);
    if (transposed_matrix == NULL) {
        printf("Failed to allocate memory\n");
        free(filename);
        matrix_destroy_struct(&matrix);
        return 8;
    }

    int save_status = -1;
    if (strstr(filename, ".bin") == filename + strlen(filename) - 4) {
        save_status = matrix_save_b(transposed_matrix, filename);
    } else if (strstr(filename, ".txt") == filename + strlen(filename) - 4) {
        save_status = matrix_save_t(transposed_matrix, filename);
    } else {
        printf("Unsupported file format\n");
        free(filename);
        matrix_destroy_struct(&transposed_matrix);
        matrix_destroy_struct(&matrix);
        return 7;
    }

    if (save_status == 2) {
        printf("Couldn't create file\n");
        free(filename);
        matrix_destroy_struct(&transposed_matrix);
        matrix_destroy_struct(&matrix);
        return 5;
    } else if (save_status == 0) {
        printf("File saved\n");
    }

    free(filename);
    matrix_destroy_struct(&transposed_matrix);
    matrix_destroy_struct(&matrix);

    return 0;
}
