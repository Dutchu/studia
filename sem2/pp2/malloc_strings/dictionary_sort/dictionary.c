#include "dictionary.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int dict_is_valid(const struct dictionary_t *d) {
    if (!d) return 0;
    if (d->size < 0 || d->capacity < 0) return 0;
    if (d->size > d->capacity) return 0;
    if (d->capacity > 0 && d->wc == NULL) return 0;
    if (d->capacity == 0 && d->wc != NULL) return 0;
    return 1;
}

struct dictionary_t* create_dictionary(int N, int *err_code) {
    if (N <= 0) {
        if (err_code) *err_code = 1;
        return NULL;
    }

    struct dictionary_t *d = (struct dictionary_t*)malloc(sizeof(struct dictionary_t));
    if (!d) {
        if (err_code) *err_code = 2;
        return NULL;
    }

    struct word_count_t *wc = (struct word_count_t*)malloc((size_t)N * sizeof(struct word_count_t));
    if (!wc) {
        free(d);
        if (err_code) *err_code = 2;
        return NULL;
    }

    d->size = 0;
    d->capacity = N;
    d->wc = wc;

    int i = 0;
    struct word_count_t *p = d->wc;
    while (i < d->capacity) {
        p->word = NULL;
        p->counter = 0;
        ++i;
        ++p;
    }

    if (err_code) *err_code = 0;
    return d;
}

void destroy_dictionary(struct dictionary_t** d) {
    if (!d || !*d) return;
    struct dictionary_t *dict = *d;
    if (dict_is_valid(dict)) {
        struct word_count_t *p = dict->wc;
        struct word_count_t *end = dict->wc ? dict->wc + dict->size : NULL;
        while (p && p < end) {
            free(p->word);
            p->word = NULL;
            p->counter = 0;
            ++p;
        }
        free(dict->wc);
        dict->wc = NULL;
    }
    free(dict);
    *d = NULL;
}

struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word) {
    if (!dict_is_valid(d) || !word) return NULL;
    struct word_count_t *p = d->wc;
    struct word_count_t *end = d->wc + d->size;
    while (p < end) {
        if (p->word && strcmp(p->word, word) == 0) {
            return p;
        }
        ++p;
    }
    return NULL;
}

int dictionary_add_word(struct dictionary_t *d, const char *word) {
    if (!dict_is_valid(d) || !word) return 1;

    struct word_count_t *found = dictionary_find_word(d, word);
    if (found) {
        found->counter += 1;
        return 0;
    }

    if (d->size == d->capacity) {
        int new_cap = d->capacity > 0 ? d->capacity * 2 : 1;
        size_t bytes = (size_t)new_cap * sizeof(struct word_count_t);
        struct word_count_t *nw = (struct word_count_t*)realloc(d->wc, bytes);
        if (!nw) return 2;
        struct word_count_t *p = nw + d->capacity;
        struct word_count_t *end = nw + new_cap;
        while (p < end) {
            p->word = NULL;
            p->counter = 0;
            ++p;
        }
        d->wc = nw;
        d->capacity = new_cap;
    }

    size_t len = strlen(word);
    char *copy = (char*)malloc(len + 1u);
    if (!copy) return 2;
    memcpy(copy, word, len + 1u);

    struct word_count_t *slot = d->wc + d->size;
    slot->word = copy;
    slot->counter = 1;
    d->size += 1;
    return 0;
}

void dictionary_display(const struct dictionary_t *d) {
    if (!dict_is_valid(d)) return;
    struct word_count_t *p = d->wc;
    struct word_count_t *end = d->wc + d->size;
    while (p < end) {
        if (p->word) {
            printf("%s %d\n", p->word, p->counter);
        }
        ++p;
    }
}

// Helpers for sorting
static int ascii_lower(int c) { return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c; }
static int is_upper_word(const char *s) { return s && (*s >= 'A' && *s <= 'Z'); }

static int alpha_cmp_words(const char *a, const char *b) {
    int au = is_upper_word(a);
    int bu = is_upper_word(b);
    if (au != bu) return au ? -1 : 1; // uppercase-first group

    const unsigned char *pa = (const unsigned char*)a;
    const unsigned char *pb = (const unsigned char*)b;
    while (*pa && *pb) {
        int la = ascii_lower((int)*pa);
        int lb = ascii_lower((int)*pb);
        if (la != lb) return la < lb ? -1 : 1;
        if (*pa != *pb) {
            // same letter ignoring case, prefer uppercase
            int a_is_upper = (*pa >= 'A' && *pa <= 'Z');
            int b_is_upper = (*pb >= 'A' && *pb <= 'Z');
            if (a_is_upper != b_is_upper) return a_is_upper ? -1 : 1;
        }
        ++pa; ++pb;
    }
    if (*pa == 0 && *pb == 0) return 0;
    return *pa == 0 ? -1 : 1; // shorter first
}

static int qsort_alpha_cmp(const void *va, const void *vb) {
    const struct word_count_t *a = (const struct word_count_t*)va;
    const struct word_count_t *b = (const struct word_count_t*)vb;
    if (!a->word && !b->word) return 0;
    if (!a->word) return -1;
    if (!b->word) return 1;
    return alpha_cmp_words(a->word, b->word);
}

static int qsort_occ_cmp(const void *va, const void *vb) {
    const struct word_count_t *a = (const struct word_count_t*)va;
    const struct word_count_t *b = (const struct word_count_t*)vb;
    if (a->counter != b->counter) {
        return (a->counter > b->counter) ? -1 : 1; // descending by count
    }
    // tie-breaker: alphabetical
    if (!a->word && !b->word) return 0;
    if (!a->word) return -1;
    if (!b->word) return 1;
    return alpha_cmp_words(a->word, b->word);
}

int dictionary_sort_alphabetically(struct dictionary_t *d) {
    if (!dict_is_valid(d)) return 1;
    if (d->size <= 1) return 0;
    qsort((void*)d->wc, (size_t)d->size, sizeof(struct word_count_t), qsort_alpha_cmp);
    return 0;
}

int dictionary_sort_occurence(struct dictionary_t *d) {
    if (!dict_is_valid(d)) return 1;
    if (d->size <= 1) return 0;
    qsort((void*)d->wc, (size_t)d->size, sizeof(struct word_count_t), qsort_occ_cmp);
    return 0;
}

int save_dictionary_b(const struct dictionary_t *d, const char *filename) {
    if (!dict_is_valid(d) || !filename) return 1;
    FILE *f = fopen(filename, "wb");
    if (!f) return 2;

    int size = d->size;
    if (fwrite(&size, sizeof(int), 1, f) != 1) { fclose(f); return 2; }
    struct word_count_t *p = d->wc;
    struct word_count_t *end = d->wc + d->size;
    while (p < end) {
        int len = 0;
        if (p->word) {
            size_t sl = strlen(p->word);
            if (sl > (size_t)0x7fffffff) { fclose(f); return 2; }
            len = (int)sl;
        }
        if (fwrite(&len, sizeof(int), 1, f) != 1) { fclose(f); return 2; }
        if (len > 0) {
            if (fwrite(p->word, 1u, (size_t)len, f) != (size_t)len) { fclose(f); return 2; }
        }
        if (fwrite(&(p->counter), sizeof(int), 1, f) != 1) { fclose(f); return 2; }
        ++p;
    }
    fclose(f);
    return 0;
}

struct dictionary_t* load_dictionary_b(const char *filename, int *err_code) {
    if (!filename) { if (err_code) *err_code = 1; return NULL; }
    FILE *f = fopen(filename, "rb");
    if (!f) { if (err_code) *err_code = 2; return NULL; }

    int size = 0;
    if (fread(&size, sizeof(int), 1, f) != 1) { fclose(f); if (err_code) *err_code = 3; return NULL; }
    if (size < 0) { fclose(f); if (err_code) *err_code = 3; return NULL; }

    int ec = 0;
    int initial_cap = size > 0 ? size : 1; // ensure capacity >=1
    struct dictionary_t *d = create_dictionary(initial_cap, &ec);
    if (!d || ec != 0) { fclose(f); if (err_code) *err_code = 4; return NULL; }

    int i = 0;
    while (i < size) {
        int len = 0;
        if (fread(&len, sizeof(int), 1, f) != 1) { destroy_dictionary(&d); fclose(f); if (err_code) *err_code = 3; return NULL; }
        if (len < 0) { destroy_dictionary(&d); fclose(f); if (err_code) *err_code = 3; return NULL; }
        char *w = (char*)malloc((size_t)len + 1u);
        if (!w) { destroy_dictionary(&d); fclose(f); if (err_code) *err_code = 4; return NULL; }
        if (len > 0) {
            if (fread(w, 1u, (size_t)len, f) != (size_t)len) { free(w); destroy_dictionary(&d); fclose(f); if (err_code) *err_code = 3; return NULL; }
        }
        *(w + len) = '\0';
        int cnt = 0;
        if (fread(&cnt, sizeof(int), 1, f) != 1) { free(w); destroy_dictionary(&d); fclose(f); if (err_code) *err_code = 3; return NULL; }
        if (cnt < 0) { free(w); destroy_dictionary(&d); fclose(f); if (err_code) *err_code = 3; return NULL; }

        // append directly without extra copy
        if (d->size == d->capacity) {
            int new_cap = d->capacity > 0 ? d->capacity * 2 : 1;
            size_t bytes = (size_t)new_cap * sizeof(struct word_count_t);
            struct word_count_t *nw = (struct word_count_t*)realloc(d->wc, bytes);
            if (!nw) { free(w); destroy_dictionary(&d); fclose(f); if (err_code) *err_code = 4; return NULL; }
            // init new slots
            struct word_count_t *pp = nw + d->capacity;
            struct word_count_t *endp = nw + new_cap;
            while (pp < endp) { pp->word = NULL; pp->counter = 0; ++pp; }
            d->wc = nw;
            d->capacity = new_cap;
        }
        struct word_count_t *slot = d->wc + d->size;
        slot->word = w;
        slot->counter = cnt;
        d->size += 1;
        ++i;
    }

    fclose(f);
    if (err_code) *err_code = 0;
    return d;
}
