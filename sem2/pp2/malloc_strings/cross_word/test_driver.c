#include <stdio.h>
#include <stdlib.h>

// Prototypes from main.c
int create_leading_word_cross(const char *first, const char *second, char ***result);
int create_double_leading_word_cross(
    const char *first, const char *second, const char *third, const char *fourth,
    char ***result, char ***first_cross, char ***second_cross);
void destroy(char **words);

static void print_rows(const char *title, char **rows) {
    printf("%s\n", title);
    if (!rows) { printf("<NULL>\n"); return; }
    char **p = rows; int n = 0;
    while (*p) { printf("%s\n", *p); ++p; ++n; }
    printf("(rows=%d)\n\n", n);
}

int main(void) {
    // TEST10: create_leading_word_cross with long vertical and short horizontal
    char **out1 = NULL;
    int rc1 = create_leading_word_cross("RJCASHSXYIBOVDBDMOQW", "RX", &out1);
    printf("TEST10 rc=%d (expected 0)\n", rc1);
    print_rows("TEST10 output:", out1);
    destroy(out1);

    // TEST129: create_double with NULL result and long 11-char words
    char **fc = NULL, **sc = NULL;
    int rc2 = create_double_leading_word_cross("ENOUGH", "ZCBITDVFCHA", "ENOUGH", "ZCBITDVFCHA", NULL, &fc, &sc);
    printf("TEST129 rc=%d (expected 1)\n", rc2);
    print_rows("TEST129 first:", fc);
    print_rows("TEST129 second:", sc);
    // Should be NULLs; nothing to free
    return 0;
}

