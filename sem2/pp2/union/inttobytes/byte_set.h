// byte_set.h
// Created by Bartek on 03.05.2025.
//

#ifndef UNION_BYTE_SET_H
#define UNION_BYTE_SET_H

#include <stddef.h>

union byte_set {
    int number_i;
    unsigned char number_bytes[sizeof(int)];
};

#endif //UNION_BYTE_SET_H
