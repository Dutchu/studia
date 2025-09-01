// Implementation of image utilities and simple transforms

#include "image_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static struct image_t* image_alloc_like(const struct image_t *src) {
    if (src == NULL || src->ptr == NULL || src->width <= 0 || src->height <= 0) {
        return NULL;
    }

    size_t struct_size = sizeof(struct image_t);
    size_t row_ptrs_size = (size_t)src->height * sizeof(int*);
    size_t pixels_size = (size_t)src->height * (size_t)src->width * sizeof(int);

    char *buffer = (char*)malloc(struct_size + row_ptrs_size + pixels_size);
    if (buffer == NULL) {
        return NULL;
    }

    struct image_t *img = (struct image_t*)buffer;
    img->ptr = (int**)(buffer + struct_size);
    int *pixel_data = (int*)(buffer + struct_size + row_ptrs_size);

    // Copy type and dimensions
    *(img->type) = 'P';
    *(img->type + 1) = '2';
    *(img->type + 2) = '\0';
    img->width = src->width;
    img->height = src->height;

    for (int i = 0; i < img->height; ++i) {
        *(img->ptr + i) = pixel_data + (size_t)i * (size_t)img->width;
    }

    return img;
}

void destroy_image(struct image_t **m) {
    if (m == NULL || *m == NULL) {
        return;
    }
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

    char p, two;
    if (fscanf(f, "%c%c", &p, &two) != 2 || p != 'P' || two != '2') {
        if (err_code) *err_code = 3;
        fclose(f);
        return NULL;
    }

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

    size_t struct_size = sizeof(struct image_t);
    size_t row_pointers_size = (size_t)height * sizeof(int*);
    size_t pixel_data_size = (size_t)height * (size_t)width * sizeof(int);

    char *buffer = (char*)malloc(struct_size + row_pointers_size + pixel_data_size);
    if (buffer == NULL) {
        if (err_code) *err_code = 4;
        fclose(f);
        return NULL;
    }

    struct image_t *img = (struct image_t*)buffer;
    img->ptr = (int**)(buffer + struct_size);
    int *pixel_data_start = (int*)(buffer + struct_size + row_pointers_size);

    *(img->type) = 'P';
    *(img->type + 1) = '2';
    *(img->type + 2) = '\0';
    img->width = width;
    img->height = height;

    for (int i = 0; i < img->height; ++i) {
        *(img->ptr + i) = pixel_data_start + (size_t)i * (size_t)img->width;
    }

    for (int i = 0; i < img->height; ++i) {
        for (int j = 0; j < img->width; ++j) {
            int pixel_value;
            if (fscanf(f, "%d", &pixel_value) != 1 || pixel_value < 0 || pixel_value > max_val) {
                if (err_code) *err_code = 3;
                free(img);
                fclose(f);
                return NULL;
            }
            *(*(img->ptr + i) + j) = pixel_value;
        }
    }

    int c;
    while ((c = fgetc(f)) != EOF) {
        if (!isspace(c)) {
            if (err_code) *err_code = 3;
            free(img);
            fclose(f);
            return NULL;
        }
    }

    if (err_code) *err_code = 0;
    fclose(f);
    return img;
}

int save_image_t(const char *filename, const struct image_t *m1) {
    if (filename == NULL || m1 == NULL || m1->ptr == NULL || m1->width <= 0 || m1->height <= 0) {
        return 1;
    }

    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        return 2;
    }

    if (fprintf(f, "%s\n", m1->type) < 0) { fclose(f); return 3; }
    if (fprintf(f, "%d %d\n", m1->width, m1->height) < 0) { fclose(f); return 3; }
    if (fprintf(f, "%d\n", 255) < 0) { fclose(f); return 3; }

    for (int i = 0; i < m1->height; ++i) {
        for (int j = 0; j < m1->width; ++j) {
            if (fprintf(f, "%d ", *(*(m1->ptr + i) + j)) < 0) { fclose(f); return 3; }
        }
        if (fprintf(f, "\n") < 0) { fclose(f); return 3; }
    }

    fclose(f);
    return 0;
}

struct image_t* image_flip_horizontal(const struct image_t *m1) {
    if (m1 == NULL || m1->ptr == NULL || m1->width <= 0 || m1->height <= 0) {
        return NULL;
    }
    struct image_t *dst = image_alloc_like(m1);
    if (dst == NULL) {
        return NULL;
    }

    // Flip across the horizontal axis (top <-> bottom)
    for (int y = 0; y < m1->height; ++y) {
        for (int x = 0; x < m1->width; ++x) {
            int dy = m1->height - 1 - y;
            int *pd = *(dst->ptr + dy) + x;
            int *ps = *(m1->ptr + y) + x;
            *pd = *ps;
        }
    }
    return dst;
}

struct image_t* image_flip_vertical(const struct image_t *m1) {
    if (m1 == NULL || m1->ptr == NULL || m1->width <= 0 || m1->height <= 0) {
        return NULL;
    }
    struct image_t *dst = image_alloc_like(m1);
    if (dst == NULL) {
        return NULL;
    }

    // Flip across the vertical axis (left <-> right)
    for (int y = 0; y < m1->height; ++y) {
        for (int x = 0; x < m1->width; ++x) {
            int dx = m1->width - 1 - x;
            int *pd = *(dst->ptr + y) + dx;
            int *ps = *(m1->ptr + y) + x;
            *pd = *ps;
        }
    }
    return dst;
}

struct image_t* image_negate(const struct image_t *m1) {
    if (m1 == NULL || m1->ptr == NULL || m1->width <= 0 || m1->height <= 0) {
        return NULL;
    }
    struct image_t *dst = image_alloc_like(m1);
    if (dst == NULL) {
        return NULL;
    }

    for (int y = 0; y < m1->height; ++y) {
        for (int x = 0; x < m1->width; ++x) {
            int *pd = *(dst->ptr + y) + x;
            int *ps = *(m1->ptr + y) + x;
            *pd = 255 - *ps;
        }
    }
    return dst;
}
