//
// Created by Bartek on 22.08.2025.
//

#ifndef UNION_BIT_SET_H
#define UNION_BIT_SET_H

union bit_set {
    unsigned char byte_value;
    struct {
        unsigned char bit0 : 1; //(LSB)
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1; //(MSB)
    } bits_t;

};

#endif //UNION_BIT_SET_H
