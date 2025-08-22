//
// Created by Bartek on 21.08.2025.
//

/**
 * @file main.c
 * @brief Main program for advanced array manipulation.
 *
 * Kopiowanie gĹÄbokie (deep copy) oznacza tworzenie caĹkowicie nowej,
 * niezaleĹźnej kopii obiektu. W kontekĹcie struktury array_t,
 * nie wystarczy skopiowaÄ wartoĹci pĂłl (size, capacity, ptr).
 * NaleĹźy zaalokowaÄ nowy, oddzielny blok pamiÄci na dane i skopiowaÄ
 * do niego zawartoĹÄ oryginalnej tablicy. DziÄki temu modyfikacje
 * w jednej tablicy (oryginalnej lub kopii) nie wpĹywajÄ na drugÄ.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "array.h"
#include "tested_declarations.h"
#include "rdebug.h"

#define USER_INPUT_BUFFER_SIZE 12

int read_user_int(char *input_buffer, int *number_read);

/**
 * @brief Main function to drive the dynamic array program.
 *
 * This program prompts for an array capacity, fills the array with user input,
 * separates the numbers into odd and even arrays, and displays the results.
 *
 * @return 0 on success, or a non-zero error code (1, 2, 3, or 8) on failure.
 */
int main() {
    struct array_t main_arr, odd_arr, even_arr;
    int capacity;
    int return_code = 0;

    int is_main_created = 0;
    int is_odd_created = 0;
    int is_even_created = 0;

    char input_buff[USER_INPUT_BUFFER_SIZE];

    printf("Podaj liczbÄ elementĂłw tablicy: ");
    int read_res = read_user_int(input_buff, &capacity);
    if (read_res != 0) {
        if (read_res == 1) {
            printf("Incorrect input\n");
            return 1;
        } else { // read_res == 2, an I/O error occurred
            printf("Failed to allocate memory\n");
            return 8;
        }
    }

    if (capacity <= 0) {
        printf("Incorrect input data\n");
        return_code = 2;
        goto cleanup;
    }

    if (array_create(&main_arr, capacity) != 0) {
        printf("Failed to allocate memory\n");
        return_code = 8;
        goto cleanup;
    }
    is_main_created = 1;

    printf("Podaj kolejne liczby, ktĂłre majÄ zostaÄ dodane do tablicy: ");
    while (1) {
        int value;
        read_res = read_user_int(input_buff, &value);
        if (read_res != 0) {
            printf("Incorrect input\n");
            return_code = 1;
            goto cleanup;
        }

        if (value == 0) {
            break;
        }

        if (array_push_back(&main_arr, value) != 0) {
            printf("Buffer is full\n");
            break;
        }
    }

    if (main_arr.size == 0) {
        printf("Not enough data available\n");
        return_code = 3;
        goto cleanup;
    }

    int separate_result = array_separate(&main_arr, &odd_arr, &even_arr);

    if (separate_result <= 0) {
        printf("Failed to allocate memory\n");
        return_code = 8;
        goto cleanup;
    }

    if (separate_result & 1) is_odd_created = 1;
    if (separate_result & 2) is_even_created = 1;

    array_display(&main_arr);
    printf("\n");

    if (is_odd_created) {
        array_display(&odd_arr);
    } else {
        printf("Buffer is empty");
    }
    printf("\n");

    if (is_even_created) {
        array_display(&even_arr);
    } else {
        printf("Buffer is empty");
    }
    printf("\n");

    cleanup:
    if (is_main_created) array_destroy(&main_arr);
    if (is_odd_created) array_destroy(&odd_arr);
    if (is_even_created) array_destroy(&even_arr);
    return return_code;
}

int read_user_int(char *input_buffer, int *number_read) {
    if (fgets(input_buffer, USER_INPUT_BUFFER_SIZE, stdin) == NULL) {
        return ferror(stdin) ? 2 : 1;
    }

    if (strchr(input_buffer, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    errno = 0;
    char *end_ptr;
    long value = strtol(input_buffer, &end_ptr, 10);

    if (end_ptr == input_buffer) return 1;

    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) return 1;

    *number_read = (int) value;
    return 0;
}
