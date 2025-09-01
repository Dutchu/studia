//
// Created by Bartek on 28.04.2025.
//

#ifndef TESTS_DEFS_H
#define TESTS_DEFS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_LINE_SIZE 100

struct word_t {
    char *word;
    int count;
};

struct file_t {
    char *name;
    struct word_t **words;
};

enum error_code_t {
    ERROR_CODE_OK = 0,
    ERROR_CODE_INCORRECT_PARAMETERS = 1,
    ERROR_CODE_FILE_NOT_EXISTS = 2,
    ERROR_CODE_FILE_CORRUPTED = 3,
    ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY = 4
};

struct file_t** words_read (const char* filename, enum error_code_t* error);
void words_display (struct file_t** files, enum error_code_t* error);
void words_free (struct file_t*** files, enum error_code_t* error);
void free_mem(struct file_t **files_arr, size_t count);

#endif //TESTS_DEFS_H
