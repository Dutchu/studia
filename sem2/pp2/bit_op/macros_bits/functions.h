//
// Macros for bit operations per task description.
//

#ifndef BIT_OP_FUNCTIONS_H
#define BIT_OP_FUNCTIONS_H

#include <limits.h>
#include <stdio.h>

// Counts set and cleared bits for the width of the value's type.
// Usage: COUNT_BITS(value, &set_count, &cleared_count)
#define COUNT_BITS(value, p_set, p_cleared)                           \
    do {                                                              \
        size_t __cb_bits = sizeof(value) * CHAR_BIT;                  \
        unsigned long long __cb_v = (unsigned long long)(value);      \
        size_t __cb_set = 0;                                          \
        for (size_t __cb_i = 0; __cb_i < __cb_bits; ++__cb_i) {       \
            if (((__cb_v >> __cb_i) & 1ULL) != 0ULL) {                \
                ++__cb_set;                                            \
            }                                                         \
        }                                                             \
        *(p_set) = (int)__cb_set;                                     \
        *(p_cleared) = (int)(__cb_bits - __cb_set);                   \
    } while (0)

// Displays the binary representation (MSB -> LSB) of the value,
// using as many bits as the value's type width, followed by a newline.
// Usage: DISPLAY_BITS(value)
#define DISPLAY_BITS(value)                                           \
    do {                                                              \
        size_t __db_bits = sizeof(value) * CHAR_BIT;                  \
        unsigned long long __db_v = (unsigned long long)(value);      \
        for (size_t __db_i = 0; __db_i < __db_bits; ++__db_i) {       \
            size_t __db_shift = __db_bits - 1 - __db_i;               \
            putchar(((__db_v >> __db_shift) & 1ULL) ? '1' : '0');     \
        }                                                             \
        putchar('\n');                                               \
    } while (0)

// Reverses the order of bits in-place for the pointed variable,
// across the width of that variable's type.
// Usage: REVERSE_BITS(&variable)
#define REVERSE_BITS(p_value)                                         \
    do {                                                              \
        size_t __rb_bits = sizeof(*(p_value)) * CHAR_BIT;             \
        unsigned long long __rb_v = (unsigned long long)(*(p_value)); \
        unsigned long long __rb_r = 0ULL;                             \
        for (size_t __rb_i = 0; __rb_i < __rb_bits; ++__rb_i) {       \
            __rb_r = (__rb_r << 1) | (__rb_v & 1ULL);                 \
            __rb_v >>= 1;                                             \
        }                                                             \
        *(p_value) = (unsigned long long)__rb_r;                      \
    } while (0)

#endif // BIT_OP_FUNCTIONS_H
