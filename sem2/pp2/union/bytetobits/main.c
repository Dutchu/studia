//
// Created by Bartek on 22.08.2025.
//

#include <stdio.h>
#include "bit_set.h"

int main() {

    union bit_set data;

    printf("Podaj liczbe: ");

    if (scanf("%hhu", &data.byte_value) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    printf("%u ", data.bits_t.bit7);
    printf("%u ", data.bits_t.bit6);
    printf("%u ", data.bits_t.bit5);
    printf("%u ", data.bits_t.bit4);
    printf("%u ", data.bits_t.bit3);
    printf("%u ", data.bits_t.bit2);
    printf("%u ", data.bits_t.bit1);
    printf("%u\n", data.bits_t.bit0);

    return 0;
}