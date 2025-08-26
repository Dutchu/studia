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
#include <stdlib.h>
#include <string.h>
#include "bit_set.h"

#define MAX_MSG_LEN 1024
#define MAX_FILENAME_LEN 51

// Prototypy funkcji
int read_image_data(const char *filename, unsigned char **data, long *size);
int encode();
int decode();

int main() {
    char choice;
    printf("Do you want to encode (E/e) or decode (D/d) a message? ");
    if (scanf(" %c", &choice) != 1) {
        printf("Incorrect input data\n");
        return 1;
    }

    if (choice == 'E' || choice == 'e') {
        return encode();
    } else if (choice == 'D' || choice == 'd') {
        return decode();
    } else {
        printf("Incorrect input data\n");
        return 1;
    }
}


/**
 * @brief Wczytuje szesnastkowe dane obrazu z pliku tekstowego do dynamicznego bufora.
 * @param filename Nazwa pliku wejściowego.
 * @param data Wskaźnik do bufora, w którym będą przechowywane dane obrazu.
 * @param size Wskaźnik do zmiennej przechowującej liczbę wczytanych bajtów.
 * @return 0 w przypadku sukcesu, 1 w przypadku błędu otwarcia pliku, 8 w przypadku błędu alokacji pamięci.
 */
int read_image_data(const char *filename, unsigned char **data, long *size) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    long estimated_bytes = file_size / 3 + 1;
    *data = (unsigned char *)malloc(estimated_bytes);
    if (*data == NULL) {
        fclose(fp);
        return 8;
    }

    *size = 0;
    unsigned int temp;
    // Podejście dwuprzebiegowe: pierwszy przebieg do zliczenia, drugi do wczytania.
    while (fscanf(fp, "%x", &temp) == 1) {
        if (*size >= estimated_bytes) {
            break;
        }
        *(*data + *size) = (unsigned char)temp;
        (*size)++;
    }

    fclose(fp);
    return 0;
}

/**
 * @brief Obsługuje proces kodowania wiadomości.
 * @return 0 w przypadku sukcesu, wartość niezerowa w przypadku błędu.
 */
int encode() {
    char *message = (char *)malloc(MAX_MSG_LEN);
    char *in_filename = (char *)malloc(MAX_FILENAME_LEN);
    char *out_filename = (char *)malloc(MAX_FILENAME_LEN);

    if (message == NULL || in_filename == NULL || out_filename == NULL) {
        printf("Failed to allocate memory\n");
        free(message); free(in_filename); free(out_filename);
        return 8;
    }

    printf("Enter a message to be encoded:: ");
    int c;
    // Pobranie znaku nowej linii pozostawionego przez poprzednie wywołanie scanf
    while ((c = getchar()) != '\n' && c != EOF);
    // Wczytanie całej linii, łącznie ze spacjami
    scanf("%[^\n]", message);

    printf("Enter input file name: ");
    scanf("%50s", in_filename);

    printf("Enter output file name: ");
    scanf("%50s", out_filename);

    unsigned char *image_data = NULL;
    long image_size = 0;
    int read_res = read_image_data(in_filename, &image_data, &image_size);
    if (read_res == 1) {
        printf("Couldn't open file\n");
        free(message); free(in_filename); free(out_filename);
        return 1;
    }
    if (read_res == 8) {
        printf("Failed to allocate memory\n");
        free(message); free(in_filename); free(out_filename);
        return 8;
    }

    long msg_len_with_null = strlen(message) + 1;
    if (image_size < msg_len_with_null * 8) {
        // Niewystarczająca ilość miejsca w obrazie
        printf("File corrupted\n");
        free(message); free(in_filename); free(out_filename); free(image_data);
        return 1;
    }

    union bit_set msg_char_converter, img_byte_converter;

    for (long i = 0; i < msg_len_with_null; ++i) {
        msg_char_converter.byte_value = *(message + i);
        unsigned char bits_to_hide[8];
        bits_to_hide[0] = msg_char_converter.bits.bit0;
        bits_to_hide[1] = msg_char_converter.bits.bit1;
        bits_to_hide[2] = msg_char_converter.bits.bit2;
        bits_to_hide[3] = msg_char_converter.bits.bit3;
        bits_to_hide[4] = msg_char_converter.bits.bit4;
        bits_to_hide[5] = msg_char_converter.bits.bit5;
        bits_to_hide[6] = msg_char_converter.bits.bit6;
        bits_to_hide[7] = msg_char_converter.bits.bit7;

        for (int j = 0; j < 8; ++j) {
            long byte_pos = i * 8 + j;
            img_byte_converter.byte_value = *(image_data + byte_pos);
            img_byte_converter.bits.bit0 = bits_to_hide[j];
            *(image_data + byte_pos) = img_byte_converter.byte_value;
        }
    }

    FILE *out_fp = fopen(out_filename, "w");
    if (out_fp == NULL) {
        printf("Couldn't create file\n");
        free(message); free(in_filename); free(out_filename); free(image_data);
        return 5;
    }

    for (long i = 0; i < image_size; ++i) {
        fprintf(out_fp, "%02x ", *(image_data + i));
    }

    fclose(out_fp);
    printf("File saved\n");

    free(message); free(in_filename); free(out_filename); free(image_data);
    return 0;
}

/**
 * @brief Obsługuje proces dekodowania wiadomości.
 * @return 0 w przypadku sukcesu, wartość niezerowa w przypadku błędu.
 */
int decode() {
    char *in_filename = (char *)malloc(MAX_FILENAME_LEN);
    if (in_filename == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Enter input file name: ");
    scanf("%50s", in_filename);

    unsigned char *image_data = NULL;
    long image_size = 0;
    int read_res = read_image_data(in_filename, &image_data, &image_size);
    if (read_res == 1) {
        printf("Couldn't open file\n");
        free(in_filename);
        return 1;
    }
    if (read_res == 8) {
        printf("Failed to allocate memory\n");
        free(in_filename);
        return 8;
    }

    union bit_set img_byte_converter, decoded_char_converter;

    for (long i = 0; ; ++i) {
        long byte_pos = i * 8;
        if (byte_pos + 7 >= image_size) {
            printf("File corrupted\n");
            free(in_filename); free(image_data);
            return 1;
        }

        img_byte_converter.byte_value = *(image_data + byte_pos + 0);
        decoded_char_converter.bits.bit0 = img_byte_converter.bits.bit0;
        img_byte_converter.byte_value = *(image_data + byte_pos + 1);
        decoded_char_converter.bits.bit1 = img_byte_converter.bits.bit0;
        img_byte_converter.byte_value = *(image_data + byte_pos + 2);
        decoded_char_converter.bits.bit2 = img_byte_converter.bits.bit0;
        img_byte_converter.byte_value = *(image_data + byte_pos + 3);
        decoded_char_converter.bits.bit3 = img_byte_converter.bits.bit0;
        img_byte_converter.byte_value = *(image_data + byte_pos + 4);
        decoded_char_converter.bits.bit4 = img_byte_converter.bits.bit0;
        img_byte_converter.byte_value = *(image_data + byte_pos + 5);
        decoded_char_converter.bits.bit5 = img_byte_converter.bits.bit0;
        img_byte_converter.byte_value = *(image_data + byte_pos + 6);
        decoded_char_converter.bits.bit6 = img_byte_converter.bits.bit0;
        img_byte_converter.byte_value = *(image_data + byte_pos + 7);
        decoded_char_converter.bits.bit7 = img_byte_converter.bits.bit0;

        if (decoded_char_converter.byte_value == '\0') {
            break;
        }
        printf("%c", decoded_char_converter.byte_value);
    }
    printf("\n");

    free(in_filename); free(image_data);
    return 0;
}
