// Bit operations on uint32_t with input handling as specified

#include <stdio.h>
#include <stdint.h>

int toggle_bit(uint32_t* pvalue, int b) {
    if (!pvalue || b < 0 || b >= 32) return -1;
    *pvalue ^= (uint32_t)(1u << b);
    return 0;
}

int set_bit(uint32_t* pvalue, int b) {
    if (!pvalue || b < 0 || b >= 32) return -1;
    *pvalue |= (uint32_t)(1u << b);
    return 0;
}

int clear_bit(uint32_t* pvalue, int b) {
    if (!pvalue || b < 0 || b >= 32) return -1;
    *pvalue &= (uint32_t)~(1u << b);
    return 0;
}

int isset_bit(const uint32_t* pvalue, int b) {
    if (!pvalue || b < 0 || b >= 32) return -1;
    return (int)((*pvalue >> b) & 1u);
}

int main(void) {
    uint32_t value = 0u;
    unsigned int tmp_u = 0u;
    int bit_index = 0;
    int op = -1;

    printf("Enter a value: ");
    fflush(stdout);
    if (scanf("%u", &tmp_u) != 1) {
        printf("Incorrect input\n");
        return 1;
    }
    value = (uint32_t)tmp_u;

    printf("Enter an index of a bit: ");
    fflush(stdout);
    if (scanf("%d", &bit_index) != 1) {
        printf("Incorrect input\n");
        return 1;
    }
    if (bit_index < 0 || bit_index >= 32) {
        printf("Invalid bit index\n");
        return 1;
    }

    printf("Select operation (0-toggle, 1-set, 2-clear, 3-read): ");
    fflush(stdout);
    if (scanf("%d", &op) != 1) {
        printf("Incorrect input\n");
        return 1;
    }
    if (op < 0 || op > 3) {
        printf("Invalid operation\n");
        return 1;
    }

    if (op == 0) {
        if (toggle_bit(&value, bit_index) != 0) {
            printf("Incorrect input\n");
            return 1;
        }
        printf("%08x\n", value);
    } else if (op == 1) {
        if (set_bit(&value, bit_index) != 0) {
            printf("Incorrect input\n");
            return 1;
        }
        printf("%08x\n", value);
    } else if (op == 2) {
        if (clear_bit(&value, bit_index) != 0) {
            printf("Incorrect input\n");
            return 1;
        }
        printf("%08x\n", value);
    } else { // op == 3
        int bit = isset_bit(&value, bit_index);
        if (bit < 0) {
            printf("Incorrect input\n");
            return 1;
        }
        printf("%d\n", bit);
    }

    return 0;
}
