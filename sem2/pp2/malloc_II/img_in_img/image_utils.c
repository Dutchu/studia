//
// Created by Bartek on 28.08.2025.
//

#include "image_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void destroy_image(struct image_t **m) {
    if (m == NULL || *m == NULL) {
        return;
    }
    // Since everything was allocated in one block, we only need to free the pointer
    // that was returned by malloc, which is the pointer to the struct itself.
    free(*m);
    *m = NULL;
}

struct image_t* load_image_t(const char *filename, int *err_code) {
    if (filename == NULL) {
        if (err_code) *err_code = 1;
        return NULL;
    }

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        if (err_code) *err_code = 2;
        return NULL;
    }

    // Read and validate the 'P2' type without using a temporary stack array.
    char p, two;
    if (fscanf(f, "%c%c", &p, &two) != 2 || p != 'P' || two != '2') {
        if (err_code) *err_code = 3;
        fclose(f);
        return NULL;
    }

    // Read header into temporary variables to determine allocation size.
    int width, height, max_val;
    if (fscanf(f, "%d %d", &width, &height) != 2 || width <= 0 || height <= 0) {
        if (err_code) *err_code = 3;
        fclose(f);
        return NULL;
    }

    if (fscanf(f, "%d", &max_val) != 1 || max_val < 0) {
        if (err_code) *err_code = 3;
        fclose(f);
        return NULL;
    }

    // --- SINGLE, COMBINED MEMORY ALLOCATION ---
    size_t struct_size = sizeof(struct image_t);
    size_t row_pointers_size = height * sizeof(int*);
    size_t pixel_data_size = height * width * sizeof(int);

    // Allocate a single contiguous block for the struct, the row pointers, and all pixel data.
    char *buffer = (char*)malloc(struct_size + row_pointers_size + pixel_data_size);

    if (buffer == NULL) {
        if (err_code) *err_code = 4;
        fclose(f);
        return NULL;
    }

    // --- Partition the single block into its components ---
    struct image_t *img = (struct image_t*)buffer;
    img->ptr = (int**)(buffer + struct_size);
    int *pixel_data_start = (int*)(buffer + struct_size + row_pointers_size);

    // Populate the struct fields
    *(img->type) = 'P';
    *(img->type + 1) = '2';
    *(img->type + 2) = '\0';
    img->width = width;
    img->height = height;
    img->max_val = max_val;

    // Set up the row pointers to point into the pixel data area
    for (int i = 0; i < img->height; ++i) {
        *(img->ptr + i) = pixel_data_start + i * img->width;
    }
    // --- END OF SINGLE ALLOCATION SETUP ---

    for (int i = 0; i < img->height; ++i) {
        for (int j = 0; j < img->width; ++j) {
            int pixel_value;
            if (fscanf(f, "%d", &pixel_value) != 1 || pixel_value < 0 || pixel_value > img->max_val) {
                if (err_code) *err_code = 3;
                free(img); // Cleanup: free the single buffer
                fclose(f);
                return NULL;
            }
            *(*(img->ptr + i) + j) = pixel_value;
        }
    }

    int c;
    while ((c = fgetc(f)) != EOF) {
        if (!isspace(c)) {
            if (err_code) *err_code = 3; // File corrupted
            free(img); // Cleanup: free the single buffer
            fclose(f);
            return NULL;
        }
    }

    if (err_code) *err_code = 0;
    fclose(f);
    return img;
}


int save_image_t(const char *filename, const struct image_t *m1) {
    if (filename == NULL || m1 == NULL || m1->ptr == NULL) {
        return 1;
    }

    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        return 2;
    }

    if (fprintf(f, "%s\n", m1->type) < 0) { fclose(f); return 3; }
    if (fprintf(f, "%d %d\n", m1->width, m1->height) < 0) { fclose(f); return 3; }
    if (fprintf(f, "%d\n", m1->max_val) < 0) { fclose(f); return 3; }

    for (int i = 0; i < m1->height; ++i) {
        for (int j = 0; j < m1->width; ++j) {
            if (fprintf(f, "%d ", *(*(m1->ptr + i) + j)) < 0) {
                fclose(f);
                return 3;
            }
        }
        if (fprintf(f, "\n") < 0) {
            fclose(f);
            return 3;
        }
    }

    fclose(f);
    return 0;
}

const int* image_get_pixel(const struct image_t *img, int x, int y) {
    if (img == NULL || img->ptr == NULL || x < 0 || y < 0 || x >= img->width || y >= img->height) {
        return NULL;
    }
    return (*(img->ptr + y) + x);
}

int* image_set_pixel(struct image_t *img, int x, int y) {
    if (img == NULL || img->ptr == NULL || x < 0 || y < 0 || x >= img->width || y >= img->height) {
        return NULL;
    }
    return (*(img->ptr + y) + x);
}

int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty) {
    if (img == NULL || src == NULL || img->ptr == NULL || src->ptr == NULL) {
        return 1;
    }
    if (destx < 0 || desty < 0 || destx + src->width > img->width || desty + src->height > img->height) {
        return 1;
    }

    for (int y = 0; y < src->height; ++y) {
        for (int x = 0; x < src->width; ++x) {
            int *pixel_dest = image_set_pixel(img, destx + x, desty + y);
            const int *pixel_src = image_get_pixel(src, x, y);
            if (pixel_dest && pixel_src) {
                *pixel_dest = *pixel_src;
            }
        }
    }
    return 0;
}
