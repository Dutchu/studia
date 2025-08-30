// Solution for word_chain
// Requirements:
// - Provide function `concatenate(int count, ...)` that joins texts with spaces
// - Read number of texts (2..4), then read that many lines (<=1000 chars each)
// - Allocate a dynamic 2D array for up to 4 texts of length 1000
// - Handle errors and avoid using the [] operator anywhere in the code

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

static void discard_line(void) {
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}

static int read_line_into(char *dst, size_t cap) {
    if (dst == NULL || cap == 0) return 0;
    if (fgets(dst, (int)cap, stdin) == NULL) return 0;

    char *nl = strchr(dst, '\n');
    if (nl != NULL) {
        *nl = '\0';
    } else {
        discard_line();
    }
    return 1;
}

char *concatenate(int count, ...) {
    if (count <= 0) return NULL;

    va_list ap;
    size_t total_len = 0;

    va_start(ap, count);
    for (int i = 0; i < count; ++i) {
        const char *s = va_arg(ap, const char *);
        if (s == NULL) {
            va_end(ap);
            return NULL;
        }
        total_len += strlen(s);
    }
    va_end(ap);

    size_t spaces = (count > 1) ? (size_t)(count - 1) : 0u;
    size_t need = total_len + spaces + 1u; // +1 for null terminator

    char *out = (char *)malloc(need);
    if (out == NULL) return NULL;

    char *p = out;

    va_start(ap, count);
    for (int i = 0; i < count; ++i) {
        const char *s = va_arg(ap, const char *);
        const char *q = s;
        while (*q != '\0') {
            *p = *q;
            ++p;
            ++q;
        }
        if (i + 1 < count) {
            *p = ' ';
            ++p;
        }
    }
    va_end(ap);

    *p = '\0';
    return out;
}

int main(void) {
    // Prepare dynamic 2D array for up to 4 texts, each up to 1000 chars (+1 for null)
    // Allocate as early as possible to immediately detect OOM conditions.
    char **rows = (char **)malloc(4u * sizeof(char *));
    if (rows == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    for (int i = 0; i < 4; ++i) {
        char *buf = (char *)malloc(1001u);
        if (buf == NULL) {
            // free previously allocated buffers
            for (int j = 0; j < i; ++j) {
                char *tmp = *(rows + j);
                free(tmp);
            }
            free(rows);
            printf("Failed to allocate memory\n");
            return 8;
        }
        *(rows + i) = buf;
    }

    printf("Podaj liczbe tekstow do wprowadzenia: ");
    fflush(stdout);

    int n = 0;
    if (scanf("%d", &n) != 1) {
        // cleanup before exit
        for (int j = 0; j < 4; ++j) {
            char *tmp = *(rows + j);
            free(tmp);
        }
        free(rows);
        printf("Incorrect input\n");
        return 1;
    }
    discard_line();

    if (n < 2 || n > 4) {
        for (int j = 0; j < 4; ++j) {
            char *tmp = *(rows + j);
            free(tmp);
        }
        free(rows);
        printf("Incorrect input data\n");
        return 2;
    }

    printf("Podaj teksty: \n");
    fflush(stdout);

    for (int i = 0; i < n; ++i) {
        char *slot = *(rows + i);
        if (!read_line_into(slot, 1001u)) {
            // cleanup
            for (int j = 0; j < 4; ++j) {
                char *tmp = *(rows + j);
                free(tmp);
            }
            free(rows);
            printf("Incorrect input\n");
            return 1;
        }
    }

    char *result = NULL;
    if (n == 2) {
        result = concatenate(2, *(rows + 0), *(rows + 1));
    } else if (n == 3) {
        result = concatenate(3, *(rows + 0), *(rows + 1), *(rows + 2));
    } else { // n == 4
        result = concatenate(4, *(rows + 0), *(rows + 1), *(rows + 2), *(rows + 3));
    }

    if (result == NULL) {
        for (int j = 0; j < 4; ++j) {
            char *tmp = *(rows + j);
            free(tmp);
        }
        free(rows);
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("%s\n", result);

    free(result);
    for (int j = 0; j < 4; ++j) {
        char *tmp = *(rows + j);
        free(tmp);
    }
    free(rows);
    return 0;
}
