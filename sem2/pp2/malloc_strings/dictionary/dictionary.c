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

    // Initialize entries to safe defaults
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
        // Initialize new slots
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

