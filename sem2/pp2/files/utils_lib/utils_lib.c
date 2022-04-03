#include "utils_lib.h"
#include <stdio.h>

int file_size_from_path(const char *path) {
    if (path == NULL) { return -2; }

    FILE *f;
    f = fopen(path, "r");
    if (f == NULL) { return -1; }


    int rozmiar = 0;
    int i = 0;
    i = fgetc(f);

    while (i != EOF) {
        i = fgetc(f);
        rozmiar++;
        if (i == EOF) { break; }
    }

    fclose(f);
    return rozmiar;
}


int file_size_from_file(FILE *f) {

    if (f == NULL) {
        return -2;
    }

    long starting_position = ftell(f);

    if (fseek(f, 0L, SEEK_END) != 0) {
        return -1;
    }
    int file_size = ftell(f);

    fseek(f, starting_position, SEEK_SET);

    return file_size;
}
