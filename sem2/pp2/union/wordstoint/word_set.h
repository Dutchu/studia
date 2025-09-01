//
// Created by Bartek on 02.06.2025.
//

#ifndef UNION_WORD_SET_H
#define UNION_WORD_SET_H

union word_set {
    int i_word;
    unsigned short h_word[sizeof(int) / sizeof(unsigned short)];
};

#endif //UNION_WORD_SET_H
