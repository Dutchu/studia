#include "util.h"
#include <stdio.h>

int main() {
    union byte_set byte;
    byte.number_i = 20;
    printf("Hello, unions! %d", byte.number_i);
}