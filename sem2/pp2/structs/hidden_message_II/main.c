
#include "string.h"
#include "stdio.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include "struct_utils.h"

#define MESS_BUFF_SIZE 4096
#define N_STRUCT_IN_BUFF 10
#define STRUCT_SIZE 24
#define FILENAME_BUFF_SIZE 10
#define CRYPTO_BUFF_SIZE (N_STRUCT_IN_BUFF * STRUCT_SIZE)
#define FORBIDDEN_SPACE_SIZE (STRUCT_SIZE - (1 + 8 + 4))
#define DEC_MESSAGE_BUFF_SIZE ((STRUCT_SIZE - FORBIDDEN_SPACE_SIZE) * N_STRUCT_IN_BUFF)

void encode(char *message, struct message_t *cryptogram, unsigned int no_elements);
int decode_message(const struct message_t *cp, int size, char *msg, int text_size);
int load_data(struct message_t *cp, int size, const char *filename);
int load_message(FILE *fp, char *mess_buff, int buff_size);


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

    decode_message(cryptogram_buff, CRYPTO_BUFF_SIZE, decrypt_message, DEC_MESSAGE_BUFF_SIZE);

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
    unsigned int a_size = sizeof ((cp + 1)->a);
    unsigned int b_size = sizeof ((cp + 1)->b);
    unsigned int c_size = sizeof ((cp + 1)->c);
    unsigned int a_offset = offsetof(struct message_t, a);
    unsigned int b_offset = offsetof(struct message_t, b);
    unsigned int c_offset = offsetof(struct message_t, c);
    int j = 0;
    for(unsigned int i = 0; i < size; i++) {
        //skip addresses of first field in struct
        if (i % 24 == a_offset) {
            i = i + a_size;
        }
        //skip addresses of second field in struct
        if (i % 24 == b_offset)  {
            i = i + b_size;
        }
        //skip addresses of third field in struct
        if (i % 24 == c_offset) {
            i = i + c_size;
        }

        char *raw_mem = (char *)cp + i;
        *(msg + j) = *raw_mem;
        printf("%c", *(msg + j));

        j++;
    }
    return 0;
}

void generate_bin(char *message_buff) {
    char *filename = "message1.txt";
//    char message[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'f', 'i', 'j', 'k', 'l', 'm'};
    struct message_t example;
    FILE *fp;

    fp = fopen("test.bin", "w+");

    FILE *mfp = fopen(filename, "r");
    load_message(mfp, message_buff, MESS_BUFF_SIZE);
    fclose(mfp);

    size_t text_size = strlen(message_buff);
    //noste - number of structs to encode
    //calculate reminding free space between struct members and only then you can have number of structs needed.
    size_t noste = text_size / (STRUCT_SIZE - FORBIDDEN_SPACE_SIZE);
    if (text_size % (STRUCT_SIZE - FORBIDDEN_SPACE_SIZE) != 0) {
        noste = noste + 1;
    }
    struct message_t crypto[noste];
    example.a = 'x';
    example.b = 99.9;
    example.c = 9;
    for (int i = 0; i < noste; i++) {
        (crypto + i)->a = example.a;
        (crypto + i)->b = example.b;
        (crypto + i)->c = example.c;
    }

    printf("\nNOSTE: %zu\n", noste);
    printf("\ntext length: %zu\n", text_size);
    printf("\nTXT LN / STR SIZE: %f\n", (text_size / (double) STRUCT_SIZE) );

    encode(message_buff, crypto, noste);
    fwrite(crypto, sizeof(struct message_t), noste, fp);

    fclose(fp);
}

void encode(char *message, struct message_t *cryptogram, unsigned int no_elements) {
    //char - 1
    //int - 4
    //double - 8
//    printf("double no_elements: %lu\n", sizeof(double));
    unsigned int struct_size = sizeof(struct message_t);
    unsigned int a_size = sizeof ((cryptogram + 1)->a);
    unsigned int b_size = sizeof ((cryptogram + 1)->b);
    unsigned int c_size = sizeof ((cryptogram + 1)->c);
    unsigned int a_offset = offsetof(struct message_t, a);
    unsigned int b_offset = offsetof(struct message_t, b);
    unsigned int c_offset = offsetof(struct message_t, c);

    printf("offsetof: %u\n", a_offset);



    int j = 0;
    for(unsigned int i = 0; i < struct_size * no_elements; i++) {
//        printf("i: %u, Address begin: %p\t", i, cryptogram + i);

        //skip addresses of first field in struct
        if (i % 24 == a_offset) {
            i = i + a_size;
//            printf("Address empty after a: %p\t", cryptogram + i);
        }
        //skip addresses of second field in struct
        if (i % 24 == b_offset)  {
            i = i + b_size;
//            printf("Address empty after b: %p\t", cryptogram + i);
        }
        //skip addresses of third field in struct
        if (i % 24 == c_offset) {
            i = i + c_size;
//            printf("Address empty after c: %p\t", cryptogram + i);
        }

        char *raw_mem = (char *)cryptogram + i;
        *raw_mem = *(message + j);
        printf("i[%d] j[%d] Writing to memory %p [%ld] - %c", i, j, raw_mem, (long) raw_mem, *(message + j));

        printf("\n");
        j++;
    }
}

int load_message(FILE *fp, char *mess_buff, int buff_size) {
    size_t ret = fread(mess_buff, sizeof(char), buff_size, fp);
    if (ret < 1) {
        fprintf(stderr, "fread() failed: %zu\n", ret);
        exit(EXIT_FAILURE);
    }
    return 0;
}

void list_directory_contents(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        printf("%s\n", entry->d_name);
    }

    closedir(dp);
}
