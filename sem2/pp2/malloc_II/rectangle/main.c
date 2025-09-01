//
// Rectangle drawing program
//

#include <stdio.h>
#include <stdlib.h>
#include "image_utils.h"

int main(void) {
    char *filename = (char*)malloc(40 * sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Podaj nazwe: ");
    if (scanf("%39s", filename) != 1) {
        printf("Incorrect input\n");
        free(filename);
        return 1;
    }
    int ch;
    do { ch = getchar(); } while (ch != '\n' && ch != EOF);

    int err_code = 0;
    struct image_t *img = load_image_t(filename, &err_code);
    if (img == NULL) {
        if (err_code == 2) {
            printf("Couldn't open file\n");
            free(filename);
            return 4;
        }
        if (err_code == 3) {
            printf("File corrupted\n");
            free(filename);
            return 6;
        }
        if (err_code == 4) {
            printf("Failed to allocate memory\n");
            free(filename);
            return 8;
        }
        free(filename);
        return 1;
    }

    struct rectangle_t rect;
    printf("Podaj wspolrzedne i wymiary prostokata: ");
    if (scanf("%d %d %d %d", &(rect.p.x), &(rect.p.y), &(rect.width), &(rect.height)) != 4) {
        printf("Incorrect input\n");
        free(filename);
        destroy_image(&img);
        return 1;
    }

    int color;
    printf("Podaj kolor: ");
    if (scanf("%d", &color) != 1) {
        printf("Incorrect input\n");
        free(filename);
        destroy_image(&img);
        return 1;
    }

    if (image_draw_rectangle(img, &rect, color) != 0) {
        printf("Incorrect input data\n");
        free(filename);
        destroy_image(&img);
        return 2;
    }

    int save_res = save_image_t(filename, img);
    if (save_res != 0) {
        printf("Couldn't create file\n");
        free(filename);
        destroy_image(&img);
        return 5;
    }

    printf("File saved\n");
    free(filename);
    destroy_image(&img);
    return 0;
}
