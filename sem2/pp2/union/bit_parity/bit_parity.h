//
// Created by Bartek on 22.08.2025.
//

#ifndef UNION_BIT_PARITY_H
#define UNION_BIT_PARITY_H

/**
 * @union parity_checker
 * @brief Represents a 32-bit value, allowing access to the whole integer
 * or its 32 individual bits.
 *
 * This union is used to count the number of set bits (1s) without
 * using bitwise operators. The size of the union is determined by its
 * largest member, which is the 4-byte unsigned int.
 */
union parity_checker {
    // Member to access the entire 32-bit integer.
    unsigned int uint_value;

    // Member to access each of the 32 bits individually.
    // The bit-fields are packed into a 4-byte integer.
    struct {
        unsigned int bit0 : 1;
        unsigned int bit1 : 1;
        unsigned int bit2 : 1;
        unsigned int bit3 : 1;
        unsigned int bit4 : 1;
        unsigned int bit5 : 1;
        unsigned int bit6 : 1;
        unsigned int bit7 : 1;
        unsigned int bit8 : 1;
        unsigned int bit9 : 1;
        unsigned int bit10 : 1;
        unsigned int bit11 : 1;
        unsigned int bit12 : 1;
        unsigned int bit13 : 1;
        unsigned int bit14 : 1;
        unsigned int bit15 : 1;
        unsigned int bit16 : 1;
        unsigned int bit17 : 1;
        unsigned int bit18 : 1;
        unsigned int bit19 : 1;
        unsigned int bit20 : 1;
        unsigned int bit21 : 1;
        unsigned int bit22 : 1;
        unsigned int bit23 : 1;
        unsigned int bit24 : 1;
        unsigned int bit25 : 1;
        unsigned int bit26 : 1;
        unsigned int bit27 : 1;
        unsigned int bit28 : 1;
        unsigned int bit29 : 1;
        unsigned int bit30 : 1;
        unsigned int bit31 : 1;
    } bits;
};

#endif //UNION_BIT_PARITY_H
