//
// Created by Bartek on 28.04.2025.
//
#include "defs.h"

struct file_t** words_read(const char* filename, enum error_code_t* error) {
    if (!error) return NULL;
    if (!filename) {
        *error = ERROR_CODE_INCORRECT_PARAMETERS;
        return NULL;
    }

    struct file_t **files_arr = NULL;
    struct file_t *file = NULL;
    FILE *fp = NULL;
    char *line_buff = NULL;
    size_t lines_count = 0;
    size_t files_count = 1;

    if ((fp = fopen(filename, "r")) == NULL) {
        *error = ERROR_CODE_FILE_NOT_EXISTS;
        return NULL;
    }

    while (fgets(line_buff, MAX_LINE_SIZE, fp) != NULL) {
        lines_count++;
    }

    files_arr = (struct file_t **)malloc(files_count * sizeof(struct file_t *));
    if (files_arr == NULL) {
        *error = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
        goto cleanup;
    }

    file = (struct file_t *)malloc(sizeof(struct file_t));
    if (file == NULL) {
        *error = ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY;
        goto cleanup;
    }


    return files_arr;

    cleanup:
    if (fp != NULL) {
        fclose(fp);
    }

    free_mem(files_arr, files_count);
}

void free_mem(struct file_t **files_arr, size_t count) {
    if (!files_arr) return;

    for (size_t i = 0; i < count; i++) {
        if (*(files_arr+i)) {
            free((*(files_arr + i))->words);
            free((*(files_arr + i))->name);
            free(*(files_arr + i));
        }
    }
    free(files_arr);
}