//
// Created by Bartek on 11.05.2022.
//

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#define FILE_PATH "C:\\Users\\Bartek\\Desktop\\studia\\sem2\\pp2\\structs\\18\\file.txt"

int write_to_file(struct file_t *struct_to_use) {
    if (struct_to_use == NULL) {
        return -1;
    }
    int size = struct_to_use->size;
    printf("[write_to_file] file_t->size: %d\n", size);
    size = size + 100;
    struct_to_use->size = size;
    return 0;
}

int write_structs_to_file(struct file_t **array_of_structs_to_use) {
    if (array_of_structs_to_use == NULL) {
        return -1;
    }

    int struct_size = sizeof(struct file_t);

    printf("[write_structs_to_file] n0th array_of_structs_to_use->size: %d\n", (*(array_of_structs_to_use + 0 * struct_size))->size);
    printf("[write_structs_to_file] n1st array_of_structs_to_use->size: %d\n", (*(array_of_structs_to_use + 1 * struct_size))->size);
    printf("[write_structs_to_file] n2nd array_of_structs_to_use->size: %d\n", (*(array_of_structs_to_use + 2 * struct_size))->size);

    return 0;
}

int main(int argc, char **argv) {

    struct file_t struct_file;
    struct file_t *p_struct_file;
    struct file_t **array_struct_file = NULL;

    FILE* file_handle;
    file_handle = fopen(FILE_PATH, "w+");
    p_struct_file = &struct_file;

    struct_file.size = 16;
    struct_file.f = file_handle;

    write_to_file(&struct_file);

    printf("[main] file_t->size: %d\n", struct_file.size);

    p_struct_file = calloc(5, sizeof(struct file_t));
    array_struct_file = &p_struct_file;

    struct file_t data[2] = { {file_handle, 1}, {file_handle, 5} };

    printf("sizeof(struct file_t): %d\n", sizeof(struct file_t));

    int dane[5] = {1,2,3,4,5};
    printf("TEST: %d\n", *(dane + 4));

//    (array_struct_file + 16) = 1024;

    int x = 2;



    int size = sizeof(struct file_t);
    (*(array_struct_file + 0))->size = 5;
    (*(array_struct_file + 1))->size = 10;

    x = 4;

    struct file_t *end_pntr = *array_struct_file + sizeof(array_struct_file) / sizeof(*array_struct_file);
    struct file_t *start_pntr = *array_struct_file;
    int i = 0;
    while (start_pntr < end_pntr) {

        start_pntr->size = i;

        start_pntr++;
        i++;
    }



    printf("1%p\n", array_struct_file);
    printf("2%p\n", *array_struct_file);
    printf("3%d\n", (**array_struct_file).size);

    write_structs_to_file(&array_struct_file);

    fclose(file_handle);

    return 0;
}