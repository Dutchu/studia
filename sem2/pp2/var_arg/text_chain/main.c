// Solution for text_chain
// - Implement concatenate() variadic function to join N strings with spaces
// - Program reads count (2..4), then N lines (each up to 1000 chars)
// - Uses dynamically allocated 2D array for inputs and 1D array for result
// - No use of [] anywhere; no fflush(stdout)

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "concatenate.h"

static void drain_line(void) {
    int ch = getchar();
    while (ch != '\n' && ch != EOF) ch = getchar();
}

int main(void) {
    const int max_texts = 4;
    const int max_len = 1000;          // without NUL
    const int slot = max_len + 1;      // with NUL
    const size_t res_cap = (size_t)max_texts * (size_t)max_len + (size_t)(max_texts - 1) + 1u;

    // Allocate buffers up front (before prompts for these inputs)
    char **texts = (char **)malloc((size_t)max_texts * sizeof(char *));
    if (!texts) {
        printf("Failed to allocate memory\n");
        return 8;
    }
    int idx = 0;
    for (idx = 0; idx < max_texts; ++idx) {
        char *block = (char *)malloc((size_t)slot * sizeof(char));
        if (!block) {
            int k;
            for (k = 0; k < idx; ++k) {
                char *ptr = *(texts + k);
                free((void *)ptr);
            }
            free((void *)texts);
            printf("Failed to allocate memory\n");
            return 8;
        }
        *(texts + idx) = block;
    }

    char *result = (char *)malloc(res_cap * sizeof(char));
    if (!result) {
        int k;
        for (k = 0; k < max_texts; ++k) {
            char *ptr = *(texts + k);
            free((void *)ptr);
        }
        free((void *)texts);
        printf("Failed to allocate memory\n");
        return 8;
    }

    // Now safe to prompt for count
    printf("Podaj liczbe tekstow do wprowadzenia: ");

    int n = 0;
    if (scanf("%d", &n) != 1) {
        printf("Incorrect input\n");
        int k;
        for (k = 0; k < max_texts; ++k) {
            char *ptr = *(texts + k);
            free((void *)ptr);
        }
        free((void *)texts);
        free((void *)result);
        return 1;
    }

    if (n < 2 || n > 4) {
        printf("Incorrect input data\n");
        int k;
        for (k = 0; k < max_texts; ++k) {
            char *ptr = *(texts + k);
            free((void *)ptr);
        }
        free((void *)texts);
        free((void *)result);
        return 2;
    }

    // Consume the rest of the line after the number
    drain_line();

    // Prompt for texts and read exactly n lines
    printf("Podaj teksty: ");

    int i;
    for (i = 0; i < n; ++i) {
        char *dst = *(texts + i);
        if (!fgets(dst, slot, stdin)) {
            // EOF or error
            printf("Incorrect input\n");
            int k;
            for (k = 0; k < max_texts; ++k) {
                char *ptr = *(texts + k);
                free((void *)ptr);
            }
            free((void *)texts);
            free((void *)result);
            return 1;
        }

        // Remove trailing newline if present; if not, line was too long -> drain
        char *p = dst;
        int had_nl = 0;
        while (*p && *p != '\n') ++p;
        if (*p == '\n') { *p = '\0'; had_nl = 1; }
        if (!had_nl) drain_line();
    }

    // Concatenate based on n
    int rc = 0;
    if (n == 2) {
        rc = concatenate(result, (int)res_cap, 2, *(texts + 0), *(texts + 1));
    } else if (n == 3) {
        rc = concatenate(result, (int)res_cap, 3, *(texts + 0), *(texts + 1), *(texts + 2));
    } else {
        rc = concatenate(result, (int)res_cap, 4, *(texts + 0), *(texts + 1), *(texts + 2), *(texts + 3));
    }

    if (rc != 0) {
        // Should not happen with our buffers; treat as memory/data error
        printf("Failed to allocate memory\n");
        int k;
        for (k = 0; k < max_texts; ++k) {
            char *ptr = *(texts + k);
            free((void *)ptr);
        }
        free((void *)texts);
        free((void *)result);
        return 8;
    }

    // Print result in a single line, no extra characters
    fputs(result, stdout);

    // Cleanup
    int k;
    for (k = 0; k < max_texts; ++k) {
        char *ptr = *(texts + k);
        free((void *)ptr);
    }
    free((void *)texts);
    free((void *)result);
    return 0;
}
