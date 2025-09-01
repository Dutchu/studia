//
// Created by Bartek on 02.06.2025.
//

#include "word_set.h"
#include <stdio.h>

int main() {
    union word_set words;
    union word_set *p_words = &words;

    printf("Podaj liczbę: ");
    if (1 != scanf("%d", &p_words->i_word)) {
        printf("Incorrect input");
        return 1;
    }

    for (unsigned short i = 0; (unsigned short) i < sizeof(union word_set) / sizeof(unsigned short); ++i) {
        printf("%hu ", *(p_words->h_word + i));
    }
}