#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

static int is_letter_ascii(int c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int main(void) {
    const size_t filebuf_len = 49u; // per specification

    char *buf = (char*)malloc(filebuf_len);
    if (!buf) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    // Prompt AFTER allocation, as required
    printf("Podaj nazwę pliku: ");

    if (!fgets(buf, (int)filebuf_len, stdin)) {
        // No input; attempt open will fail anyway; trim to empty
        *buf = '\0';
    } else {
        // trim trailing newline
        char *p = buf;
        while (*p && *p != '\n') ++p;
        if (*p == '\n') *p = '\0';
    }

    FILE *f = fopen(buf, "r");
    if (!f) {
        free(buf);
        printf("Couldn't open file\n");
        return 4;
    }

    int err = 0;
    struct dictionary_t *dict = create_dictionary(10, &err);
    if (!dict || err != 0) {
        fclose(f);
        free(buf);
        printf("Failed to allocate memory\n");
        return 8;
    }

    // Reuse buffer for word accumulation (expandable if needed)
    char *word_buf = buf;
    size_t word_cap = filebuf_len;
    char *wp = word_buf;

    int ch;
    while ((ch = fgetc(f)) != EOF) {
        if (is_letter_ascii(ch)) {
            size_t used = (size_t)(wp - word_buf);
            // ensure room for character + NUL
            if (used + 1u >= word_cap) {
                size_t new_cap = word_cap ? word_cap * 2u : 4u;
                while (used + 1u >= new_cap) new_cap *= 2u;
                char *nb = (char*)realloc(word_buf, new_cap);
                if (!nb) {
                    fclose(f);
                    destroy_dictionary(&dict);
                    free(word_buf);
                    printf("Failed to allocate memory\n");
                    return 8;
                }
                // update pointers after realloc
                wp = nb + (wp - word_buf);
                word_buf = nb;
                word_cap = new_cap;
            }
            *wp = (char)ch;
            ++wp;
        } else {
            if (wp > word_buf) {
                *wp = '\0';
                int ares = dictionary_add_word(dict, word_buf);
                if (ares == 2) {
                    fclose(f);
                    destroy_dictionary(&dict);
                    free(word_buf);
                    printf("Failed to allocate memory\n");
                    return 8;
                } else if (ares == 1) {
                    // Inconsistent dictionary input (should not happen in normal flow)
                    fclose(f);
                    destroy_dictionary(&dict);
                    free(word_buf);
                    return 1;
                }
                wp = word_buf; // reset for next word
            }
        }
    }

    // finalize last word if file ended while in a word
    if (wp > word_buf) {
        *wp = '\0';
        int ares = dictionary_add_word(dict, word_buf);
        if (ares == 2) {
            fclose(f);
            destroy_dictionary(&dict);
            free(word_buf);
            printf("Failed to allocate memory\n");
            return 8;
        } else if (ares == 1) {
            fclose(f);
            destroy_dictionary(&dict);
            free(word_buf);
            return 1;
        }
    }

    if (dict->size == 0) {
        printf("Nothing to show\n");
    } else {
        dictionary_display(dict);
    }

    fclose(f);
    destroy_dictionary(&dict);
    free(word_buf);
    return 0;
}

