#include <stdarg.h>
#include <stddef.h>
#include "concatenate.h"
#ifdef INSIDE_DANTE
#include "tested_declarations.h"
#endif

static size_t cstr_len(const char *s) {
    if (!s) return 0u;
    const char *p = s;
    while (*p) ++p;
    return (size_t)(p - s);
}

int concatenate(char *buf, int size, int texts_count, ...) {
    if (!buf || size <= 0 || texts_count <= 0) return 1;
    size_t capacity = (size_t)size;

    va_list ap;
    size_t needed = 0u;

    // First pass: compute required length (without temporary allocations)
    va_start(ap, texts_count);
    int i = 0;
    for (i = 0; i < texts_count; ++i) {
        char *s = va_arg(ap, char *);
        if (!s) { va_end(ap); return 1; }
        needed += cstr_len(s);
        if (i + 1 < texts_count) needed += 1u; // space between texts
    }
    va_end(ap);

    // +1 for terminating null character
    if (needed + 1u > capacity) return 2;

    // Second pass: copy into destination streaming through arguments
    va_start(ap, texts_count);
    char *out = buf;
    for (i = 0; i < texts_count; ++i) {
        char *s = va_arg(ap, char *);
        const char *p = s;
        if (i > 0) { *out = ' '; ++out; }
        while (*p) { *out = *p; ++out; ++p; }
    }
    va_end(ap);

    *out = '\0';
    return 0;
}
