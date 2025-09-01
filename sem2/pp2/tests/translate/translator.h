//
// Created by Bartek on 23.04.2025.
//

#ifndef TESTS_TRANSLATOR_H
#define TESTS_TRANSLATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> // For errno with file operations

#define MAX_LINE_LENGTH 256 // Maximum length of a line read from the file
#define INITIAL_CAPACITY 8 // Initial allocation size for the array

struct word_t {
    char* text_pl;
    char* text_en;
};

enum error_t{
    ERROR_OK,
    ERROR_INCORRECT_PARAMETERS,
    ERROR_FILE_IO,
    ERROR_MEMORY
};

// Helper function prototype to free the allocated memory
void free_words_array(struct word_t** words, size_t count);
struct word_t** read_words(const char* filename, enum error_t* errcode);
void delete_words(struct word_t** tab);
char** translate_words( struct word_t** tab, int n, ...);

#endif //TESTS_TRANSLATOR_H
