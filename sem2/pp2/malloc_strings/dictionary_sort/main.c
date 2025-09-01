#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

static int is_letter_ascii(int c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static char* build_out_name(const char *in, const char *suffix) {
    if (!in || !suffix) return NULL;
    const char *s = in;
    const char *end = in;
    while (*end) ++end;
    const char *dot = end;
    const char *p = end;
    while (p > s) { --p; if (*p == '.') { dot = p; break; } }
    int has_dot = (dot < end && *dot == '.');

    size_t base_len = has_dot ? (size_t)(dot - s) : (size_t)(end - s);
    size_t suffix_len = strlen(suffix);
    size_t ext_copy_len = has_dot ? (size_t)(end - dot) : 0u; // keep original extension
    size_t add_bin_len = ext_copy_len ? 0u : 4u; // default to .bin if no extension
    size_t new_len = base_len + suffix_len + ext_copy_len + add_bin_len;
    char *out = (char*)malloc(new_len + 1u);
    if (!out) return NULL;

    char *w = out;
    if (base_len) { memcpy(w, s, base_len); w += base_len; }
    memcpy(w, suffix, suffix_len); w += suffix_len;
    if (ext_copy_len) { memcpy(w, dot, ext_copy_len); w += ext_copy_len; }
    else { memcpy(w, ".bin", 4u); w += 4u; }
    *w = '\0';
    return out;
}

int main(void) {
    const size_t filebuf_len = 40u; // per specification
    char *buf = (char*)malloc(filebuf_len);
    if (!buf) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    // Prompt AFTER allocation
    printf("Podaj nazwe pliku: ");
    if (!fgets(buf, (int)filebuf_len, stdin)) {
        *buf = '\0';
    } else {
        char *p = buf;
        while (*p && *p != '\n') ++p;
        if (*p == '\n') *p = '\0';
    }

    printf("Co chcesz teraz zrobić: ");
    int option = 0;
    int sc = scanf("%d", &option);
    if (sc != 1) {
        free(buf);
        printf("Incorrect input\n");
        return 1;
    }
    if (!(option == 0 || option == 1)) {
        free(buf);
        printf("Incorrect input data\n");
        return 2;
    }

    // Build output filenames now, before possibly reusing buf for words
    char *name_alpha = build_out_name(buf, "_alpha");
    char *name_occ = build_out_name(buf, "_occ");
    if (!name_alpha || !name_occ) {
        free(name_alpha);
        free(name_occ);
        free(buf);
        printf("Failed to allocate memory\n");
        return 8;
    }

    struct dictionary_t *dict = NULL;

    if (option == 0) {
        int ec = 0;
        dict = load_dictionary_b(buf, &ec);
        if (!dict) {
            if (ec == 4) { printf("Failed to allocate memory\n"); free(name_alpha); free(name_occ); free(buf); return 8; }
            if (ec == 2) { printf("Couldn't open file\n"); free(name_alpha); free(name_occ); free(buf); return 4; }
            if (ec == 3) { printf("File corrupted\n"); free(name_alpha); free(name_occ); free(buf); return 6; }
            // other errors treated as corrupted
            printf("File corrupted\n");
            free(name_alpha); free(name_occ); free(buf);
            return 6;
        }
    } else {
        FILE *f = fopen(buf, "r");
        if (!f) {
            free(name_alpha); free(name_occ); free(buf);
            printf("Couldn't open file\n");
            return 4;
        }
        int ec = 0;
        dict = create_dictionary(10, &ec);
        if (!dict || ec != 0) {
            fclose(f);
            free(name_alpha); free(name_occ); free(buf);
            printf("Failed to allocate memory\n");
            return 8;
        }

        // Reuse buffer for streaming words
        char *word_buf = buf;
        size_t word_cap = filebuf_len;
        char *wp = word_buf;

        int ch;
        while ((ch = fgetc(f)) != EOF) {
            if (is_letter_ascii(ch)) {
                size_t used = (size_t)(wp - word_buf);
                if (used + 1u >= word_cap) {
                    size_t new_cap = word_cap ? word_cap * 2u : 4u;
                    while (used + 1u >= new_cap) new_cap *= 2u;
                    char *nb = (char*)realloc(word_buf, new_cap);
                    if (!nb) {
                        fclose(f);
                        destroy_dictionary(&dict);
                        free(name_alpha); free(name_occ); free(word_buf);
                        printf("Failed to allocate memory\n");
                        return 8;
                    }
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
                        free(name_alpha); free(name_occ); free(word_buf);
                        printf("Failed to allocate memory\n");
                        return 8;
                    } else if (ares == 1) {
                        fclose(f);
                        destroy_dictionary(&dict);
                        free(name_alpha); free(name_occ); free(word_buf);
                        return 1;
                    }
                    wp = word_buf;
                }
            }
        }
        if (wp > word_buf) {
            *wp = '\0';
            int ares = dictionary_add_word(dict, word_buf);
            if (ares == 2) {
                fclose(f);
                destroy_dictionary(&dict);
                free(name_alpha); free(name_occ); free(word_buf);
                printf("Failed to allocate memory\n");
                return 8;
            } else if (ares == 1) {
                fclose(f);
                destroy_dictionary(&dict);
                free(name_alpha); free(name_occ); free(word_buf);
                return 1;
            }
        }
        fclose(f);
        // we already built output names; free the (possibly reallocated) word buffer
        free(word_buf);
        buf = NULL;
    }

    // Sort by occurrence and save
    if (dictionary_sort_occurence(dict) == 0) {
        int s1 = save_dictionary_b(dict, name_occ);
        if (s1 == 0) printf("File saved\n");
        else printf("Couldn't create file\n");
    } else {
        // sorting failed due to invalid state; treat as no-save
        printf("Couldn't create file\n");
    }

    // Sort alphabetically and save
    if (dictionary_sort_alphabetically(dict) == 0) {
        int s2 = save_dictionary_b(dict, name_alpha);
        if (s2 == 0) printf("File saved\n");
        else printf("Couldn't create file\n");
    } else {
        printf("Couldn't create file\n");
    }

    destroy_dictionary(&dict);
    free(name_alpha);
    free(name_occ);
    free(buf);
    return 0;
}
