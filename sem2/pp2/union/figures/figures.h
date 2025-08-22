//
// Created by Bartek on 22.08.2025.
//

#ifndef UNION_FIGURES_H
#define UNION_FIGURES_H

#include <math.h>

// Structure definitions
struct point_t {
    int x;
    int y;
};

struct rectangle_t {
    struct point_t p;
    int width;
    int height;
};

struct circle_t {
    struct point_t c;
    float r;
};

struct triangle_t {
    struct point_t p1;
    struct point_t p2;
    struct point_t p3;
};

enum figure_types {
    TRIANGLE = 1,
    RECTANGLE,
    CIRCLE
};

struct figure_t {
    union {
        struct rectangle_t rect;
        struct triangle_t triangle;
        struct circle_t circ;
    };
    enum figure_types type;
};

// Function prototypes for area calculation
float area_triangle(const struct triangle_t *t);
float area_rectangle(const struct rectangle_t *r);
float area_circle(const struct circle_t *c);
float area_figure(const struct figure_t *f);

// Function prototypes for displaying figures
void display_rectangle(const struct rectangle_t *rect);
void display_triangle(const struct triangle_t *t);
void display_circle(const struct circle_t *circ);
void display_figure(struct figure_t *f);

// Function prototype for sorting
int sort_by_area(struct figure_t **figures, int size);

#endif //UNION_FIGURES_H
