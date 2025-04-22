//
// Created by Bartek on 22.04.2025.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define PHONE_BOOK_SIZE 8
#define MAX_PHONE_NUMBER_SIZE 9
#define NAME_SIZE 20
#define LASTNAME_SIZE 40
#define COL_DIV_SIZE 3
#define LINE_END_SIZE 2
#define INPUT_BUFFER_SIZE 100

struct entry_t {
    char name[NAME_SIZE];
    char last_name[LASTNAME_SIZE];
    int number;
};

const struct entry_t *find_by_last_name(const struct entry_t *p, int size, const char *last_name);


void display(const struct entry_t *p);

int load_phonebook_t(const char *filename, struct entry_t *p, int size);

int read_input_from_user(char *buffer, int buff_size);

int parse_line_to_entry(char *line, struct entry_t *entry);

int validate_name(char *str);

int validate_number(char *str);

char *trim_whitespace(char *str);

int main() {
    char *filename;
    char *lastname;
    char input_buffer[INPUT_BUFFER_SIZE];
    struct entry_t phone_book[PHONE_BOOK_SIZE];
    int result;

    printf("Enter file name: ");
    result = read_input_from_user(input_buffer, INPUT_BUFFER_SIZE);
    if (result == 1) return 1;
    trim_whitespace(input_buffer);
    filename = input_buffer;

    result = load_phonebook_t(filename, phone_book, sizeof(phone_book) / sizeof(*phone_book));
    if (result < 0) {
        printf("Couldn't open file");
        return 4;
    } else if (result == 0) {
        printf("File corrupted");
        return 6;
    }

    printf("Enter last name: ");
    result = read_input_from_user(input_buffer, INPUT_BUFFER_SIZE);
    if (result == 1) return 1;
    trim_whitespace(input_buffer);
    lastname = input_buffer;

    const struct entry_t *found = find_by_last_name(phone_book, sizeof(*phone_book), lastname);
    if (found == NULL) {
        printf("Couldn't find name");
        return 0;
    }

    display(found);

    return 0;
}

void display(const struct entry_t *p) {
    if (p == NULL) return;

    printf("Name: ");
    for (size_t i = 0; i < sizeof(p->name); i++) {
        char curr_char = *(p->name + i);

        if (curr_char == '\n' || curr_char == '\0') {
            break;
        }

        printf("%c", curr_char);
    }
    printf("\n");
    printf("Last name: ");
    for (size_t i = 0; i < sizeof(p->last_name); i++) {
        char curr_char = *(p->last_name + i);

        if (curr_char == '\n' || curr_char == '\0') {
            break;
        }

        printf("%c", curr_char);
    }
    printf("\n");
    printf("Phone number: %d", p->number);
}

int read_input_from_user(char *buffer, int buff_size) {

    if (!fgets(buffer, buff_size, stdin)) {
        return 1;
    }

    return 0;
}

int load_phonebook_t(const char *filename, struct entry_t *p, int size) {
    if (filename == NULL || p == NULL || size < 1) {
        return -1;
    }

    FILE *fp;
    size_t read_no = 0;
    const int ROW_SIZE =
            NAME_SIZE + COL_DIV_SIZE + LASTNAME_SIZE + COL_DIV_SIZE + MAX_PHONE_NUMBER_SIZE + LINE_END_SIZE;
    char line_buff[NAME_SIZE + COL_DIV_SIZE + LASTNAME_SIZE + COL_DIV_SIZE + MAX_PHONE_NUMBER_SIZE + LINE_END_SIZE];
    char *row;

    if ((fp = fopen(filename, "r")) == NULL) {
        return -2;
    }

    for (int r = 0; r < size; r++) {
        row = fgets(line_buff, ROW_SIZE, fp);

        if (parse_line_to_entry(row, p + read_no)) {
            read_no++;
        }
    }

    fclose(fp);
    return (int) read_no;
}

char *trim_whitespace(char *str) {

    if (str == NULL) return NULL;

    while (isspace((unsigned char) *str)) str++;

    if (*str == 0)
        return str;

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) {

        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_line_to_entry(char *line, struct entry_t *entry) {
    if (!line || !entry) return 0;

    char *trimmed_line = trim_whitespace(line);

    if (trimmed_line == NULL || strlen(trimmed_line) == 0) {
        return 0;
    }

    int field_count = 0;
    char *field_saveptr = NULL;
    char *name_str = NULL;
    char *lastname_str = NULL;
    char *number_str = NULL;

    char *field = strtok_r(trimmed_line, "|", &field_saveptr);
    while (field != NULL) {
        char *trimmed_field = trim_whitespace(field);
        int non_empty = (strlen(trimmed_field) > 0);

        if (non_empty) {
            field_count++;

            switch (field_count) {
                case 1:
                    name_str = trimmed_field;
                    break;
                case 2:
                    lastname_str = trimmed_field;
                    break;
                case 3:
                    number_str = trimmed_field;
                    break;
                default:
//                    printf("Skipping line (Unexpected field count): %s\n", line);
                    return 0;
            }
        } else {
//            printf("Skipping line (empty field detected): %s\n", line);
            return 0;
        }

        field = strtok_r(NULL, "|", &field_saveptr);
    }

    int is_valid_name = validate_name(name_str);
    int is_valid_lastname = validate_name(lastname_str);
    int is_valid_number = validate_number(number_str);

    if (!is_valid_name || !is_valid_lastname || !is_valid_number) {
//        printf("Validation of fields in a row failed!");
        return 0;
    }

    snprintf(entry->name, NAME_SIZE, "%s", name_str);
    snprintf(entry->last_name, LASTNAME_SIZE, "%s", lastname_str);

    char *endptr;
    long phone_number;
    if ((phone_number = strtol(number_str, &endptr, 10)) < 1 || *endptr != '\0') {
//        printf("Phone number conversion to a number failed");
        return 0;
    }
    entry->number = (int) phone_number;

    return 1;
}

int validate_name(char *str) {
    if (!str || strlen(str) == 0) return 0;
    int result = 1;

//    for (char *c = str; *c != '\0'; c++) {
//        if (!isalpha((unsigned char) *c) && *c != ' ' && *c != '-' && *c != '\'' && *c != '.') {
//            result = 0;
//        }
//    }

    return result;
}

int validate_number(char *str) {
    if (!str || strlen(str) == 0) return 0;
    int result = 1;

    int i = 0;
    for (char *c = str; *c != '\0'; c++) {
        if (!isdigit((unsigned char) *c) || i > MAX_PHONE_NUMBER_SIZE - 1) {
            result = 0;
        }

        i++;
    }

    return result;
}

const struct entry_t *find_by_last_name(const struct entry_t *p, int size, const char *last_name) {
    if (!p || !last_name) return NULL;

    const struct entry_t *found_entry = NULL;
    int found = 0;
    size_t lastname_len = strlen(last_name);

    for (int i = 0; i < size; i++) {
        if (found) break;
        if (*(p + i)->last_name != *last_name) continue;

        for (size_t last_name_idx = 0; last_name_idx < lastname_len; last_name_idx++) {
            if (*((p + i)->last_name + last_name_idx) != *(last_name + last_name_idx)) {
                found_entry = NULL;
                break;
            }
            found_entry = p + i;
            if (last_name_idx == lastname_len -1) found = 1;
        }
    }

    return found_entry;
}