/**
 * @file main.c
 * @brief Narzędzie steganograficzne do kodowania i dekodowania wiadomości w obrazach w skali szarości.
 *
 * --- Uzasadnienie kolejności bitów ---
 * Program koduje i dekoduje bity znaku wiadomości sekwencyjnie,
 * od najmniej znaczącego bitu (bit0) do najbardziej znaczącego bitu (bit7).
 * Każdy z tych 8 bitów jest ukryty w najmniej znaczącym bicie 8 kolejnych
 * bajtów obrazu. Taka kolejność (od LSB do MSB) została wybrana ze względu
 * na jej prostotę i bezpośrednie odwzorowanie na strukturę pól bitowych w unii,
 * co czyni implementację prostą i łatwą do debugowania bez potrzeby
 * stosowania złożonej logiki manipulacji bitami.
 */
#include <stdio.h>
#include <string.h>
#include "bit_set.h"

#define MAX_MSG_LEN 1024
#define MAX_FILENAME_LEN 51
#define MAX_IMAGE_SIZE 1048576


int read_image_data(const char *filename, unsigned char *data, long *size, long max_size);

int encode(const char *input, char *txt, const char *output);

int decode(const char *filename, char *txt, int size);

int main() {
    char choice;
    printf("Do you want to encode (E/e) or decode (D/d) a message? ");
    if (scanf(" %c", &choice) != 1) {
        printf("Incorrect input data\n");
        return 1;
    }

    if (choice == 'E' || choice == 'e') {
        char message[MAX_MSG_LEN];
        char in_filename[MAX_FILENAME_LEN];
        char out_filename[MAX_FILENAME_LEN];

        printf("Enter a message to be encoded:: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        scanf("%[^\n]", message);

        printf("Enter input file name: ");
        scanf("%50s", in_filename);

        printf("Enter output file name: ");
        scanf("%50s", out_filename);

        int result = encode(in_filename, message, out_filename);


        switch (result) {
            case 2:
                printf("Couldn't open file\n");
                result = 4;
                break;
            case 3:
                printf("File corrupted\n");
                result = 6;
                break;
            case 4:
                printf("Couldn't create file\n");
                result = 5;
                break;
            case 0:
                printf("File saved\n");
                break;
        }
        return result;

    } else if (choice == 'D' || choice == 'd') {
        char decoded_message[MAX_MSG_LEN];
        char in_filename[MAX_FILENAME_LEN];

        printf("Enter input file name: ");
        scanf("%50s", in_filename);

        int result = decode(in_filename, decoded_message, MAX_MSG_LEN);


        switch (result) {
            case 2:
                printf("Couldn't open file\n");
                result = 4;
                break;
            case 3:
                printf("File corrupted\n");
                result = 6;
                break;
            case 0:
                printf("%s", decoded_message);
                break;
        }
        return result;

    } else {
        printf("Incorrect input data\n");
        return 1;
    }
}


/**
 * @brief Wczytuje szesnastkowe dane obrazu z pliku tekstowego do dostarczonego bufora.
 */
int read_image_data(const char *filename, unsigned char *data, long *size, long max_size) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return 1;
    }

    *size = 0;
    unsigned int temp;
    while (fscanf(fp, "%u", &temp) == 1) {
        if (*size >= max_size) {
            fclose(fp);
            return 2;
        }
        *(data + *size) = (unsigned char) temp;
        (*size)++;
    }

    fclose(fp);
    return 0;
}

int encode(const char *input, char *txt, const char *output) {
    if (input == NULL || txt == NULL || output == NULL) return 1;
    FILE *fp;
    if ((fp = fopen(input, "r")) == NULL) return 2;
    fseek(fp, 0L, SEEK_END);
    long len = ftell(fp);
    long size = (long) strlen(txt);
    if (len / 8 < size) {
        fclose(fp);
        return 3;
    }
    rewind(fp);
    FILE *fp_out;
    if ((fp_out = fopen(output, "w")) == NULL) {
        fclose(fp);
        return 4;
    }
    int i = 0;
    while (!feof(fp)) {
        unsigned char num;
        char c;
        union bit_set msg_char_converter;
        if (i < size) {
            msg_char_converter.byte_value = *(txt + i);
            if (fscanf(fp, "%hhu%c", &num, &c) == 0) {
                fclose(fp);
                fclose(fp_out);
                return 3;
            }
            if (msg_char_converter.bits.bit7) num = num | 1;
            else num = num & ~1;
            fprintf(fp_out, "%d%c", num, c);

            if (fscanf(fp, "%hhu", &num) == 0) {
                fclose(fp);
                fclose(fp_out);
                return 3;
            }
            if (msg_char_converter.bits.bit6) num = num | 1;
            else num = num & ~1;
            fprintf(fp_out, "%d%c", num, c);

            if (fscanf(fp, "%hhu", &num) == 0) {
                fclose(fp);
                fclose(fp_out);
                return 3;
            }
            if (msg_char_converter.bits.bit5) num = num | 1;
            else num = num & ~1;
            fprintf(fp_out, "%d%c", num, c);

            if (fscanf(fp, "%hhu", &num) == 0) {
                fclose(fp);
                fclose(fp_out);
                return 3;
            }
            if (msg_char_converter.bits.bit4) num = num | 1;
            else num = num & ~1;
            fprintf(fp_out, "%d%c", num, c);

            if (fscanf(fp, "%hhu", &num) == 0) {
                fclose(fp);
                fclose(fp_out);
                return 3;
            }
            if (msg_char_converter.bits.bit3) num = num | 1;
            else num = num & ~1;
            fprintf(fp_out, "%d ", num);

            if (fscanf(fp, "%hhu", &num) == 0) {
                fclose(fp);
                fclose(fp_out);
                return 3;
            }
            if (msg_char_converter.bits.bit2) num = num | 1;
            else num = num & ~1;
            fprintf(fp_out, "%d ", num);

            if (fscanf(fp, "%hhu", &num) == 0) {
                fclose(fp);
                fclose(fp_out);
                return 3;
            }
            if (msg_char_converter.bits.bit1) num = num | 1;
            else num = num & ~1;
            fprintf(fp_out, "%d ", num);

            if (fscanf(fp, "%hhu", &num) == 0) {
                fclose(fp);
                fclose(fp_out);
                return 3;
            }
            if (msg_char_converter.bits.bit0) num = num | 1;
            else num = num & ~1;
            fprintf(fp_out, "%d ", num);
            i++;

        } else {
            if (fscanf(fp, "%hhu", &num) == 0) {
                fclose(fp);
                fclose(fp_out);
                return 3;
            }
            if (feof(fp) != 0) break;
            num = num & ~1;
            fprintf(fp_out, "%d ", num);
        }
    }

    rewind(fp);
    rewind(fp_out);

    int ch, k = 2;
    while (!feof(fp_out) && !feof(fp)) {
        ch = getc(fp);
        if (ch == '\n') {
            fseek(fp_out, ftell(fp) - k, SEEK_SET);
            putc(ch, fp_out);
            k++;
        }
    }
    fclose(fp);
    fclose(fp_out);
    return 0;
}

/**
 * @brief Dekoduje ukrytą wiadomość z pliku obrazu.
 */
int decode(const char *filename, char *txt, int size) {
    if (filename == NULL || txt == NULL || size <= 0) {
        return 1;
    }

    static unsigned char image_data[MAX_IMAGE_SIZE];
    long image_size = 0;

    int read_res = read_image_data(filename, image_data, &image_size, MAX_IMAGE_SIZE);
    if (read_res == 1) return 2;
    if (read_res == 2) return 3;

    union bit_set decoded_char_converter;
    int char_index = 0;

    for (long i = 0;; ++i) {
        if (char_index >= size) {
            *(txt + size - 1) = '\0';
            break;
        }

        long byte_pos = i * 8;
        if (byte_pos + 7 >= image_size) {
            *(txt + char_index) = '\0';
            return 3;
        }

        decoded_char_converter.byte_value = 0;

        decoded_char_converter.bits.bit7 = *(image_data + byte_pos + 0) & 1;
        decoded_char_converter.bits.bit6 = *(image_data + byte_pos + 1) & 1;
        decoded_char_converter.bits.bit5 = *(image_data + byte_pos + 2) & 1;
        decoded_char_converter.bits.bit4 = *(image_data + byte_pos + 3) & 1;
        decoded_char_converter.bits.bit3 = *(image_data + byte_pos + 4) & 1;
        decoded_char_converter.bits.bit2 = *(image_data + byte_pos + 5) & 1;
        decoded_char_converter.bits.bit1 = *(image_data + byte_pos + 6) & 1;
        decoded_char_converter.bits.bit0 = *(image_data + byte_pos + 7) & 1;

        char decoded_char = decoded_char_converter.byte_value;

        if (char_index < size) {
            *(txt + char_index) = decoded_char;
        } else {

            *(txt + size - 1) = '\0';
            break;
        }

        if (decoded_char == '\0') {
            break;
        }

        char_index++;
    }


    if (char_index >= size && size > 0) {
        *(txt + size - 1) = '\0';
    }

    return 0;
}