//
// Created by Bartek on 15.04.2025.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PHONE_BOOK_SIZE 8
#define MAX_PHONE_NUMBER_SIZE 9
#define FILE_NAME "2415test.txt"

struct entry_t {
    char name[20];
    char last_name[40];
    int number;
};
const struct entry_t* find_by_last_name(const struct entry_t* p, int size, const char *last_name);

void display(const struct entry_t *p);

int load_phonebook_t(const char *filename, struct entry_t *p, int size);

void for_strcpy(struct entry_t *p, const char *str);

void while_strcpy(struct entry_t *p, const char *str);

int main() {
    char *str_name = "name test";
    char *str_lastname = "lastname test";
    int phone_no = 451227189;

    char *filename = FILE_NAME;
    struct entry_t test = {};
    struct entry_t *test_ptr = &test;
    struct entry_t phone_book[PHONE_BOOK_SIZE] = {};

    if (strlen(str_name) < sizeof(test_ptr->name)) {
        strcpy(test_ptr->name, str_name);
    } else {
        printf("Error: Source string too long (this should ideally never happen).\n");
    }

    if (strlen(str_lastname) < sizeof(test_ptr->last_name)) {
        strcpy(test_ptr->last_name, str_lastname);
    } else {
        printf("Error: Source string too long (this should ideally never happen).\n");
    }

    printf("sizeof(test): %lu \t sizeof(*test): %lu\n", sizeof(test), sizeof(test_ptr));

    load_phonebook_t(filename, phone_book, 5);

//    while_strcpy(test_ptr, str_name);
//    for_strcpy(test_ptr, str_lastname);
    test.number = phone_no;

    display(test_ptr);
    printf("\n");
    display(phone_book + 0);
    printf("\n");
    display(phone_book + 1);
    printf("\n");
    display(phone_book + 2);
    printf("\n");
    display(phone_book + 3);
    printf("\n");
    display(phone_book + 4);
    printf("\n");

    const struct entry_t *found = find_by_last_name(phone_book, sizeof(*phone_book), "TylerMoore");

    printf("======found:\t=======\n");
    display(found);
    printf("\n");

    return 0;
}

void for_strcpy(struct entry_t *p, const char *str) {
    for (int i = 0; i < strlen(str); i++) {
        *(p->last_name + i) = *(str + i);
    }
}

void while_strcpy(struct entry_t *p, const char *str) {
    char *dest_ptr = p->name; // Pointer to the beginning of the name array
    int i = 0;

    // Loop through the source string and copy characters to the struct's name
    while (*str != '\0' && i < sizeof(p->name) - 1) {
        *dest_ptr = *str; // Dereference pointers to copy the character
        dest_ptr++;          // Move the destination pointer to the next character
        str++;           // Move the source pointer to the next character
        i++;
    }

    // Ensure null termination of the name in the struct
    *dest_ptr = '\0';
}

void display(const struct entry_t *p) {
    if (p == NULL) return;

    printf("Name: ");
    for (int i = 0; i < sizeof(p->name); i++) {
        char curr_char = *(p->name + i);

        if (curr_char == '\n') {
            break;
        }

        printf("%c", curr_char);
    }
    printf("\n");
    printf("Last name: ");
    for (int i = 0; i < sizeof(p->last_name); i++) {
        char curr_char = *(p->last_name + i);

        if (curr_char == '\n') {
            break;
        }

        printf("%c", curr_char);
    }
    printf("\n");
    printf("Phone number: %d", p->number);
}

int load_phonebook_t(const char *filename, struct entry_t *p, int size) {
    if (filename == NULL || p == NULL || size < 1) {
        return -1;
    }

    int result = 0;
    FILE *fp;
    size_t read_no;
    char phone_str[MAX_PHONE_NUMBER_SIZE];

    if ((fp = fopen(filename, "r")) == NULL) {
        return -2;
    }

    int next;
    for (int index = 0; index < size; index++) {
        next = 0;

        int i = 0;
        do {
            char c = fgetc(fp);

            // Checking for end of file
            if (feof(fp))
                break;
            // Checking for end of file
            if (c == '\0') break;
            if (c == '|')
                break;
            if (c == '\n' || c == '\r') {
                next = 1;
                break;
            }
//            if (i > (sizeof(p->name) - 1)) break;
            if (c == ' ') continue;

            *((p + index)->name + i) = c;
            i++;
//        printf("\n%c,", c);

        } while (1);

        int j = 0;
        do {
            // Taking input single character at a time
            char c = fgetc(fp);

            // Checking for end of file
            if (feof(fp))
                break;
            // Checking for end of file
            if (c == '|')
                break;
            if (c == '\n' || c == '\r') {
                next = 1;
                break;
            }
//            if (i > (sizeof(p->last_name) - 1)) break;
            if (c == ' ') continue;
            if (c == '\0') break;


            *((p + index)->last_name + j) = c;
            j++;
//        printf("\n%c,", c);
        } while (1);

        //don't read number end line character was reached
        if (next) continue;

        fseek(fp, 1, SEEK_CUR);

        read_no = fread(phone_str, sizeof(char), sizeof(phone_str), fp);
        if (read_no != sizeof(phone_str)) {
            printf("Wrong number of read structures! read_no = %zu, size = %lu\n", read_no, sizeof(phone_str));
        }

        char *end_ptr;
        printf("ftell(fp): %ld, j+i+fread(): %d\n", ftell(fp), j + i + (int) read_no);
        (p + index)->number = (int) strtol(phone_str, &end_ptr, 0);

        fseek(fp, 2, SEEK_CUR);
    }

    fclose(fp);
    return result;
}

const struct entry_t* find_by_last_name(const struct entry_t* p, int size, const char *last_name) {
    const struct entry_t *found_entry = NULL;

    for(int i = 0; i < size; i++) {
        if (*(p+i)->last_name != *last_name) continue;

        for (int last_name_idx = 0; last_name_idx < strlen(last_name); last_name_idx++) {
            if (*((p+i)->last_name + last_name_idx) != *(last_name+last_name_idx)) {
                found_entry = NULL;
                break;
            }

            found_entry = p+i;
        }
    }

    return found_entry;
}