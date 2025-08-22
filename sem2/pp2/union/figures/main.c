//
// Created by Bartek on 22.08.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "figures.h"


float area_triangle(const struct triangle_t *t) {
    if (t == NULL) return -1;

    long long area_check = (long long) t->p1.x * (t->p2.y - t->p3.y) +
                           (long long) t->p2.x * (t->p3.y - t->p1.y) +
                           (long long) t->p3.x * (t->p1.y - t->p2.y);

    if (area_check == 0) {
        return -1;
    }

    return fabsf((float) area_check) / 2.0f;
}

float area_rectangle(const struct rectangle_t *r) {
    if (r == NULL || r->width <= 0 || r->height <= 0) {
        return -1;
    }
    return (float) r->width * (float) r->height;
}

float area_circle(const struct circle_t *c) {
    if (c == NULL || c->r <= 0) {
        return -1;
    }
    return (float) M_PI * c->r * c->r;
}

float area_figure(const struct figure_t *f) {
    if (f == NULL) return -1;
    switch (f->type) {
        case TRIANGLE:
            return area_triangle(&f->triangle);
        case RECTANGLE:
            return area_rectangle(&f->rect);
        case CIRCLE:
            return area_circle(&f->circ);
        default:
            return -1;
    }
}


void display_rectangle(const struct rectangle_t *rect) {
    if (rect == NULL) return;
    printf("Rectangle (%d, %d), width = %d, height = %d\n", rect->p.x, rect->p.y, rect->width, rect->height);
}

void display_triangle(const struct triangle_t *t) {
    if (t == NULL) return;
    printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d)\n", t->p1.x, t->p1.y, t->p2.x, t->p2.y, t->p3.x, t->p3.y);
}

void display_circle(const struct circle_t *circ) {
    if (circ == NULL) return;
    printf("Circle (%d, %d), radius = %f\n", circ->c.x, circ->c.y, circ->r);
}

void display_figure(struct figure_t *f) {
    if (f == NULL) return;
    switch (f->type) {
        case TRIANGLE:
            display_triangle(&f->triangle);
            break;
        case RECTANGLE:
            display_rectangle(&f->rect);
            break;
        case CIRCLE:
            display_circle(&f->circ);
            break;
    }
}


int sort_by_area(struct figure_t **figures, int size) {
    if (figures == NULL || size <= 0) {
        return 1;
    }

    for (int i = 0; i < size; ++i) {
        if (area_figure(*(figures + i)) < 0) {
            return 1;
        }
    }

    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            float area1 = area_figure(*(figures + j));
            float area2 = area_figure(*(figures + j + 1));
            if (area1 < area2) {
                struct figure_t *temp = *(figures + j);
                *(figures + j) = *(figures + j + 1);
                *(figures + j + 1) = temp;
            }
        }
    }
    return 0;
}

int main() {
    struct figure_t figures_storage[50];
    struct figure_t *figure_pointers[50];
    int figure_count = 0;

    while (figure_count < 50) {
        int type_input;
        printf("Enter figure's type: ");
        if (scanf("%d", &type_input) != 1) {
            printf("Incorrect input\n");
            return 1;
        }

        if (type_input == 0) {
            break;
        }

        struct figure_t *current_figure = figures_storage + figure_count;

        switch (type_input) {
            case TRIANGLE:
                printf("Enter vertices' coordinates of a triangle (x1 y1 x2 y2 x3 y3): ");
                if (scanf("%d %d %d %d %d %d", &current_figure->triangle.p1.x, &current_figure->triangle.p1.y,
                          &current_figure->triangle.p2.x, &current_figure->triangle.p2.y,
                          &current_figure->triangle.p3.x, &current_figure->triangle.p3.y) != 6) {
                    printf("Incorrect input\n");
                    return 1;
                }
                current_figure->type = TRIANGLE;
                break;
            case RECTANGLE:
                printf("Enter coordinates of a rectangle along with its dimensions (x y width height): ");
                if (scanf("%d %d %d %d", &current_figure->rect.p.x, &current_figure->rect.p.y,
                          &current_figure->rect.width, &current_figure->rect.height) != 4) {
                    printf("Incorrect input\n");
                    return 1;
                }
                current_figure->type = RECTANGLE;
                break;
            case CIRCLE:
                printf("Enter coordinates and radius of a circle: ");
                if (scanf("%d %d %f", &current_figure->circ.c.x, &current_figure->circ.c.y, &current_figure->circ.r) !=
                    3) {
                    printf("Incorrect input\n");
                    return 1;
                }
                current_figure->type = CIRCLE;
                break;
            default:

                printf("Incorrect input data\n");
                return 2;
        }
        *(figure_pointers + figure_count) = current_figure;
        figure_count++;
    }

    for (int i = 0; i < figure_count; ++i) {
        if (area_figure(*(figure_pointers + i)) < 0) {
            printf("Incorrect input data\n");
            return 2;
        }
    }

    sort_by_area(figure_pointers, figure_count);

    for (int i = 0; i < figure_count; ++i) {
        display_figure(*(figure_pointers + i));
    }

    return 0;
}
