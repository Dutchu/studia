// mirror_image: flip (horizontal/vertical) and negate P2 images

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_utils.h"

static char* prefixed_name(const char* prefix, const char* original) {
    if (prefix == NULL || original == NULL) return NULL;
    size_t lp = strlen(prefix);
    size_t lo = strlen(original);
    char *out = (char*)malloc(lp + lo + 1);
    if (out == NULL) return NULL;
    // Build string using pointer arithmetic
    char *p = out;
    const char *s = prefix;
    while (*s) { *p = *s; ++p; ++s; }
    s = original;
    while (*s) { *p = *s; ++p; ++s; }
    *p = '\0';
    return out;
}

int main(void) {
    // Allocate buffer for filename BEFORE prompting (per memory-failure flow)
    char *filename = (char*)malloc(40 * sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Enter file name: ");
    if (scanf("%39s", filename) != 1) {
        // The task does not specify input validation for the name; treat as generic incorrect input
        free(filename);
        printf("Incorrect input\n");
        return 1;
    }

    int err_code = 0;
    struct image_t *src = load_image_t(filename, &err_code);
    if (src == NULL) {
        free(filename);
        if (err_code == 2) { printf("Couldn't open file\n"); return 4; }
        if (err_code == 3) { printf("File corrupted\n"); return 6; }
        if (err_code == 4) { printf("Failed to allocate memory\n"); return 8; }
        return 1;
    }

    // Horizontal mirror (top-bottom): use horizontal-axis flip function
    struct image_t *mh = image_flip_horizontal(src);
    if (mh == NULL) {
        printf("Failed to allocate memory\n");
        destroy_image(&src);
        free(filename);
        return 8;
    }
    char *name_h = prefixed_name("mirror_h_", filename);
    if (name_h == NULL) {
        printf("Failed to allocate memory\n");
        destroy_image(&mh);
        destroy_image(&src);
        free(filename);
        return 8;
    }
    int rc = save_image_t(name_h, mh);
    if (rc == 0) printf("File saved\n"); else printf("Couldn't create file\n");
    destroy_image(&mh);
    free(name_h);

    // Vertical mirror (left-right): use vertical-axis flip function
    struct image_t *mv = image_flip_vertical(src);
    if (mv == NULL) {
        printf("Failed to allocate memory\n");
        destroy_image(&src);
        free(filename);
        return 8;
    }
    char *name_v = prefixed_name("mirror_v_", filename);
    if (name_v == NULL) {
        printf("Failed to allocate memory\n");
        destroy_image(&mv);
        destroy_image(&src);
        free(filename);
        return 8;
    }
    rc = save_image_t(name_v, mv);
    if (rc == 0) printf("File saved\n"); else printf("Couldn't create file\n");
    destroy_image(&mv);
    free(name_v);

    // Invert
    struct image_t *ni = image_negate(src);
    if (ni == NULL) {
        printf("Failed to allocate memory\n");
        destroy_image(&src);
        free(filename);
        return 8;
    }
    char *name_i = prefixed_name("invert_", filename);
    if (name_i == NULL) {
        printf("Failed to allocate memory\n");
        destroy_image(&ni);
        destroy_image(&src);
        free(filename);
        return 8;
    }
    rc = save_image_t(name_i, ni);
    if (rc == 0) printf("File saved\n"); else printf("Couldn't create file\n");
    destroy_image(&ni);
    free(name_i);

    destroy_image(&src);
    free(filename);
    return 0;
}
