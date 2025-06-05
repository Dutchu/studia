//
// Created by Bartek on 05.06.2025.
//
#include <stdio.h>
#include <string.h>
#include "struct_utils.h"

int main() {
    struct student_t s_bartek;
    struct student_t *ptr_student = &s_bartek;
    strcpy(ptr_student->name, "Bartłomiej");
    strcpy(ptr_student->surname, "Bałszczyk");
    s_bartek.index = 177013;

    printf("Hello, student!\n");
    printf("name: %s\n", ptr_student->name);
    printf("surname: %s\n", ptr_student->surname);
    printf("index: %d\n", s_bartek.index);
}