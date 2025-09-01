/* Text modifier using function pointers, streaming and heap-tight */

#include <stdio.h>
#include <stdlib.h>
#include "char_operations.h"

int main(void) {
    /* Allocate user input buffer first; only then prompt */
    char *buffer = (char *)malloc(1001);
    if (!buffer) {
        printf("failed to allocate memory\n");
        return 8;
    }

    printf("Podaj tekst: ");
    if (!fgets(buffer, 1001, stdin)) {
        free(buffer);
        printf("Incorrect input\n");
        return 1;
    }

    /* If input line exceeded 1000 chars, drain the rest until newline */
    const char *check = buffer;
    int has_nl = 0;
    while (*check != '\0') {
        if (*check == '\n') { has_nl = 1; break; }
        ++check;
    }
    if (!has_nl) {
        int c = getchar();
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
    }

    printf("Podaj rodzaj operacji: ");
    int op = -1;
    if (scanf("%d", &op) != 1) {
        free(buffer);
        printf("Incorrect input\n");
        return 1;
    }
    if (!(op == 0 || op == 1 || op == 2 || op == 3)) {
        free(buffer);
        printf("Incorrect input data\n");
        return 2;
    }

    /* Array of function pointers (declaration uses [], access via pointer arithmetic) */
    char (*funcs[])(char) = { lower_to_upper, upper_to_lower, space_to_dash, reverse_letter };
    char (*chosen)(char) = *(funcs + op);

    char *modified = letter_modifier((const char *)buffer, chosen);
    if (!modified) {
        free(buffer);
        printf("failed to allocate memory\n");
        return 8;
    }

    /* Print transformed text exactly as modified (may include newline from input) */
    printf("%s", modified);

    free(modified);
    free(buffer);
    return 0;
}
