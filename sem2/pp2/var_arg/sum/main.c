#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBERS_COUNT 3
#define BUFF_SIZE 64

int stats(int *sum, float *avg, int num,...) ;

void clear_stdin_buffer(void) {
    int c;
    // Loop continues as long as the character read is not a newline
    // and not the end-of-file marker.
    while ((c = getchar()) != '\n' && c != EOF) {
        // The loop body is empty because its only purpose is to consume characters.
    }
}

int main(void) {

    char buff[BUFF_SIZE];
    int numbers[NUMBERS_COUNT];
    int num;

    printf("Enter number of elements: ");
    if (scanf("%d", &num) != 1) {
        printf("Incorrect input");
        return 1;
    }

    if (num > NUMBERS_COUNT || num < 1) {
        printf("Incorrect input data");
        return 2;
    }

    clear_stdin_buffer();

    printf("Enter numbers: ");
    if (!fgets(buff, BUFF_SIZE, stdin)) {
        printf("Incorrect input");
        return 1;
    }

    char *endptr;
    char *current = buff;

    long val;
    int count = 0;
    while (count < NUMBERS_COUNT) {
        errno = 0;
        val = strtol(current, &endptr, 10);

        if (errno == ERANGE) {
            printf("Incorrect input");
            return 1;
        }
        if (endptr == current) {
            break;
        }

        *(numbers + count) = val;
        count++;
        current = endptr;
    }

    // After the loop, re-check for invalid characters.
    // This handles cases like "1 2 3a".
    current = endptr;
    while (isspace((unsigned char)*current)) {
        current++;
    }

    if (*current != '\0') {
        printf("Incorrect input");
        return 1;
    }


    if (count != num) {
        printf("Incorrect input");
        return 1;
    }


    int sum;
    float avg;
    if (stats(&sum, &avg, num, *(numbers + 0), *(numbers + 1), *(numbers + 2)) != 0) {

    }

    printf("%d %f", sum, avg);

    return 0;
}

int stats(int *sum, float *avg, int num,...) {
    if (sum == NULL || avg == NULL) return 1;
    if (num < 1) return 1;
    *sum = 0;
    *avg = 0;

    va_list args;

    va_start(args, num);

    int x;
    for (int i = 0; i < num; i++) {
         x = va_arg(args, int);
        *sum = *sum + x;
        *avg = (float)*sum / (float)(i+1);
    }

    va_end(args);

    return 0;
}