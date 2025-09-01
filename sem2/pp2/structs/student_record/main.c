//
// Created by Bartek on 05.06.2025.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct student_t {
    char name[20];
    char surname[40];
    int index;
};

struct student_t *read(struct student_t *p, int *err_code);

void show(const struct student_t *p);

size_t is_valid_char(int c);

size_t is_ending_seq(int c);

size_t is_name_letter(int c);

size_t is_surname_letter(int c);

int main() {
    struct student_t s_student = {0};
    struct student_t *ptr_student = &s_student;
    int err = 2;

    printf("Podaj dane: \n");

    if (NULL == read(ptr_student, &err) || err > 0) {
        printf("Incorrect input");
        exit(err);
    }

    show(ptr_student);
}

struct student_t *read(struct student_t *p, int *err_code) {
    if (p == NULL && err_code == NULL) {
        return NULL;
    }
    if (p == NULL) {
        *err_code = 1;
        return NULL;
    }

    int c = '\0';
    int i = 0;
    int rev = 0;
    int i_name = 0;
    int i_surname = 0;
    int name_flag = 0;
    int surname_flag = 0;
    int index_flag = 0;
    int coma_flag = 0;
    int name_processing = 0;
    int surname_processing = 0;
    int index_processing = 0;
    int name_processing_started = 0;
    int surname_processing_started = 0;
    int index_processing_started = 0;

    struct student_t *result = NULL;
    p->index = 0;

    while (1) {
        c = getc(stdin);

        if (!is_valid_char(c)) {
            break;
        }

        //name guard
        if (name_flag == 0 && surname_flag == 0 && i_name < 20) {
            name_processing_started = 1;
            name_processing = 1;
            if (is_name_letter(c)) {
                memcpy(p->name + i, &c, sizeof(char));
                i_name++;
            }
            if (c == ',') {
                coma_flag = 1;
                rev = i;
            }
            if (coma_flag && c == ' ' && (i - rev == 1)) {
                name_flag = 1;
                name_processing = 0;
                coma_flag = 0;
                i = 0;
                *(p->name + i_name) = '\0';
                continue;
            }
        }//unhappy path
        if ((name_processing && !is_name_letter(c) && !is_ending_seq(c)) || (i_name > 19)) {
            break;
        }

        //surname guard
        if (name_flag == 1 && surname_flag == 0 && i_surname < 40) {
            surname_processing_started = 1;
            surname_processing = 1;
            if (is_surname_letter(c) && !coma_flag) {
                memcpy(p->surname + i, &c, sizeof(char));
                i_surname++;
            }
            //1. first start with coma
            if (c == ',') {
                coma_flag = 1;
                rev = i;
            }
            //2. then check previous coma and break loop blocking access again to surname
            if ((coma_flag && c == ' ' && (i - rev == 1))) {
                surname_flag = 1;
                surname_processing = 0;
                coma_flag = 0;
                i = 0;
                *(p->surname + i_surname) = '\0';
                continue;
            }
        }//unhappy path
        if ((surname_processing && !is_surname_letter(c) && !is_ending_seq(c)) || (i_surname > 39)) {
            break;
        }

        //index guard
        if (name_flag == 1 && surname_flag == 1) {
            index_processing_started = 1;
            index_processing = 1;
            if (isdigit(c)) {
                p->index = p->index * 10 + (c - '0');
            }
            if (i == 6 && c == '\n') {
                index_flag = 1;
                break;
            }
        }//unhappy path
        if (index_processing && !isdigit(c) && c != '\n' || (c == '\n' && i < 6)) {
            break;
        }

        i++;
    }

    int correct_name = 0;
    if (name_processing_started && name_flag) {
        correct_name = 1;
    }
    int correct_surname = 0;
    if (surname_processing_started && surname_flag) {
        correct_surname = 1;
    }
    int correct_index = 0;
    if (index_processing_started && index_flag) {
        correct_index = 1;
    }

    if (err_code != NULL) {
        if (!correct_name && !correct_surname && !correct_index) {
            *err_code = 1;
        } else if (correct_name && !correct_surname && !correct_index) {
            *err_code = 2;
        } else if (correct_name && correct_surname && !correct_index) {
            *err_code = 3;
        } else {
            *err_code = 0;
            result = p;
        }
    } else {
        if (correct_name && correct_surname && correct_index) {
            result = p;
        }
    }

    return result;
}

void show(const struct student_t *p) {
    if (p == NULL) return;
    printf("%s ", p->name);
    printf("%s, ", p->surname);
    printf("%06d", p->index);
}

size_t is_valid_char(int c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == ',' || c == '\n' || c == ' ' || c == '.' || c == '-') {
        return 1;
    } else {
        return 0;
    }
}

size_t is_ending_seq(int c) {
    if (c == ' ' || c == ',') {
        return 1;
    } else {
        return 0;
    }
}

size_t is_name_letter(int c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 46) {
        return 1;
    } else {
        return 0;
    }
}

size_t is_surname_letter(int c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 45 || c == 32) {
        return 1;
    } else {
        return 0;
    }
}