// Dictionary API for word histogram
// No use of [] operator in this implementation

#ifndef DICTIONARY_H
#define DICTIONARY_H

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

// Creates an empty dictionary with capacity for N entries.
// On success returns pointer and sets *err_code to 0 (if provided).
// On invalid input sets *err_code to 1 and returns NULL.
// On memory failure sets *err_code to 2 and returns NULL.
struct dictionary_t* create_dictionary(int N, int *err_code);

// Destroys dictionary and sets *d to NULL. Does nothing on invalid input.
void destroy_dictionary(struct dictionary_t** d);

// Adds a word occurrence to dictionary d. Case-sensitive.
// Returns 0 on success, 1 on invalid input/inconsistent state, 2 on allocation failure.
int dictionary_add_word(struct dictionary_t *d, const char *word);

// Finds a word; returns pointer to word_count_t within dictionary or NULL
// if not found or on invalid input.
struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word);

// Displays dictionary entries in insertion order: "<word> <count>\n" per line.
// Does nothing on invalid input.
void dictionary_display(const struct dictionary_t *d);

#endif // DICTIONARY_H

