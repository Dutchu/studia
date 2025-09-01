//
// Created by Bartek on 23.04.2025.
//
#include "stdio.h"

int hello_world(char *name) {
    if (!name) return -1;
    printf("Hello World from, %s!", name);
    return 0;
}