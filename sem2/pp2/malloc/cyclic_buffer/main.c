//
// Created by Bartek on 07.06.2025.
//

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include "circular_buffer.h"

#define NUMBER_OF_DIGITS_FOR_USER_INPUT 8

int read_user_int(char *input_buffer, int *number_read);

int main() {

    struct circular_buffer_t *ptr_cb = NULL;
    int err, size, choice, item, return_code = 0;
    char* input_buff = malloc(NUMBER_OF_DIGITS_FOR_USER_INPUT);

    printf("Podaj rozmiar bufora: ");
    int read_res = read_user_int(input_buff, &size);
    if (read_res != 0) {
        printf("incorrect input\n");
        return_code = 1;
        goto clean_up;
    }

    if (size <= 0) {
        printf("Incorrect input data\n");
        return_code = 2;
        goto clean_up;
    }

    if (circular_buffer_create_struct(&ptr_cb, size) > 0) {
        printf("Failed to allocate memory\n");
        return_code = 8;
        goto clean_up;
    }

    while (1) {

        printf("Co chcesz zrobic? ");

        read_res = read_user_int(input_buff, &choice);
        if (read_res != 0) {
            printf("incorrect input\n");
            return_code = 1;
            goto clean_up;
        }

        switch (choice) {
            case 0:
                goto clean_up;

            case 1:
                printf("Podaj liczbe ");
                read_res = read_user_int(input_buff, &item);
                if (read_res == 0) circular_buffer_push_back(ptr_cb, item);
                else {
                    printf("incorrect input\n");
                    return_code = 1;
                    goto clean_up;
                }
                break;

            case 2:
                item = circular_buffer_pop_back(ptr_cb, &err);
                if (err == 0) printf("%d\n", item);
                else if (err == 1) printf("w przypadku błędnych danych wejściowych lub braku ich spójności.\n");
                else if (err == 2) printf("Buffer is empty\n");
                break;

            case 3:
                item = circular_buffer_pop_front(ptr_cb, &err);
                if (err == 0) printf("%d\n", item);
                else if (err == 1) printf("w przypadku błędnych danych wejściowych lub braku ich spójności.\n");
                else if (err == 2) printf("Buffer is empty\n");
                break;

            case 4:
                if (circular_buffer_empty(ptr_cb)) printf("Buffer is empty\n");
                else circular_buffer_display(ptr_cb);
                break;

            case 5:
                printf("%d\n", circular_buffer_empty(ptr_cb));
                break;

            case 6:
                printf("%hhu\n", ptr_cb->full);
                break;

            default:
                printf("Incorrect input data\n");
                break;
        }
    }

    clean_up:
    circular_buffer_destroy_struct(&ptr_cb);
    free(input_buff);
    return return_code;
}


int read_user_int(char *input_buffer, int *number_read) {
    if (fgets(input_buffer, NUMBER_OF_DIGITS_FOR_USER_INPUT, stdin) == NULL) {
        return feof(stdin) ? 2 : 1;
    }

    if (strchr(input_buffer, '\n') == NULL) {
        // There's garbage left in the input buffer. We must clear it.
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    errno = 0;
    char *end_ptr;
    long strtol_result = strtol(input_buffer, &end_ptr, 0);
    if (end_ptr == input_buffer) {
        return 1;
    }
    if (*end_ptr != '\n' && *end_ptr != '\0') {
        return 1;
    }
    if (errno == ERANGE) {
        return 1;
    }
    if (strtol_result > INT_MAX || strtol_result < INT_MIN) {
        return 1;
    }

    *number_read = (int) strtol_result;
    return 0;
}