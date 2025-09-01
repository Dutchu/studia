//
// Created by Bartek on 23.04.2025.
//

#include "translator.h"

// Helper function prototype to free the allocated memory
void free_words_array(struct word_t **words, size_t count);

struct word_t **read_words(const char *filename, enum error_t *errcode) {
    if (!errcode) return NULL;
    if (!filename) {
        *errcode = ERROR_INCORRECT_PARAMETERS;
        return NULL;
    }

    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        *errcode = ERROR_FILE_IO;
        return NULL;
    }

    char line_buff[MAX_LINE_LENGTH];
    char *delimiter = " ";

    char *token_pl;
    char *token_en;
    size_t pl_len;
    size_t en_len;
    size_t max_pl_len = 0;
    size_t max_en_len = 0;

    struct word_t **dictionary_ptr = NULL;
    size_t capacity = 0;
    size_t words_num = 0;

    struct word_t *current_word_t = NULL;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        *errcode = ERROR_FILE_IO;
        return NULL;
    }

    while (fgets(line_buff, MAX_LINE_LENGTH, fp) != NULL) {

        token_pl = strtok(line_buff, delimiter);
        token_en = strtok(NULL, delimiter);
        char *token_remaining = strtok(NULL, delimiter);

        // Validate format: exactly two tokens expected
        if (!token_pl || !token_en || token_remaining != NULL) {
            continue;
        }

        // 4. Resize the array of pointers if necessary
        if (capacity < words_num) {

            size_t new_capacity = (capacity == 0) ? INITIAL_CAPACITY : capacity * 2;
            // Prevent potential integer overflow on large capacities
            if (new_capacity <= capacity) {
                *errcode = ERROR_MEMORY; // Treat overflow as a memory allocation issue
                goto cleanup_error;
            }

            struct word_t** temp = realloc(dictionary_ptr, new_capacity * sizeof(struct word_t*));
            if (temp == NULL) {
                *errcode = ERROR_MEMORY;
                goto cleanup_error;
            }
            dictionary_ptr = temp;
            capacity = new_capacity;
        }

        //5. Allocate memory for the current word_t struct
        current_word_t = (struct word_t *) malloc(sizeof(struct word_t));
        if (current_word_t == NULL) {
            *errcode = ERROR_MEMORY;
            goto cleanup_error;
        }
        current_word_t->text_en = NULL;
        current_word_t->text_pl = NULL;

        // 6. Allocate memory and copy the strings (strdup allocates and copies)
        current_word_t->text_pl = strdup(token_pl);
        if (current_word_t->text_pl == NULL) {
            free(current_word_t);
            *errcode = ERROR_MEMORY;
            goto cleanup_error;
        }

        current_word_t->text_en = strdup(token_en);
        if (current_word_t->text_en == NULL) {
            free(current_word_t->text_pl);
            free(current_word_t);
            *errcode = ERROR_MEMORY;
            goto cleanup_error;
        }

        // 7. Store the pointer to the new struct in the array
        *(dictionary_ptr + words_num) = current_word_t;
        words_num++;
    }

    // Check for read errors after the loop
    if (ferror(fp)) {
        perror("Error reading from file");
        // Decide if this should override previous errors or be a specific error
        *errcode = ERROR_FILE_IO; // Re-using file open error, or define ERR_FILE_READ
        goto cleanup_error;
    }

    // 8. Final checks and cleanup
    fclose(fp); // Close file successfully

    if (words_num == 0) {
        // File was opened but contained no valid lines
        *errcode = ERROR_FILE_IO;
        free(dictionary_ptr); // Free the initial (or resized) potentially non-NULL pointer
        return NULL;
    }

    // Success!
    *errcode = ERROR_OK;
    return dictionary_ptr;

    //Error handling block: Cleans up allocated resources before returning NULL
    cleanup_error:
    if (fp) {
        fclose(fp);
    }
    //Free all allocated structs and their strings, and the main array
    free_words_array(dictionary_ptr, words_num); // num_words is how many were successfully added
    return NULL;
}


void free_words_array(struct word_t **words, size_t count) {
    if (!words) {
        return; // Nothing to free
    }
    for (size_t i = 0; i < count; ++i) {

        if (*(words+i)) {
            free((*(words+i))->text_pl); // Free Polish string (strdup'd)
            free(words[i]->text_en); // Free English string (strdup'd)
            free(words[i]);          // Free the struct word_t itself
        }
    }
    free(words); // Free the array of pointers
}