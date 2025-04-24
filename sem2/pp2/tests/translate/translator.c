//
// Created by Bartek on 23.04.2025.
//

#include "translator.h"
#include "stddef.h"
#include "stdio.h"

#define LINES_COUNT 100
#define LINE_SIZE 50

struct word_t** read_words(const char* filename, enum error_t* errcode) {
    if (!filename || !errcode) return NULL;

    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        printf("[read_words] fopen() failed!\n");
        return NULL;
    }

    char line_buff[LINE_SIZE];

    if (fgets(line_buff, LINE_SIZE, fp) != line_buff) {
        printf("[read_words] fgets() failed!\n");
        return NULL;
    }

    

    return NULL;
}