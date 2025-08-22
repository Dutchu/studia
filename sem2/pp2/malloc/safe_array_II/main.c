//
// Created by Bartek on 21.08.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "array.h"

// Define a reasonable buffer size for reading a single integer from the user.
#define USER_INPUT_BUFFER_SIZE 12

/**
 * @brief Reads a line of text from stdin and safely converts it to an integer.
 *
 * This function handles various input errors, such as non-numeric characters,
 * values outside the integer range, and input lines that are too long.
 *
 * @param input_buffer A character buffer to store the user's input line.
 * @param number_read A pointer to an integer where the result will be stored.
 * @return 0 on success, 1 on any conversion or input error.
 */
int read_user_int(char *input_buffer, int *number_read) {
    // Read a line from standard input.
    if (fgets(input_buffer, USER_INPUT_BUFFER_SIZE, stdin) == NULL) {
        return 1; // fgets failed
    }

    // If the input string does not contain a newline, it means the input was
    // too long for the buffer. We must clear the rest of the line from stdin.
    if (strchr(input_buffer, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // Use strtol for robust string-to-long conversion.
    errno = 0;
    char *end_ptr;
    long value = strtol(input_buffer, &end_ptr, 10);

    // Check for conversion errors.
    if (end_ptr == input_buffer) return 1; // No digits were found.
    if (*end_ptr != '\n' && *end_ptr != '\0') return 1; // Extra non-numeric characters found.
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) return 1; // Value out of int range.

    *number_read = (int)value;
    return 0;
}

/**
 * @brief Main function to drive the dynamic array program.
 *
 * This program prompts the user for an array capacity, creates the array,
 * reads integers to add to it until 0 is entered or the array is full,
 * and finally displays the contents.
 *
 * @return 0 on success, or a non-zero error code (1, 2, or 8) on failure.
 */
int main() {
    struct array_t arr;
    int capacity;
    int return_code = 0;
    int is_created = 0; // Flag to prevent destroying an uninitialized array.
    char* input_buff = malloc(USER_INPUT_BUFFER_SIZE);
    if (input_buff == NULL) {
        // A very basic failure, unlikely to happen but good practice to check.
        return 8;
    }

    // 1. Get the initial capacity from the user.
    printf("Podaj rozmiar tablicy: ");
    if (read_user_int(input_buff, &capacity) != 0) {
        printf("Incorrect input\n");
        return_code = 1;
        goto cleanup;
    }

    if (capacity <= 0) {
        printf("Incorrect input data\n");
        return_code = 2;
        goto cleanup;
    }

    // 2. Create the array structure.
    if (array_create(&arr, capacity) != 0) {
        printf("Failed to allocate memory\n");
        return_code = 8;
        goto cleanup;
    }
    is_created = 1; // Mark that creation was successful.

    // 3. Read numbers from the user and add them to the array.
    printf("Podaj liczby do zapisania:\n");
    while (1) {
        int value;
        if (read_user_int(input_buff, &value) != 0) {
            printf("Incorrect input\n");
            return_code = 1;
            goto cleanup;
        }

        // The number 0 is the sentinel value to stop input.
        if (value == 0) {
            break;
        }

        // Try to add the value to the array.
        int push_result = array_push_back(&arr, value);
        if (push_result != 0) {
            // A non-zero result means the element could not be added,
            // which implies the buffer is full in this context.
            printf("Buffer is full\n");
            break;
        }
    }

    // 4. Display the final contents of the array.
    if (arr.size == 0) {
        printf("Buffer is empty\n");
    } else {
        array_display(&arr);
    }

// 5. Centralized cleanup point.
    cleanup:
    if (is_created) {
        array_destroy(&arr);
    }
    free(input_buff);
    return return_code;
}