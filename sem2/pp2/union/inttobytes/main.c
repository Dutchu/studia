// W komentarzu na początku programu odpowiedz na następujące pytania:
// 1. Jak z wyświetlonych bajtów 68 67 66 65 powstaje wartość 1094861636?
// 2. Jak nazywa się kolejność 68 67 66 65 i 65 66 67 68?
// odp1: Zapis hexadecymalny np. 0x44 reprezentuje 8 bitów w bajcie -> 1000100. Int składa się z czterech takich ciągów bitowych które są ułożone według zasady LITTLE ENDIAN, albo BIG ENDIAN i czytane wedle ustalonej kolejności po kolei składając się na całą liczbę w zapisie bitowym.
// odp2: BIG ENDIAN -> 68 67 66 65, ponieważ wartość 68=0x44 która w liczbie 0x414243(44) reprezentuje najmniej istotny bajt znajduje się pod największym adresem w pamięci. 65 66 67 68 -> LITTLE ENDIAN, ponieważ LSB (65) znajduje się pod największym adresem.

#include "byte_set.h"
#include <stdio.h>

int main() {
    union byte_set set_u;
    union byte_set *set_ptr = &set_u;
//    int test = 0x41424344;

    printf("Podaj liczbe: \n");

    int result = scanf("%d", &set_ptr->number_i);
    if (result != 1) {
        printf("Incorrect input");
        return 1;
    }

//    set_u.number_i = test;
//    printf("%d\n", set_u.number_i);
//    printf("%s\n", set_u.number_bytes);
//
//
//    for (size_t i = 0; i < sizeof(int); ++i) {
//        printf("bytes[%zu]: 0x%02X | %d | Znak: '%c'\n",
//               i,
//               *(set_ptr->number_bytes + i),
//               *(set_ptr->number_bytes + i),
//               *(set_ptr->number_bytes + i) >= 32 && *(set_ptr->number_bytes + i) ? (char) *(set_ptr->number_bytes + i) : '?');
//    }
//
//    printf("------------------\n");

//    set_u.number_i = input;
//    printf("%d\n", set_u.number_i);
//    printf("%s\n", set_u.number_bytes);
//
//    for (size_t i = 0; i < sizeof(int); ++i) {
//        printf("bytes[%zu][%p]: 0x%02X | %d | Znak: '%c'\n",
//               i,
//               (set_ptr->number_bytes + i),
//               *(set_ptr->number_bytes + i),
//               *(set_ptr->number_bytes + i),
//               *(set_ptr->number_bytes + i) >= 32 && *(set_ptr->number_bytes + i) ? (char) *(set_ptr->number_bytes + i) : '?');
//    }
    for (size_t i = 0; i < sizeof(int); ++i) {
        printf("%d ", *(set_ptr->number_bytes + i));
    }

    return 0;
}
