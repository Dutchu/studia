//
// Image utilities for grayscale P2 PGM images and rectangle drawing
//

#ifndef MALLOC_II_RECTANGLE_IMAGE_UTILS_H
#define MALLOC_II_RECTANGLE_IMAGE_UTILS_H

struct image_t {
    char type[3];
    int **ptr;
    int width;
    int height;
};

struct point_t {
    int x;
    int y;
};

struct rectangle_t {
    struct point_t p;
    int width;
    int height;
};

struct image_t* load_image_t(const char *filename, int *err_code);
int save_image_t(const char * filename, const struct image_t *m1);
void destroy_image(struct image_t **m);

const int* image_get_pixel(const struct image_t *img, int x, int y);
int* image_set_pixel(struct image_t *img, int x, int y);

int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty);

int image_draw_rectangle(struct image_t *img, const struct rectangle_t *rect, int value);

#endif //MALLOC_II_RECTANGLE_IMAGE_UTILS_H

