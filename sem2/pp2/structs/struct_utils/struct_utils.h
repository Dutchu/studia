//
// Created by Bartek on 11.05.2022.
//

#ifndef STRUCT_UTILS_H
#define STRUCT_UTILS_H

#include "stdio.h"

#define FILE_NAME_BUFFER_SIZE 999
#define PROJECT_PATH "C:\\Users\\Bartek\\Desktop\\studia\\sem2\\pp2\\structs\\hidden_message_II\\file"
#define FILES_NUMBER 5

#define FILE_PATH "C:\\Users\\Bartek\\Desktop\\studia\\sem2\\pp2\\structs\\file_struct\\file.txt"

struct file_t {
    FILE *f;
    int size;
};

struct message_t
{
    char a;
    double b;
    int c;
};

int open_file(struct file_t *f, const char *filename);
struct file_t *find_min(const struct file_t *files, int size);
void close_file(struct file_t *f);
void print(struct file_t *files, int size);
int build_path(char *file_path, int number);
int take_input(char *input);
void print_string_array(char **array, int size);
int check_file_name(FILE *fp);
int get_file_size(FILE *f_handle);
int decode_message(const struct message_t *cp, int size, char *msg, int text_size);
int load_data(struct message_t *cp, int size, const char *filename);
#endif //STRUCT_UTILS_H
