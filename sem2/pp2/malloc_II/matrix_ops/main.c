#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_utils.h"


struct matrix_t* load_matrix_from_file(const char* prompt) {
    char *filename = (char*)malloc(20 * sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory\n");
        exit(8);
    }

    printf("%s", prompt);
    scanf("%19s", filename);

    struct matrix_t* matrix = NULL;
    int err_code = 0;

    if (strstr(filename, ".bin") == filename + strlen(filename) - 4) {
        matrix = matrix_load_b(filename, &err_code);
    } else if (strstr(filename, ".txt") == filename + strlen(filename) - 4) {
        matrix = matrix_load_t(filename, &err_code);
    } else {
        printf("Unsupported file format\n");
        free(filename);
        exit(7);
    }

    free(filename); 

    if (matrix == NULL) {
        switch (err_code) {
            case 2:
                printf("Couldn't open file\n");
                exit(4);
            case 3:
                printf("File corrupted\n");
                exit(6);
            case 4:
                printf("Failed to allocate memory\n");
                exit(8);
            default:
                printf("An unknown error occurred\n");
                exit(1);
        }
    }
    return matrix;
}

int main(void) {
    struct matrix_t *m1 = load_matrix_from_file("Podaj nazwę pierwszego pliku: ");
    struct matrix_t *m2 = load_matrix_from_file("Podaj nazwę drugiego pliku: ");

    struct matrix_t *add_res = matrix_add(m1, m2);
    matrix_display(add_res);
    matrix_destroy_struct(&add_res);

    struct matrix_t *sub_res = matrix_subtract(m1, m2);
    matrix_display(sub_res);
    matrix_destroy_struct(&sub_res);

    struct matrix_t *mul_res = matrix_multiply(m1, m2);
    matrix_display(mul_res);
    matrix_destroy_struct(&mul_res);

    matrix_destroy_struct(&m1);
    matrix_destroy_struct(&m2);

    return 0;
}
