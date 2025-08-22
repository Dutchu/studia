//
// Created by Bartek on 22.08.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "bit_set.h"

// Define constants for the bitmap dimensions.
#define IMAGE_ROWS 8
#define BYTES_PER_ROW 5
#define TOTAL_BYTES (IMAGE_ROWS * BYTES_PER_ROW)
#define MAX_FILENAME_LEN 51 // 50 characters + null terminator

/**
 * @brief Main function to read, display, and save a monochrome bitmap.
 *
 * The program dynamically allocates memory for the image data and filename,
 * reads hexadecimal values from the user, and then renders the image to
 * the console and a text file using a union to access individual bits.
 *
 * @return An integer exit code (0 for success, non-zero for errors).
 */
int main() {
    // Dynamically allocate memory for the bitmap data.
    unsigned char *bmp_data = (unsigned char *)malloc(TOTAL_BYTES);
    if (bmp_data == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    // Dynamically allocate memory for the filename.
    char *filename = (char *)malloc(MAX_FILENAME_LEN);
    if (filename == NULL) {
        printf("Failed to allocate memory\n");
        free(bmp_data); // Clean up previously allocated memory.
        return 8;
    }

    // Read the 40 hexadecimal values for the bitmap.
    printf("Enter values: ");
    for (int i = 0; i < TOTAL_BYTES; ++i) {
        // "%hhx" reads an unsigned char from a hexadecimal string.
        if (scanf("%hhx", bmp_data + i) != 1) {
            printf("Incorrect input\n");
            free(bmp_data);
            free(filename);
            return 1;
        }
    }

    // Read the output filename from the user.
    printf("Podaj nazwe pliku: ");
    if (scanf("%50s", filename) != 1) {
        printf("Incorrect input\n");
        free(bmp_data);
        free(filename);
        return 1;
    }

    // Open the specified file for writing.
    FILE *output_file = fopen(filename, "w");

    union bit_set converter;

    // Iterate through each row and each byte of the bitmap data.
    for (int row = 0; row < IMAGE_ROWS; ++row) {
        for (int byte_index = 0; byte_index < BYTES_PER_ROW; ++byte_index) {
            // Get the current byte from the input data.
            converter.byte_value = *(bmp_data + row * BYTES_PER_ROW + byte_index);

            // Access bits from Most Significant (bit7) to Least Significant (bit0).
            char pixels[8];
            *(pixels + 0) = converter.bits.bit7 ? '#' : ' ';
            *(pixels + 1) = converter.bits.bit6 ? '#' : ' ';
            *(pixels + 2) = converter.bits.bit5 ? '#' : ' ';
            *(pixels + 3) = converter.bits.bit4 ? '#' : ' ';
            *(pixels + 4) = converter.bits.bit3 ? '#' : ' ';
            *(pixels + 5) = converter.bits.bit2 ? '#' : ' ';
            *(pixels + 6) = converter.bits.bit1 ? '#' : ' ';
            *(pixels + 7) = converter.bits.bit0 ? '#' : ' ';

            // Print and write the 8 pixels for the current byte.
            for(int i = 0; i < 8; ++i) {
                printf("%c", *(pixels + i));
                if (output_file != NULL) {
                    fputc(*(pixels + i), output_file);
                }
            }
        }
        // After each row, print and write a newline character.
        printf("\n");
        if (output_file != NULL) {
            fputc('\n', output_file);
        }
    }

    // Check if the file was created successfully.
    if (output_file == NULL) {
        printf("Couldn't create file\n");
        free(bmp_data);
        free(filename);
        return 5;
    }

    // Close the file and inform the user of success.
    fclose(output_file);
    printf("File saved\n");

    // Free all dynamically allocated memory before exiting.
    free(bmp_data);
    free(filename);

    return 0;
}