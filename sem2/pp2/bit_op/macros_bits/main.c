#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>
#include "functions.h"

static int read_number_as_ull(unsigned long long* out_value) {
    char buf[256];
    if (scanf("%255s", buf) != 1) {
        return 1; // Incorrect input
    }
    // Validate characters: only digits allowed
    size_t len = strlen(buf);
    if (len == 0) {
        return 1; // Incorrect input
    }
    for (size_t i = 0; i < len; ++i) {
        if (!isdigit((unsigned char)buf[i])) {
            return 1; // Incorrect input (bad chars)
        }
    }
    errno = 0;
    char* endptr = NULL;
    unsigned long long value = strtoull(buf, &endptr, 10);
    if (errno == ERANGE || endptr == NULL || *endptr != '\0') {
        return 2; // Incorrect input data (overflow or parse issue despite digits)
    }
    *out_value = value;
    return 0;
}

int main(void) {
    int type;
    printf("Enter data type: ");
    fflush(stdout);
    if (scanf("%d", &type) != 1) {
        printf("Incorrect input\n");
        return 1;
    }
    if (type < 0 || type > 2) {
        printf("Incorrect input data\n");
        return 2;
    }

    printf("Enter an integer number: ");
    fflush(stdout);
    unsigned long long in_val = 0ULL;
    int rn = read_number_as_ull(&in_val);
    if (rn == 1) {
        printf("Incorrect input\n");
        return 1;
    } else if (rn != 0) {
        printf("Incorrect input data\n");
        return 2;
    }

    if (type == 1) {
        // unsigned short (16-bit)
        if (in_val > (unsigned long long)UINT16_MAX) {
            printf("Incorrect input data\n");
            return 2;
        }
        unsigned short n = (unsigned short)in_val;
        int set = 0, cleared = 0;
        COUNT_BITS(n, &set, &cleared);
        printf("%d\n", set);
        printf("%d\n", cleared);
        DISPLAY_BITS(n);
        REVERSE_BITS(&n);
        DISPLAY_BITS(n);
    } else if (type == 0) {
        // unsigned int (32-bit)
        if (in_val > (unsigned long long)UINT32_MAX) {
            printf("Incorrect input data\n");
            return 2;
        }
        unsigned int n = (unsigned int)in_val;
        int set = 0, cleared = 0;
        COUNT_BITS(n, &set, &cleared);
        printf("%d\n", set);
        printf("%d\n", cleared);
        DISPLAY_BITS(n);
        REVERSE_BITS(&n);
        DISPLAY_BITS(n);
    } else {
        // type == 2: unsigned long long (64-bit)
        // in_val is already ull; any value accepted within ULL range
        unsigned long long n = in_val;
        int set = 0, cleared = 0;
        COUNT_BITS(n, &set, &cleared);
        printf("%d\n", set);
        printf("%d\n", cleared);
        DISPLAY_BITS(n);
        REVERSE_BITS(&n);
        DISPLAY_BITS(n);
    }

    return 0;
}
