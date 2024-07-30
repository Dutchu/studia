
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include "string.h"
#include "stdio.h"
#include "math.h"

struct point_t {
    int x;
    int y;
};

struct point_t* set(struct point_t* p, int x, int y);
void show(const struct point_t* p);
float distance(const struct point_t* p1, const struct point_t* p2, int *err_code);
int read_number();
int get_x();
int get_y();
float parse_number(int a, int *err);
struct point_t* read(struct point_t* p);
int main() {


    int p_err;
    struct point_t p1;
    struct point_t *pp1;
    pp1 = read(&p1);


    time_t t;
    srand((unsigned) time(&t));

    struct point_t p2;
    struct point_t *pp2;
    pp2 = set(&p2, rand() % 100, rand() % 100);

    show(pp1);
    show(pp2);

    float result = distance(pp1, pp2, &p_err);


    printf("%.2f", result);

    return p_err;
}

struct point_t* set(struct point_t* p, int x, int y) {
    if (p == NULL) return NULL;

    p->x = x;
    p->y = y;

    return p;
}

void show(const struct point_t* p) {
    if (p == NULL) return;
    printf("x = %d; y = %d\n", p->x, p->y);
}

float distance(const struct point_t* p1, const struct point_t* p2, int *err_code) {

    int err = 0;
    int err1 = 0;
    int err2 = 0;
    int err3 = 0;
    int err4 = 0;
    if (err_code == NULL) {
        err_code = &err;
    }
    if (p1 == NULL || p2 == NULL) {*err_code = 1; return -1.0f;} else *err_code = 0;

    float x1,x2,y1,y2,result;

    x1 = parse_number(p1->x, &err1);
    x2 = parse_number(p2->x, &err2);
    y1 = parse_number(p1->y, &err3);
    y2 = parse_number(p2->y, &err4);

    if (err != 0 || err1 != 0 || err2 != 0 || err3 != 0 || err4 != 0) {
        *err_code = 1;
        result = -1;
    } else {
        result = sqrtf(powf(x2 - x1, 2.0f) + powf(y2 - y1, 2.0f));
    }

    return result;

}

int get_x() {
    printf("Podaj współrzędną x: ");
    return read_number();
}
int get_y() {
    printf("Podaj współrzędną y: ");
    return read_number();
}
int read_number() {
    int a;
    int rc;
    rc = scanf("%d", &a);
    if (rc != 1) {
        printf("Incorrect input");
        exit(1);
    }
    return a;
}
float parse_number(int a, int *err) {

    float b = (float) a;
    if (b > FLT_MAX || b < -FLT_MAX) {
        *err = -1;
        b = 0;
    }
    return b;
}
struct point_t* read(struct point_t* p) {
    if (p == NULL) return NULL;

    int x = get_x();
    int y = get_y();

    p->x = x;
    p->y = y;

    return p;
}