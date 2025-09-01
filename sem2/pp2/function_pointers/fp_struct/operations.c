#include <stdlib.h>
#include "operations.h"

static void free_if_needed(void* p, void* keep) {
    if (p && p != keep) {
        free(p);
    }
}

void* find_extremum(const void *a,
                    const void *b,
                    const struct operations_t *op,
                    int(* comp)(const void *, const void *)) {
    if (!op || !comp) {
        return NULL;
    }

    void* results_add = NULL;
    void* results_sub = NULL;
    void* results_div = NULL;
    void* results_mul = NULL;

    if (op->add) {
        results_add = op->add(a, b);
    }
    if (op->sub) {
        results_sub = op->sub(a, b);
    }
    if (op->div) {
        results_div = op->div(a, b);
    }
    if (op->mul) {
        results_mul = op->mul(a, b);
    }

    void* best = NULL;
    int any = 0;

    if (results_add) {
        best = results_add;
        any = 1;
    }
    if (results_sub) {
        if (!best) {
            best = results_sub;
            any = 1;
        } else if (comp(results_sub, best) == 1) {
            best = results_sub;
        }
    }
    if (results_div) {
        if (!best) {
            best = results_div;
            any = 1;
        } else if (comp(results_div, best) == 1) {
            best = results_div;
        }
    }
    if (results_mul) {
        if (!best) {
            best = results_mul;
            any = 1;
        } else if (comp(results_mul, best) == 1) {
            best = results_mul;
        }
    }

    if (!any) {
        return NULL;
    }

    free_if_needed(results_add, best);
    free_if_needed(results_sub, best);
    free_if_needed(results_div, best);
    free_if_needed(results_mul, best);

    return best;
}

