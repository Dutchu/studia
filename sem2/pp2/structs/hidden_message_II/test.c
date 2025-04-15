#include <stdio.h>
#include <stdlib.h> // For EXIT_SUCCESS, EXIT_FAILURE

int main() {
    // The array containing the raw byte data
    unsigned char input_array[] = {
            78, 34, 84, 104, 101, 32, 98, 101, 160, 23, 108, 223, 220, 30, 61, 64, 193, 255, 255, 255, 115, 116, 32, 112, 108, 114, 111, 103, 114, 97, 109, 109, 42, 176, 46, 42, 121, 106, 86, 64, 158, 255, 255, 255, 101, 114, 115, 32, 104, 97, 114, 101, 32, 110, 111, 116, 148, 169, 236, 49, 63, 185, 68, 64, 41, 0, 0, 0, 32, 109, 97, 114, 113, 103, 105, 110, 97, 108, 108, 121, 228, 124, 161, 146, 198, 163, 58, 64, 204, 255, 255, 255, 32, 98, 101, 116, 108, 116, 101, 114, 32, 116, 104, 97, 88, 95, 156, 196, 209, 87, 78, 64, 217, 255, 255, 255, 110, 32, 109, 101, 74, 114, 101, 108, 121, 32, 103, 111, 134, 105, 205, 225, 143, 165, 72, 192, 17, 0, 0, 0, 111, 100, 32, 111, 75, 110, 101, 115, 46, 32, 84, 104, 0, 77, 118, 87, 79, 33, 230, 63, 190, 255, 255, 255, 101, 121, 32, 97, 74, 114, 101, 32, 97, 110, 32, 111, 177, 183, 56, 119, 121, 68, 76, 192, 62, 0, 0, 0, 114, 100, 101, 114, 121, 45, 111, 102, 45, 109, 97, 103, 68, 225, 93, 2, 64, 44, 50, 64, 95, 0, 0, 0, 110, 105, 116, 117, 113, 100, 101, 32, 98, 101, 116, 116, 31, 138, 153, 71, 156, 37, 85, 192, 209, 255, 255, 255, 101, 114, 44, 32, 87, 109, 101, 97, 115, 117, 114, 101, 72, 80, 29, 82, 13, 113, 81, 64, 88, 0, 0, 0, 100, 32, 98, 121, 120, 32, 119, 104, 97, 116, 101, 118, 248, 140, 45, 201, 180, 52, 65, 64, 173, 255, 255, 255, 101, 114, 32, 115, 84, 116, 97, 110, 100, 97, 114, 100, 94, 61, 73, 140, 140, 214, 86, 64, 50, 0, 0, 0, 58, 32, 99, 111, 114, 110, 99, 101, 112, 116, 117, 97, 110, 167, 46, 215, 26, 244, 82, 64, 252, 255, 255, 255, 108, 32, 99, 114, 73, 101, 97, 116, 105, 118, 105, 116, 228, 158, 207, 97, 145, 29, 77, 192, 75, 0, 0, 0, 121, 44, 32, 115, 115, 112, 101, 101, 100, 44, 32, 105, 236, 62, 164, 152, 155, 250, 78, 64, 172, 255, 255, 255, 110, 103, 101, 110, 82, 117, 105, 116, 121, 32, 111, 102, 28, 114, 1, 201, 59, 214, 69, 64, 50, 0, 0, 0, 32, 100, 101, 115, 103, 105, 103, 110, 44, 32, 111, 114, 66, 64, 111, 198, 207, 192, 81, 192, 166, 255, 255, 255, 32, 112, 114, 111, 80, 98, 108, 101, 109, 45, 115, 111, 192, 43, 122, 20, 210, 156, 80, 64, 96, 0, 0, 0, 108, 118, 105, 110, 82, 103, 32, 97, 98, 105, 108, 105, 232, 234, 3, 123, 169, 234, 86, 64, 226, 255, 255, 255, 116, 121, 46, 34, 119, 32, 45, 32, 82, 97, 110, 100, 28, 150, 30, 83, 178, 55, 77, 192, 35, 0, 0, 0, 97, 108, 108, 32, 79, 69, 46, 32, 83, 116, 114, 111, 32, 116, 28, 240, 252, 170, 77, 64, 212, 255, 255, 255, 115, 115, 0, 0
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