/* Implementation of character operations and text modifier */

#include "char_operations.h"
#include <stdlib.h>

char lower_to_upper(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return (char)('A' + (ch - 'a'));
    }
    return ch;
}

char upper_to_lower(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return (char)('a' + (ch - 'A'));
    }
    return ch;
}

char space_to_dash(char ch) {
    if (ch == ' ') {
        return '_';
    }
    return ch;
}

char reverse_letter(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return (char)('z' - (ch - 'a'));
    }
    if (ch >= 'A' && ch <= 'Z') {
        return (char)('Z' - (ch - 'A'));
    }
    return ch;
}

char *letter_modifier(const char *input_text, char (*modifier)(char)) {
    if (!input_text || !modifier) {
        return NULL;
    }

    /* Determine length without using indexing */
    const char *p = input_text;
    size_t len = 0u;
    while (*p != '\0') {
        ++len;
        ++p;
    }

    /* Allocate result buffer (exactly once) */
    char *out = (char *)malloc(len + 1u);
    if (!out) {
        return NULL;
    }

    /* Stream-transform characters */
    const char *src = input_text;
    char *dst = out;
    while (*src != '\0') {
        *dst = modifier(*src);
        ++src;
        ++dst;
    }
    *dst = '\0';

    return out;
}
