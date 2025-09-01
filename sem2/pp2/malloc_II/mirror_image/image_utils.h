// Image utilities for grayscale P2 PGM images and basic transforms

#ifndef MALLOC_II_MIRROR_IMAGE_IMAGE_UTILS_H
#define MALLOC_II_MIRROR_IMAGE_IMAGE_UTILS_H

struct image_t {
    char type[3];
    int **ptr;
    int width;
    int height;
};

// I/O and memory management (as in exercise 5.7)
struct image_t* load_image_t(const char *filename, int *err_code);
int save_image_t(const char * filename, const struct image_t *m1);
void destroy_image(struct image_t **m);

// Basic transforms
struct image_t* image_flip_horizontal(const struct image_t *m1);
struct image_t* image_flip_vertical(const struct image_t *m1);
struct image_t* image_negate(const struct image_t *m1);

#endif //MALLOC_II_MIRROR_IMAGE_IMAGE_UTILS_H

