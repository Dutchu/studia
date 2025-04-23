//
// Created by Bartek on 23.04.2025.
//

#include <stddef.h>
#include "utils.h"
#include "stdio.h"

int main() {
    char *name = NULL;
    int result;

    if ((result = hello_world(name))){};
    printf("%d", result);

    return 0;
}