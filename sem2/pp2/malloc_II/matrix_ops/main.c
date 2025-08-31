#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "matrix_utils.h"


int load_matrix_from_file(const char* prompt, struct matrix_t **out_m) {
    if (out_m == NULL) return 1;
    *out_m = NULL;

    char *filename = (char*)malloc((size_t)20 * sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory\n");
        fflush(stdout);
        return 8;
    }

    // Prompt only after successful allocation to avoid prompting when we cannot proceed
    printf("%s", prompt);
    fflush(stdout);
    if (scanf("%19s", filename) != 1) {
        free(filename);
        return 1;
    }
    int truncated = 0;
    size_t len = strlen(filename);
    if (len == 19) {
        int c = getchar();
        if (c != EOF && !isspace(c)) {
            truncated = 1;
            // consume the rest of the token to reach next whitespace
            while (c != EOF && !isspace(c)) {
                c = getchar();
            }
        }
    }

    int loader_err = 0;
    struct matrix_t *m = NULL;
    char *ext = strrchr(filename, '.');
    if (!truncated && ext != NULL && strcmp(ext, ".bin") == 0) {
        m = matrix_load_b(filename, &loader_err);
    } else if (!truncated && ext != NULL && strcmp(ext, ".txt") == 0) {
        m = matrix_load_t(filename, &loader_err);
    } else {
        printf("Unsupported file format\n");
        free(filename);
        fflush(stdout);
        return 7;
    }

    free(filename);

    if (m == NULL) {
        switch (loader_err) {
            case 2:
                printf("Couldn't open file\n");
                fflush(stdout);
                return 4;
            case 3:
                printf("File corrupted\n");
                fflush(stdout);
                return 6;
            case 4:
                printf("Failed to allocate memory\n");
                fflush(stdout);
                return 8;
            default:
                return 1;
        }
    }

    *out_m = m;
    return 0;
}

int main(int argc, char **argv) {
    setvbuf(stdout, NULL, _IONBF, 0);
    struct matrix_t *m1 = NULL;
    int code = load_matrix_from_file("Podaj nazwę pierwszego pliku: ", &m1);
    if (code != 0) {
        return code;
    }

    struct matrix_t *m2 = NULL;
    code = load_matrix_from_file("Podaj nazwę drugiego pliku: ", &m2);
    if (code != 0) {
        matrix_destroy_struct(&m1);
        return code;
    }

    if (argc > 1) {
        // Compatibility mode: allocate result matrices and print results
        struct matrix_t *res = NULL;

        res = matrix_add(m1, m2);
        if (res == NULL) {
            printf("Error\n");
        } else {
            matrix_display(res);
            matrix_destroy_struct(&res);
        }

        res = matrix_subtract(m1, m2);
        if (res == NULL) {
            printf("Error\n");
        } else {
            matrix_display(res);
            matrix_destroy_struct(&res);
        }

        res = matrix_multiply(m1, m2);
        if (res == NULL) {
            printf("Error\n");
        } else {
            matrix_display(res);
            matrix_destroy_struct(&res);
        }
    } else {
        // Stream results directly without allocating temporary result matrices
        matrix_display_add(m1, m2);
        matrix_display_subtract(m1, m2);
        matrix_display_multiply(m1, m2);
    }

    matrix_destroy_struct(&m1);
    matrix_destroy_struct(&m2);

    return 0;
}
