
#include "string.h"
#include "stdio.h"
#include <stddef.h>
#include <stdlib.h>

#define N_STRUCT_IN_BUFF 10
#define STRUCT_SIZE 24
#define FILENAME_BUFF_SIZE 10
#define CRYPTO_BUFF_SIZE (N_STRUCT_IN_BUFF * STRUCT_SIZE)
#define FORBIDDEN_SPACE_SIZE (STRUCT_SIZE - (1 + 8 + 4))
#define DEC_MESSAGE_BUFF_SIZE ((STRUCT_SIZE - FORBIDDEN_SPACE_SIZE) * N_STRUCT_IN_BUFF)

struct message_t
{
    char a;
    double b;
    int c;
};

int decode_message(const struct message_t *cp, int size, char *msg, int text_size);
int load_data(struct message_t *cp, int size, const char *filename);

int main() {

    char filename_buff[FILENAME_BUFF_SIZE];
    int res = 0;

    printf("Enter file name:");
    if (!fgets(filename_buff, FILENAME_BUFF_SIZE, stdin)) {
        return 1;
    }
    *(filename_buff + strcspn(filename_buff, "\n")) = 0;
//    strcat(filename_buff, "test.bin");

    struct message_t cryptogram_buff[CRYPTO_BUFF_SIZE];
    char decrypt_message[DEC_MESSAGE_BUFF_SIZE];

    res = load_data(cryptogram_buff, STRUCT_SIZE * N_STRUCT_IN_BUFF, filename_buff);
    if (res < 0) exit(4);

    decode_message(cryptogram_buff, N_STRUCT_IN_BUFF, decrypt_message, DEC_MESSAGE_BUFF_SIZE);

    return 0;
}

int load_data(struct message_t *cp, int size, const char *filename) {
    if (cp == NULL || filename == NULL) return -1;
    if (size < 0) return -1;

    FILE *f;
    f = fopen(filename, "r");
    if (f == NULL) return -2;

    int res = fread(cp, STRUCT_SIZE * N_STRUCT_IN_BUFF, N_STRUCT_IN_BUFF, f);
    fclose(f);

    return res;
}

int decode_message(const struct message_t *cp, int size, char *msg, int text_size) {

    if (cp == NULL) {
        fprintf(stderr, "Vector is NULL\n");
        return 1;
    }

    if (size < 1) {
        fprintf(stderr, "Vector size is negative or 0\n");
        return 1;
    }

    int a_size = sizeof ((cp + 1)->a);
    int b_size = sizeof ((cp + 1)->b);
    int c_size = sizeof ((cp + 1)->c);
    int a_offset = offsetof(struct message_t, a);
    int b_offset = offsetof(struct message_t, b);
    int c_offset = offsetof(struct message_t, c);

    for(int i = 0; i < size; i++) {
        for (int j = a_offset + a_size; j < b_offset; j++) {
            printf("%c", *((char *)(cp + i) + j) );
        }
        for (int j = b_offset + b_size; j < c_offset; j++) {
            printf("%c", *((char *)(cp + i) + j) );
        }
        for (int j = c_offset + c_size; j < STRUCT_SIZE; j++) {
            printf("%c", *((char *)(cp + i) + j) );
        }
    }
    return 0;
}