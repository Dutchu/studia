//
// Image utilities and rectangle drawing implementation
//

#include "image_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
            if (fprintf(f, "%d ", *(*(m1->ptr + i) + j)) < 0) {
                fclose(f);
                return 3;
            }
        }
        if (fprintf(f, "\n") < 0) { fclose(f); return 3; }
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
    if (img->width <= 0 || img->height <= 0 || src->width <= 0 || src->height <= 0) {
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

int image_draw_rectangle(struct image_t *img, const struct rectangle_t *rect, int value) {
    if (img == NULL || img->ptr == NULL || rect == NULL) {
        return 1;
    }
    if (img->width <= 0 || img->height <= 0) {
        return 1;
    }
    if (*(img->type) != 'P' || *(img->type + 1) != '2') {
        return 1;
    }

    if (rect->width <= 0 || rect->height <= 0) {
        return 1;
    }
    if (rect->p.x < 0 || rect->p.y < 0) {
        return 1;
    }
    if (rect->p.x + rect->width > img->width || rect->p.y + rect->height > img->height) {
        return 1;
    }
    if (value < 0 || value > 255) {
        return 1;
    }

    int x0 = rect->p.x;
    int y0 = rect->p.y;
    int x1 = rect->p.x + rect->width - 1;
    int y1 = rect->p.y + rect->height - 1;

    for (int x = x0; x <= x1; ++x) {
        int *ptop = image_set_pixel(img, x, y0);
        if (ptop) { *ptop = value; }
        if (y1 != y0) {
            int *pbot = image_set_pixel(img, x, y1);
            if (pbot) { *pbot = value; }
        }
    }

    for (int y = y0; y <= y1; ++y) {
        int *pleft = image_set_pixel(img, x0, y);
        if (pleft) { *pleft = value; }
        if (x1 != x0) {
            int *pright = image_set_pixel(img, x1, y);
            if (pright) { *pright = value; }
        }
    }

    return 0;
}

