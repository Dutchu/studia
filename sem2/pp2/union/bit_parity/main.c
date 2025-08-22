//
// Created by Bartek on 22.08.2025.
//

#include <stdio.h>
#include "bit_parity.h"

/**
 * @brief Main function to check if a 32-bit unsigned integer has an
 * even number of set bits (even parity).
 *
 * The program reads a number, uses a union to access its individual bits,
 * counts the number of set bits, and determines if the count is even.
 *
 * @return 0 on success, 1 on input error.
 */
int main() {
    union parity_checker data;
    int bit_count = 0;

    printf("Podaj wartosc: ");

    // Read the 32-bit unsigned integer directly into the union.
    if (scanf("%u", &data.uint_value) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    // Sum the values of all 32 bit-fields. Since each bit is either
    // 0 or 1, this sum gives the total count of set bits.
    bit_count += data.bits.bit0;
    bit_count += data.bits.bit1;
    bit_count += data.bits.bit2;
    bit_count += data.bits.bit3;
    bit_count += data.bits.bit4;
    bit_count += data.bits.bit5;
    bit_count += data.bits.bit6;
    bit_count += data.bits.bit7;
    bit_count += data.bits.bit8;
    bit_count += data.bits.bit9;
    bit_count += data.bits.bit10;
    bit_count += data.bits.bit11;
    bit_count += data.bits.bit12;
    bit_count += data.bits.bit13;
    bit_count += data.bits.bit14;
    bit_count += data.bits.bit15;
    bit_count += data.bits.bit16;
    bit_count += data.bits.bit17;
    bit_count += data.bits.bit18;
    bit_count += data.bits.bit19;
    bit_count += data.bits.bit20;
    bit_count += data.bits.bit21;
    bit_count += data.bits.bit22;
    bit_count += data.bits.bit23;
    bit_count += data.bits.bit24;
    bit_count += data.bits.bit25;
    bit_count += data.bits.bit26;
    bit_count += data.bits.bit27;
    bit_count += data.bits.bit28;
    bit_count += data.bits.bit29;
    bit_count += data.bits.bit30;
    bit_count += data.bits.bit31;

    // A number has even parity if the count of its set bits is even.
    if (bit_count % 2 == 0) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}
