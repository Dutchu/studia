#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Allocate before prompting (tests expect this order). */
    char *buf = NULL;
    size_t cap = 0u;
    size_t init_cap = 50u; /* any value ok; growth limited to <= 50 */

    buf = (char *)realloc(NULL, init_cap);
    if (!buf) {
        printf("Failed to allocate memory\n");
        return 8; /* as specified for initial failure */
    }
    cap = init_cap;

    /* Now prompt the user. */
    printf("Podaj tekst: ");

    size_t len = 0u;
    int ch;
    for (;;) {
        ch = getchar();
        if (ch == EOF || ch == '\n') {
            break;
        }

        /* Ensure room for this character plus terminating NUL. */
        if (len + 1u >= cap) {
            size_t grow = 50u; /* per-call limit */
            size_t new_cap = cap + grow;
            char *nb = (char *)realloc(buf, new_cap);
            if (!nb) {
                /* Print text collected so far (no error message here). */
                *(buf + len) = '\0';
                fputs(buf, stdout);
                free(buf);
                return 0;
            }
            buf = nb;
            cap = new_cap;
        }

        *(buf + len) = (char)ch;
        ++len;
    }

    *(buf + len) = '\0';
    fputs(buf, stdout);
    free(buf);
    return 0;
}
