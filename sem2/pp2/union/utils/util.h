// util.h
// Created by Bartek on 02.05.2025.
//

#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stddef.h>

union byte_set {
    int number_i;
    unsigned char number_bytes[sizeof(int)];
};

void print_union(union byte_set *union_ptr);

#endif //UTIL_H