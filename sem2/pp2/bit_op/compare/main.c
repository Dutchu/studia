#include <stdio.h>

int is_equal(int a, int b);
int is_negative(int value);

int main(void) {
    int a, b;

    printf("Podaj dwie liczby: ");
    scanf("%d %d", &a, &b);

    if(is_equal(a, b)) {
        printf("rowne\n");
    } else {
        printf("nierowne\n");
    }

    if (is_negative(a)) {
        printf("ujemna ");
    } else {
        printf("nieujemna ");
    }

    if (is_negative(b)) {
        printf("ujemna ");
    } else {
        printf("nieujemna ");
    }

    return 0;
}

int is_equal(int a, int b) {
    return !(a^b);
}
int is_negative(int value) {
    return (value >> 31) & 1;
}