//
// Created by Bartek on 22.08.2025.
//

#include <stdio.h>
#include "int_bits.h"

/**
 * @brief Prints the 8 bits of a single octet from MSB to LSB.
 *
 * This helper function is used to avoid code repetition and contains
 * no conditional logic, adhering to the problem constraints.
 *
 * @param octet The octet_t struct to be printed.
 */
void print_octet(struct octet_t octet) {
    printf("%u", octet.bit7);
    printf("%u", octet.bit6);
    printf("%u", octet.bit5);
    printf("%u", octet.bit4);
    printf("%u", octet.bit3);
    printf("%u", octet.bit2);
    printf("%u", octet.bit1);
    printf("%u", octet.bit0);
}

/**
 * @brief Main function to read a 32-bit number and display its
 * different memory representations using a union.
 *
 * @return 0 on success, 1 on input error.
 */
int main() {
    union bit_set data;

    printf("Podaj liczbę: ");

    // The single allowed 'if' statement validates the user input.
    // "%u" reads a 32-bit unsigned integer.
    if (scanf("%u", &data.uint_value) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    // 1. Print as a single unsigned int.
    printf("%u\n", data.uint_value);

    // 2. Print as two 16-bit words.
    printf("%hu %hu\n", data.words.w0, data.words.w1);

    // 3. Print as four 8-bit bytes.
    printf("%hhu %hhu %hhu %hhu\n", data.bytes.b0, data.bytes.b1, data.bytes.b2, data.bytes.b3);

    // 4. Print as four octets of 8 bits each, from MSB to LSB.
    print_octet(data.octets.o0);
    printf(" ");
    print_octet(data.octets.o1);
    printf(" ");
    print_octet(data.octets.o2);
    printf(" ");
    print_octet(data.octets.o3);
    printf("\n");

    return 0;
}
