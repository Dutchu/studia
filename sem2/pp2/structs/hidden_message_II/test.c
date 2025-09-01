//
// Created by Bartek on 14.04.2025.
//
#include <stdio.h>
#include <stdlib.h> // For EXIT_SUCCESS, EXIT_FAILURE

int main() {
    // The array containing the raw byte data
    unsigned char input_array[] = {
            85, 73, 109, 112, 101, 114, 102, 101, 18, 120, 125, 8, 198, 62, 82, 64, 251, 255, 255, 255, 99, 116, 105, 111, 104, 110, 32, 105, 115, 32, 98, 101, 232, 98, 174, 249, 252, 164, 67, 192, 254, 255, 255, 255, 97, 117, 116, 121, 103, 44, 32, 109, 97, 100, 110, 101, 0, 58, 138, 185, 34, 238, 82, 64, 207, 255, 255, 255, 115, 115, 32, 105, 82, 115, 32, 103, 101, 110, 105, 117, 26, 123, 3, 135, 39, 87, 85, 192, 24, 0, 0, 0, 115, 32, 97, 110, 116, 100, 32, 105, 116, 39, 115, 32, 154, 215, 218, 195, 60, 187, 84, 64, 240, 255, 255, 255, 98, 101, 116, 116, 84, 101, 114, 32, 116, 111, 32, 98, 215, 60, 45, 247, 88, 67, 87, 192, 13, 0, 0, 0, 101, 32, 97, 98, 66, 115, 111, 108, 117, 116, 101, 108, 229, 64, 53, 58, 80, 26, 67, 192, 194, 255, 255, 255, 121, 32, 114, 105, 84, 100, 105, 99, 117, 108, 111, 117, 106, 118, 141, 51, 164, 98, 80, 64, 231, 255, 255, 255, 115, 32, 116, 104, 65, 97, 110, 32, 97, 98, 115, 111, 96, 201, 23, 6, 158, 205, 26, 192, 160, 255, 255, 255, 108, 117, 116, 101, 102, 108, 121, 32, 98, 111, 114, 105, 94, 61, 250, 51, 162, 36, 87, 64, 51, 0, 0, 0, 110, 103, 46, 32, 74, 45, 32, 77, 97, 114, 105, 108, 26, 169, 168, 253, 116, 43, 86, 64, 214, 255, 255, 255, 121, 110, 32, 77, 90, 111, 110, 114, 111, 101, 0, 0, 172, 250, 85, 67, 95, 6, 57, 64, 175, 255, 255, 255, 0, 0, 0, 0
    };

    // Calculate the total number of bytes in the array
    // sizeof on an array gives its total size in bytes
    size_t array_size = sizeof(input_array);

    // Define the name for the output binary file
    const char *filename = "C:\\Users\\Bartek\\work\\studia\\sem2\\pp2\\structs\\hidden_message_II\\cmake-build-debug\\t11.bin";

    // Open the file for writing in binary mode ("wb")
    // 'w' = write, 'b' = binary mode (crucial to prevent text translations)
    FILE *outfile = fopen(filename, "wb");

    // Check if the file could be opened
    if (outfile == NULL) {
        perror("Error opening file for writing"); // Print system error description
        return EXIT_FAILURE; // Indicate failure
    }

    // Write the entire array content to the file
    // fwrite(pointer_to_data, size_of_each_element, number_of_elements, file_stream)
    // sizeof(unsigned char) is guaranteed to be 1
    size_t bytes_written = fwrite(input_array, sizeof(unsigned char), array_size, outfile);

    // Check if the number of bytes written matches the array size
    if (bytes_written != array_size) {
        fprintf(stderr, "Error writing to file: tried to write %zu bytes, but wrote %zu bytes.\n",
                array_size, bytes_written);
        fclose(outfile); // Close the file even if write failed
        return EXIT_FAILURE; // Indicate failure
    }

    // Close the file
    if (fclose(outfile) != 0) {
        perror("Error closing file");
        // Data might be partially written, but the close failed
        return EXIT_FAILURE;
    }

    printf("Successfully wrote %zu bytes to %s\n", array_size, filename);

    return EXIT_SUCCESS; // Indicate success
}