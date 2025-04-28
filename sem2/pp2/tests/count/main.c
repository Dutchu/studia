//
// Created by Bartek on 28.04.2025.
//
#include "defs.h"

int main() {
    enum error_code_t err;

    struct file_t **result = words_read("test.txt", &err);

    if (result == NULL) {
        printf("ERROR CODE: %d", err);
    }

    return 0;
}
