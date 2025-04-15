
#include "string.h"
#include "stdio.h"
#include <stddef.h>
#include <stdlib.h>

#define N_STRUCT_IN_BUFF 100
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

    int res;

    char filename_buff[FILENAME_BUFF_SIZE];
    struct message_t cryptogram_buff[CRYPTO_BUFF_SIZE];
    char decrypt_message[DEC_MESSAGE_BUFF_SIZE];

    printf("Enter file name:");
    if (!fgets(filename_buff, FILENAME_BUFF_SIZE, stdin)) {
        return 1;
    }
    *(filename_buff + strcspn(filename_buff, "\n")) = 0;

    res = load_data(cryptogram_buff, CRYPTO_BUFF_SIZE, filename_buff);
    printf("load_data result: %d\n", res);
    if (res < 0) exit(4);

    decode_message(cryptogram_buff, N_STRUCT_IN_BUFF, decrypt_message, DEC_MESSAGE_BUFF_SIZE);
    printf("%s", decrypt_message);

    return 0;
 }

int load_data(struct message_t *cp, int size, const char *filename) {
    if (cp == NULL || filename == NULL) return -1;
    if (size < 0) return -1;

    FILE *f;
    f = fopen(filename, "rb");
    if (f == NULL) return -2;

    size_t items_read = fread(cp, sizeof(struct message_t), (size_t)size, f);

    if (items_read < (size_t)size && ferror(f)) {
        fclose(f);
        return -3;
    }

    fclose(f);

    return (int)items_read;
}

int decode_message(const struct message_t *cp, int size, char *msg, int text_size) {
    if (cp == NULL) {
        return 1;
    }
    if (size < 1) {
        return 1;
    }
    if (msg == NULL) {
        return 1;
    }

//    Result of operation is garbage or undefined 8
//←
//The left operand of '!=' is a garbage value
    if (*msg != '\0') {
        *msg = '\0';
    }

    if (text_size < 1) {
        return 1;
    }

    int a_size = sizeof ((cp + 1)->a);
    int b_size = sizeof ((cp + 1)->b);
    int c_size = sizeof ((cp + 1)->c);
    int a_offset = offsetof(struct message_t, a);
    int b_offset = offsetof(struct message_t, b);
    int c_offset = offsetof(struct message_t, c);

    size_t current_len = 0;
    size_t remaining_space = text_size - current_len;

    char dec_char;
    for(int i = 0; i < size; i++) {
        for (int j = a_offset + a_size; j < b_offset; j++) {
            dec_char = *((char *)(cp + i) + j);

            snprintf(msg + current_len, remaining_space, "%c", dec_char);
            current_len = current_len + sizeof(char);
            remaining_space = text_size - current_len;
        }
        for (int j = b_offset + b_size; j < c_offset; j++) {
            dec_char = *((char *)(cp + i) + j);

            snprintf(msg + current_len, remaining_space, "%c", dec_char);
            current_len = current_len + sizeof(char);
            remaining_space = text_size - current_len;
        }
        for (int j = c_offset + c_size; j < STRUCT_SIZE; j++) {
            dec_char = *((char *)(cp + i) + j);

            snprintf(msg + current_len, remaining_space, "%c", dec_char);
            current_len = current_len + sizeof(char);
            remaining_space = text_size - current_len;
        }
    }
    return 0;
}