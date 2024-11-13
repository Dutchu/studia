//
// Created by Bartek on 11.05.2022.
//

#include "struct_utils.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>


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

    printf("[write_structs_to_file] n0th array_of_structs_to_use->size: %d\n",
           (*(array_of_structs_to_use + 0 * struct_size))->size);
    printf("[write_structs_to_file] n1st array_of_structs_to_use->size: %d\n",
           (*(array_of_structs_to_use + 1 * struct_size))->size);
    printf("[write_structs_to_file] n2nd array_of_structs_to_use->size: %d\n",
           (*(array_of_structs_to_use + 2 * struct_size))->size);

    return 0;
}

int comp(const void *elem1, const void *elem2) {
    struct file_t f = *((struct file_t *) elem1);
    struct file_t s = *((struct file_t *) elem2);
    if (f.size > s.size) return 1;
    if (f.size < s.size) return -1;
    return 0;
}

struct file_t *find_min(const struct file_t *files, int size) {
    if (files == NULL || size <= 0) {
        return NULL;
    }

    int min = 0;
    for (int i = 0; i < size; i++) {
        if ( (files + i)->size < (files + min)->size ) { min = i; }
    }

    return (struct file_t *)(files + min);
}

int open_file(struct file_t *f, const char *filename) {

    if (f == NULL || filename == NULL) return 1;

    FILE *file;

    file = fopen(filename, "a");
    if (file == NULL) return 2;
    int result;
    result = get_file_size(file);
    printf("[open_file] File size : %d\n", result);
    f->f = file;
    f->size = result;

    return 0;
}

int get_file_size(FILE *f_handle) {
    if (f_handle == NULL) {
        printf("Handle is null");
        return -1;
    }
    unsigned long l_file_size;

    // obtain file size:
    fseek(f_handle, 0, SEEK_END);
    l_file_size = ftell(f_handle);
    rewind(f_handle);

    return (int) l_file_size;
}

void print(struct file_t *files, int size) {

    for (int i = 0; i < size; i++) {
        printf("%d\n", (files + i)->size);
    }
}

void print_string_array(char **array, int size) {

    for (int i = 0; i < size; i++) {
        printf("[%d]", *(*(array + i)));
        printf("%s\n", *(array + i));
    }

}


int take_input(char *input) {
    if (input == NULL) return -1;

    printf("[take_input] Enter file names:%c", ' ');
    if (fgets(input, FILE_NAME_BUFFER_SIZE, stdin)) {
        *(input + strcspn(input, "\n")) = 0;
        printf("[take_input] input: %s\n", input);
    }

    return 0;
}

void close_file(struct file_t *f) {
    if ( f == NULL ) return;
    if ( f->f == NULL ) return;
    fclose(f->f);
}



