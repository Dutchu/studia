//
// Created by Bartek on 22.08.2025.
//

#ifndef UNION_INT_BITS_H
#define UNION_INT_BITS_H

/**
 * @struct octet_t
 * @brief Represents 8 individual bits using bit-fields.
 *
 * This struct is packed into a single unsigned char (1 byte).
 */
struct octet_t {
    unsigned char bit0 : 1; // Least Significant Bit (LSB)
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
    unsigned char bit5 : 1;
    unsigned char bit6 : 1;
    unsigned char bit7 : 1; // Most Significant Bit (MSB)
};

/**
 * @union bit_set
 * @brief Represents a 32-bit value, allowing it to be interpreted
 * as different data types that share the same memory location.
 *
 * The layout of the structs (words, bytes, octets) assumes a
 * little-endian architecture, which is standard for most modern PCs.
 */
union bit_set {
    // View 1: A single 32-bit unsigned integer.
    unsigned int uint_value;

    // View 2: Two 16-bit words.
    struct {
        unsigned short w0; // Least significant word
        unsigned short w1; // Most significant word
    } words;

    // View 3: Four 8-bit bytes.
    struct {
        unsigned char b0; // Least significant byte
        unsigned char b1;
        unsigned char b2;
        unsigned char b3; // Most significant byte
    } bytes;

    // View 4: Four octets of 8 bits each.
    struct {
        struct octet_t o0; // Least significant octet
        struct octet_t o1;
        struct octet_t o2;
        struct octet_t o3; // Most significant octet
    } octets;
};

#endif //UNION_INT_BITS_H
