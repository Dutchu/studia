#include "stdio.h"
#include "malloc.h"

#define NUMBER 5

struct file_t {
    FILE *f;
    int size;
};

void print(struct file_t *files, int size);
void populate(struct file_t *files, int size, FILE *f);
void modify(struct file_t *files, int size);

int main() {

    struct file_t *files;
    struct file_t *file;
    FILE *f = fopen("..\\elo.txt", "w+");

    files = malloc(NUMBER * sizeof(struct file_t));
    file = malloc( sizeof(struct file_t));

    populate(files, 10, f);
    print(files, 10);
    modify(files, 10);
    print(files, 10);

    return 0;
}

void print(struct file_t *files, int size) {

    for (int i = 0; i < size; i++) {
        printf("%d\n", (files + i)->size);
    }

}

void populate(struct file_t *files, int size, FILE *f) {

    for (int i = 0; i < size; i++) {
        (files + i)->f = f;
        (files + i)->size = i;
    }

}

void modify(struct file_t *files, int size) {

    for (int i = 0; i < size; i++) {

        if(i == 5){
            (files + i)->size = 2345;
        }

    }

}