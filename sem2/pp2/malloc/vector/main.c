//
// Created by Bartek on 17.08.2025.
//

#include "vector.h"
#include <stdio.h>

#define SIZE 8

int main() {
    // A pointer to the vector structure is used, as required.
    // Direct declaration of 'struct vector_t' is not allowed.
    struct vector_t *vec = NULL;
    int capacity;

    // Prompt the user for the initial capacity of the vector.
    printf("Podaj pojemność tablicy: ");
    if (scanf("%d", &capacity) != 1) {
        // Handle non-integer input.
        printf("Incorrect input\n");
        return 1;
    }

    // The initial capacity must be a positive integer.
    if (capacity <= 0) {
        printf("Incorrect input data\n");
        return 2;
    }

    // Attempt to create the vector structure and allocate memory for its data.
    int create_result = vector_create_struct(&vec, capacity);
    if (create_result != 0) {
        if (create_result == 1) {
            // This case should not be triggered if capacity > 0, but is here for completeness.
            printf("Incorrect input data\n");
            return 2;
        }
        if (create_result == 2) {
            // Handle memory allocation failure.
            printf("Failed to allocate memory\n");
            return 8;
        }
    }

    int choice;
    // Main interactive loop for vector operations.
    while (1) {
        printf("Co chcesz zrobic: ");
        if (scanf("%d", &choice) != 1) {
            // Handle non-integer input for the menu choice.
            printf("Incorrect input\n");
            vector_destroy_struct(&vec); // Clean up memory before exiting.
            return 1;
        }

        // Process the user's choice.
        if (choice == 0) {
            // Option 0: Exit the program.
            break;
        } else if (choice == 1) {
            // Option 1: Add elements to the vector.
            printf("Podaj kolejne liczby, które mają zostać dodane do tablicy: ");
            int value_to_add;
            while (1) {
                if (scanf("%d", &value_to_add) != 1) {
                    printf("Incorrect input\n");
                    vector_destroy_struct(&vec); // Clean up memory.
                    return 1;
                }
                // Stop reading when the user enters 0.
                if (value_to_add == 0) {
                    break;
                }
                // Add the value to the vector.
                if (vector_push_back(vec, value_to_add) == 2) {
                    printf("Failed to allocate memory\n");
                    break; // Stop adding if reallocation fails.
                }
            }
        } else if (choice == 2) {
            // Option 2: Remove elements from the vector.
            printf("Podaj kolejne liczby, które mają zostać usuniete z tablicy: ");
            int value_to_remove;
            while (1) {
                if (scanf("%d", &value_to_remove) != 1) {
                    printf("Incorrect input\n");
                    vector_destroy_struct(&vec); // Clean up memory.
                    return 1;
                }
                // Stop reading when the user enters 0.
                if (value_to_remove == 0) {
                    break;
                }
                // Remove all occurrences of the value.
                vector_erase(vec, value_to_remove);
            }
        } else {
            // Handle invalid menu options.
            printf("Incorrect input data\n");
            continue; // Skip the display part and re-prompt.
        }

        // After an add or remove operation, display the vector's state.
        if (vec == NULL || vec->size == 0) {
            printf("Buffer is empty\n");
        } else {
            vector_display(vec);
        }
    }

    // Free all allocated memory before exiting.
    vector_destroy_struct(&vec);
    return 0;

    return 0;
}