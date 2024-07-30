//
// Created by Bartek on 29.07.2024.
//
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "errno.h"

int LIMIT = 1000;

int main() {
    int num;
    int n;
    char buff[5];
    char filename[10];
    char contents[10];
    char *endptr;
    FILE *fp;

    unsigned int seed = (unsigned int) time(NULL) ^ getpid();
    srand(seed);

    printf("Podaj liczbę liczb:\n");
    if (fgets(buff, sizeof(buff), stdin) == NULL) {
        fprintf(stderr, "Incorrect input");
        return EXIT_FAILURE;
    }

    int len = strlen(buff);
    if (len == 0 || len > 4) {
        fprintf(stderr, "Incorrect input");
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtol(buff, &endptr, 10);
    if (errno != 0 || *endptr != '\0') {
        fprintf(stderr, "Incorrect input");
        return EXIT_FAILURE;
    }

    if (n < 1 || n > 1000) {
        fprintf(stderr, "Incorrect input data");
        return EXIT_FAILURE;
    }

    int next = 1;
    for (int i = 0; i < n; i++) {
        num = rand() % LIMIT;

        if (next == 1) {
            sprintf(filename, "%d", i / 10);
            strcat(filename, ".txt");
            printf("%s\n", filename);
            fp = fopen(filename, "w+");
        }

        if (fp == NULL) {
            fprintf(stderr, "Couldn't create file");
            exit(EXIT_FAILURE);
        }
        sprintf(contents, "%d, ", num);
        fwrite(contents, sizeof(char), strlen(contents), fp);

        if ((i % 10) == 9) {
            next = 1;
            fclose(fp);
        } else {
            next = 0;
        }
    }
}