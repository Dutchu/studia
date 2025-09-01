// Extended dictionary API: sorting and binary I/O
// Constraint: no use of [] operator anywhere

#ifndef DICTIONARY_SORT_DICTIONARY_H
#define DICTIONARY_SORT_DICTIONARY_H

#include <stddef.h>

struct word_count_t {
    char *word;
    int counter;
};

struct dictionary_t {
    int size;
    int capacity;
    struct word_count_t *wc;
};

// Base 6.7 API
struct dictionary_t* create_dictionary(int N, int *err_code);
void destroy_dictionary(struct dictionary_t** d);
int dictionary_add_word(struct dictionary_t *d, const char *word);
struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word);
void dictionary_display(const struct dictionary_t *d);

// Sorting
int dictionary_sort_alphabetically(struct dictionary_t *d);
int dictionary_sort_occurence(struct dictionary_t *d);

// Binary I/O
int save_dictionary_b(const struct dictionary_t *d, const char *filename);
struct dictionary_t* load_dictionary_b(const char *filename, int *err_code);

#endif // DICTIONARY_SORT_DICTIONARY_H

