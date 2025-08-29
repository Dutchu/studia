#include <stdio.h>
#include <ctype.h>
#include "int_operations.h"

/**
 *
0 - dodawanie,
1 - odejmowanie,
2 - dzielenie,
3 - mnożenie.
 */

int add_int(int a, int b) {
    return a + b;
}

int sub_int(int a, int b) {
    return a - b;
}

int div_int(int a, int b) {
    if (b == 0) return 0;
    return a / b;
}

int mul_int(int a, int b) {
    return a * b;
}

typedef int (*binary_operation)(int, int);

int calculate(int a, int b, binary_operation op) {
    return op(a, b);
}

int main(void) {
    int a, b, operation;

    printf("Enter numbers: ");
    if (scanf("%d %d", &a, &b) != 2) {
        printf("Incorrect input\n");
        return 1;
    }

    // 2. Check for any remaining non-whitespace characters.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (!isspace(c)) {
            // Found a non-whitespace character, indicating too much input.
            printf("Incorrect input\n");
            return 1;
        }
    }

    printf("Choose an operation: ");
    if (scanf("%d", &operation) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    // 2. Check for any remaining non-whitespace characters.
    while ((c = getchar()) != '\n' && c != EOF) {
        if (!isspace(c)) {
            // Found a non-whitespace character, indicating too much input.
            printf("Incorrect input\n");
            return 1;
        }
    }

    int result;
    switch (operation) {
        case 0:
            result = calculate(a, b, add_int);
            break;
        case 1:
            result = calculate(a, b, sub_int);
            break;
        case 2:
            result = calculate(a, b, div_int);
            break;
        case 3:
            result = calculate(a, b, mul_int);
            break;
        default:
            printf("Incorrect input data");
            return 2;
    }

    printf("Result: %d", result);

    return 0;
}
