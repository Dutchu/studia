//
// Created by Bartek on 22.08.2025.
//
#ifndef UNION_BIT_SET_H
#define UNION_BIT_SET_H

/**
 * @union bit_set
 * @brief Represents a single byte (8 bits), providing access to the whole value
 * or its individual bits.
 *
 * This union is essential for manipulating bits without using bitwise operators.
 * The size is 1 byte, determined by the size of unsigned char. The bit order
 * assumes a little-endian architecture, common on most PCs.
 */
union bit_set {
    // Member to access the entire 8-bit byte value.
    unsigned char byte_value;

    // Member to access each of the 8 bits individually.
    struct {
        unsigned char bit0 : 1; // Least Significant Bit (LSB)
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1; // Most Significant Bit (MSB)
    } bits;
};


#endif //UNION_BIT_SET_H
