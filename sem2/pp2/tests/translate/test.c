//
// Created by Bartek on 26.04.2025.
//
#include "translator.h"

/**
 * @brief Reads word pairs from a file and stores them in a dynamically allocated array.
 *
 * Reads a file where each line is expected to contain two words separated by a space
 * (e.g., "czesc hello"). It dynamically allocates an array of pointers to word_t
 * structures. Each word_t structure and its internal strings (text_pl, text_en)
 * are also dynamically allocated.
 *
 * @param filename The path to the file to read.
 * @param errcode Pointer to an error_t enum where the status code will be written.
 * ERR_OK on success, otherwise an error code.
 * @return struct word_t** A dynamically allocated array of pointers to struct word_t.
 * Each element points to a dynamically allocated struct word_t.
 * The strings text_pl and text_en within each struct are also
 * dynamically allocated.
 * Returns NULL on failure (e.g., file error, memory error,
 * no valid words found). Check *errcode for the specific reason.
 * The caller is responsible for freeing the returned array and
 * all its contents using free_words_array() or similar logic.
 * The returned array itself is NOT NULL-terminated; its size
 * needs to be tracked separately (e.g., by counting elements
 * until an error occurs or by modifying the function to return
 * the size). For this example, we assume the caller knows how
 * many valid words were intended or will use the error code.
 * (Alternatively, the function could return the count via another pointer).
 */
struct word_t** read_words(const char* filename, enum error_t* errcode) {
    FILE *file = NULL;
    char line[MAX_LINE_LENGTH];
    const char *delimiter = " \t\n\r"; // Include space, tab, newline, carriage return

    struct word_t** words_array = NULL; // The array of pointers we will return
    size_t num_words = 0;             // Number of words read so far
    size_t capacity = 0;              // Current allocated capacity of words_array

    // 1. Initialize error code
    if (!errcode) {
        // If errcode pointer is NULL, we cannot report errors. Abort.
        // Or handle this differently based on requirements.
        fprintf(stderr, "Error: errcode pointer cannot be NULL.\n");
        return NULL; // Cannot proceed without error reporting mechanism
    }
    *errcode = ERROR_OK;

    // 2. Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        *errcode = ERROR_FILE_IO;
        return NULL;
    }

    // 3. Read line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove trailing newline if present (robustly handles \n and \r\n)
        line[strcspn(line, "\r\n")] = 0;

        // Skip empty or whitespace-only lines
        if (strspn(line, " \t") == strlen(line)) {
            continue;
        }

        // Tokenize the line
        char *pl_token = strtok(line, delimiter);
        char *en_token = strtok(NULL, delimiter);
        char *remaining = strtok(NULL, delimiter); // Check for extra tokens

        // Validate format: exactly two tokens expected
        if (!pl_token || !en_token || remaining != NULL) {
            // Optionally: Log a warning for invalid lines
            fprintf(stderr, "Warning: Skipping invalid line format: '%s'\n", line);
            // Continue to the next line instead of treating as fatal error
            // *errcode = ERR_INVALID_FORMAT; // Uncomment if invalid format should stop processing
            // goto cleanup_error; // Uncomment if invalid format should stop processing
            continue;
        }


        // 4. Resize the array of pointers if necessary
        if (num_words >= capacity) {
            size_t new_capacity = (capacity == 0) ? INITIAL_CAPACITY : capacity * 2;
            // Prevent potential integer overflow on large capacities
            if (new_capacity <= capacity) {
                fprintf(stderr, "Error: Capacity overflow detected.\n");
                *errcode = ERROR_MEMORY; // Treat overflow as a memory allocation issue
                goto cleanup_error;
            }

            struct word_t** temp = realloc(words_array, new_capacity * sizeof(struct word_t*));
            if (temp == NULL) {
                perror("Error reallocating words array");
                *errcode = ERROR_MEMORY;
                goto cleanup_error;
            }
            words_array = temp;
            capacity = new_capacity;
        }

        // 5. Allocate memory for the current word_t struct
        struct word_t* current_word = malloc(sizeof(struct word_t));
        if (current_word == NULL) {
            perror("Error allocating memory for word struct");
            *errcode = ERROR_MEMORY;
            goto cleanup_error;
        }
        current_word->text_pl = NULL; // Initialize pointers for cleanup safety
        current_word->text_en = NULL;

        // 6. Allocate memory and copy the strings (strdup allocates and copies)
        current_word->text_pl = strdup(pl_token);
        if (current_word->text_pl == NULL) {
            perror("Error duplicating Polish text");
            free(current_word); // Free the struct allocated just before
            *errcode = ERROR_MEMORY;
            goto cleanup_error;
        }

        current_word->text_en = strdup(en_token);
        if (current_word->text_en == NULL) {
            perror("Error duplicating English text");
            free(current_word->text_pl); // Free the first string
            free(current_word);          // Free the struct
            *errcode = ERROR_MEMORY;
            goto cleanup_error;
        }

        // 7. Store the pointer to the new struct in the array
        words_array[num_words] = current_word;
        num_words++;
    }

    // Check for read errors after the loop
    if (ferror(file)) {
        perror("Error reading from file");
        // Decide if this should override previous errors or be a specific error
        *errcode = ERROR_FILE_IO; // Re-using file open error, or define ERR_FILE_READ
        goto cleanup_error;
    }

    // 8. Final checks and cleanup
    fclose(file); // Close file successfully

    if (num_words == 0) {
        // File was opened but contained no valid lines
        *errcode = ERROR_FILE_IO;
        free(words_array); // Free the initial (or resized) potentially non-NULL pointer
        return NULL;
    }

    // Optional: Trim the array to the exact size to save memory
    struct word_t** final_array = realloc(words_array, num_words * sizeof(struct word_t*));
    if (final_array == NULL && num_words > 0) {
        // Realloc failure when shrinking is unlikely but possible.
        // The original 'words_array' is still valid. We can choose
        // to return it (slightly oversized) or treat it as an error.
        // Let's return the original one in this case, as data is intact.
        fprintf(stderr, "Warning: Failed to shrink array to final size, returning slightly oversized array.\n");
        // *errcode = ERR_MEM_ALLOC; // Optionally signal this minor issue
        // goto cleanup_error; // If strict memory usage is critical
    } else if (num_words > 0) {
        words_array = final_array; // Use the potentially shrunk array
    }
    // else: num_words is 0, words_array is already NULL or freed.

    // Success!
    *errcode = ERROR_OK;
    return words_array;

// Error handling block: Cleans up allocated resources before returning NULL
    cleanup_error:
    if (file) {
        fclose(file);
    }
    // Free all allocated structs and their strings, and the main array
    free_words_array(words_array, num_words); // num_words is how many were successfully added
    return NULL;
}

/**
 * @brief Helper function to free the memory allocated by read_words.
 *
 * Iterates through the array of pointers, freeing the text strings,
 * the word_t struct itself, and finally the array of pointers.
 *
 * @param words The array of pointers to free (struct word_t**).
 * @param count The number of elements in the array (pointers to free).
 */
void free_words_array(struct word_t** words, size_t count) {
    if (!words) {
        return; // Nothing to free
    }
    for (size_t i = 0; i < count; ++i) {
        if (words[i]) {
            free(words[i]->text_pl); // Free Polish string (strdup'd)
            free(words[i]->text_en); // Free English string (strdup'd)
            free(words[i]);          // Free the struct word_t itself
        }
    }
    free(words); // Free the array of pointers
}