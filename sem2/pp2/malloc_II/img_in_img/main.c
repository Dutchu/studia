//
// Created by Bartek on 28.08.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_utils.h"

char* create_modified_filename(const char* original_name) {
    const char* suffix = "_modified";
    char* dot = strrchr(original_name, '.');
    char* new_name;
    if (dot == NULL) {
        new_name = malloc(strlen(original_name) + strlen(suffix) + 1);
        if (new_name == NULL) return NULL;
        strcpy(new_name, original_name);
        strcat(new_name, suffix);
    } else {
        int base_len = dot - original_name;
        new_name = malloc(base_len + strlen(suffix) + strlen(dot) + 1);
        if (new_name == NULL) return NULL;
        strncpy(new_name, original_name, base_len);
        *(new_name + base_len) = '\0';
        strcat(new_name, suffix);
        strcat(new_name, dot);
    }
    return new_name;
}


int main(void) {
    char *dest_filename_buffer = (char*)malloc(40 * sizeof(char));
    if (dest_filename_buffer == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Enter destination image file name: ");
    scanf("%39s", dest_filename_buffer);

    int err_code;
    struct image_t *dest_img = load_image_t(dest_filename_buffer, &err_code);

    if (dest_img == NULL) {
        free(dest_filename_buffer);
        if (err_code == 2) { printf("Couldn't open file\n"); return 4; }
        if (err_code == 3) { printf("File corrupted\n"); return 6; }
        if (err_code == 4) { printf("Failed to allocate memory\n"); return 8; }
        return 1;
    }

    int num_subimages;
    printf("How many subimages you want to draw: ");
    if (scanf("%d", &num_subimages) != 1) {
        printf("Incorrect input\n");
        free(dest_filename_buffer);
        destroy_image(&dest_img);
        return 1;
    }
    if (num_subimages < 1) {
        printf("Incorrect input data\n");
        free(dest_filename_buffer);
        destroy_image(&dest_img);
        return 2;
    }

    for (int i = 0; i < num_subimages; ++i) {
        char *sub_filename_buffer = (char*)malloc(40 * sizeof(char));
        if (sub_filename_buffer == NULL) {
            printf("Failed to allocate memory\n");
            free(dest_filename_buffer);
            destroy_image(&dest_img);
            return 8;
        }

        printf("Enter a name of a subimage: ");
        scanf("%39s", sub_filename_buffer);

        struct image_t *sub_img = load_image_t(sub_filename_buffer, &err_code);
        free(sub_filename_buffer);

        if (sub_img == NULL) {
            if (err_code == 2) printf("Couldn't open file\n");
            else if (err_code == 3) printf("File corrupted\n");
            else if (err_code == 4) {
                printf("Failed to allocate memory\n");
                free(dest_filename_buffer);
                destroy_image(&dest_img);
                return 8;
            }
            continue;
        }

        int destx, desty;
        printf("Enter coordinates (x, y): ");
        if (scanf("%d %d", &destx, &desty) != 2) {
            printf("Incorrect input\n");
            destroy_image(&sub_img);
            free(dest_filename_buffer);
            destroy_image(&dest_img);
            return 1;
        }

        if (draw_image(dest_img, sub_img, destx, desty) != 0) {
            printf("Incorrect input data\n");
        }

        destroy_image(&sub_img);
    }

    char* modified_filename = create_modified_filename(dest_filename_buffer);
    if (modified_filename == NULL) {
        printf("Failed to allocate memory\n");
        free(dest_filename_buffer);
        destroy_image(&dest_img);
        return 8;
    }

    if (save_image_t(modified_filename, dest_img) != 0) {
        printf("Couldn't create file\n");
        free(modified_filename);
        free(dest_filename_buffer);
        destroy_image(&dest_img);
        return 5;
    }

    printf("File saved\n");

    free(modified_filename);
    free(dest_filename_buffer);
    destroy_image(&dest_img);

    return 0;
}
