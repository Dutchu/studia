//
// Created by Bartek on 28.08.2025.
//
#include <stdio.h>
#include "format_type.h"

struct statistic_t {
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};

int load(const char *filename, int ***ptr, enum save_format_t format) {return 0;}
int statistics_row(int **ptr, struct statistic_t **stats) {return 0;}
void destroy(int ***ptr) {}
void display(int **ptr) {}

int main(void) {
    struct statistic_t statistic;
    statistic.max = 100;
    printf("Hello Statistics! %d\n", statistic.max);
    return 0;
}
