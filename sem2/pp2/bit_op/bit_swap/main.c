#include <stdio.h>
#include <stdint.h>

// Swaps bits b1 and b2 in the value pointed by pvalue.
// Returns 0 on success, 1 on invalid input.
unsigned int swap_bits(unsigned int *pvalue, int b1, int b2) {
    if (!pvalue) return 1;
    if (b1 < 0 || b1 >= 32 || b2 < 0 || b2 >= 32) return 1;

    if (b1 == b2) return 0; // nothing to do

    unsigned int v = *pvalue;
    unsigned int bit1 = (v >> b1) & 1u;
    unsigned int bit2 = (v >> b2) & 1u;
    if (bit1 != bit2) {
        // Flip both bits
        v ^= (1u << b1);
        v ^= (1u << b2);
        *pvalue = v;
    }
    return 0;
}

int main(void) {
    unsigned int value;
    int b1, b2;

    printf("Enter an uint32 number: ");
    fflush(stdout);
    if (scanf("%u", &value) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    printf("Enter 1st bit index: ");
    fflush(stdout);
    if (scanf("%d", &b1) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    printf("Enter 2nd bit index: ");
    fflush(stdout);
    if (scanf("%d", &b2) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    if (swap_bits(&value, b1, b2) != 0) {
        printf("Error\n");
        return 1;
    }

    printf("Result: %u\n", value);
    return 0;
}

