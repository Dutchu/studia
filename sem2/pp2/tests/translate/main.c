//
// Created by Bartek on 23.04.2025.
//

#include <stddef.h>
#include "utils.h"
#include "translator.h"
#include "stdio.h"

int main() {
    char *name = NULL;
    int result;
    enum error_t error;

    if ((result = hello_world(name))){};
    printf("%d\n", result);

    read_words("test.txt", &error);

    return 0;
}