#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

// Generate API for int and double
DEFINE_ARRAY(int)
CREATE_ARRAY(int)
FREE_ARRAY(int)
SAVE_ARRAY(int)
LOAD_ARRAY(int)
SORT_ARRAY(int)

DEFINE_ARRAY(double)
CREATE_ARRAY(double)
FREE_ARRAY(double)
SAVE_ARRAY(double)
LOAD_ARRAY(double)
SORT_ARRAY(double)

static void print_msg(const char *msg) {
    fputs(msg, stdout);
    fputc('\n', stdout);
}

int main(void) {
    // Allocate filename buffer dynamically for 30 characters
    char *filename = (char *)malloc(30u);
    if (!filename) {
        print_msg("Failed to allocate memory");
        return 8;
    }

    fputs("Enter filename: ", stdout);
    if (scanf("%29s", filename) != 1) {
        free(filename);
        print_msg("Incorrect input");
        return 1;
    }

    int type = -1;
    fputs("Choose your type: ", stdout);
    if (scanf("%d", &type) != 1) {
        free(filename);
        print_msg("Incorrect input");
        return 1;
    }

    if (type != 0 && type != 1) {
        free(filename);
        print_msg("Incorrect input data");
        return 2;
    }

    int rc = 0;

    if (type == 0) { // int
        struct array_int_t *arr = NULL;
        rc = load_array_int(&arr, filename);
        if (rc == 1) { free(filename); print_msg("Incorrect input data"); return 2; }
        if (rc == 2) { free(filename); print_msg("Couldn't open file"); return 4; }
        if (rc == 3) { free(filename); print_msg("File corrupted"); return 6; }
        if (rc == 4) { free(filename); print_msg("Failed to allocate memory"); return 8; }

        rc = sort_array_int(arr);
        if (rc != 0) {
            free_array_int(arr);
            free(filename);
            print_msg("Incorrect input data");
            return 2;
        }

        rc = save_array_int(arr, filename);
        if (rc == 1) { free_array_int(arr); free(filename); print_msg("Incorrect input data"); return 2; }
        if (rc == 2) { free_array_int(arr); free(filename); print_msg("Couldn't create file"); return 5; }

        free_array_int(arr);
    } else { // double
        struct array_double_t *arr = NULL;
        rc = load_array_double(&arr, filename);
        if (rc == 1) { free(filename); print_msg("Incorrect input data"); return 2; }
        if (rc == 2) { free(filename); print_msg("Couldn't open file"); return 4; }
        if (rc == 3) { free(filename); print_msg("File corrupted"); return 6; }
        if (rc == 4) { free(filename); print_msg("Failed to allocate memory"); return 8; }

        rc = sort_array_double(arr);
        if (rc != 0) {
            free_array_double(arr);
            free(filename);
            print_msg("Incorrect input data");
            return 2;
        }

        rc = save_array_double(arr, filename);
        if (rc == 1) { free_array_double(arr); free(filename); print_msg("Incorrect input data"); return 2; }
        if (rc == 2) { free_array_double(arr); free(filename); print_msg("Couldn't create file"); return 5; }

        free_array_double(arr);
    }

    free(filename);
    print_msg("File saved");
    return 0;
}
