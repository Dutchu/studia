#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include "int_operations.h"
#include "float_operations.h"
#include "complex_operations.h"

static void fill_operations(struct operations_t* dst,
                            binary_op_t addf,
                            binary_op_t subf,
                            binary_op_t divf,
                            binary_op_t mulf,
                            read_func_t readf,
                            show_func_t showf) {
    if (!dst) {
        return;
    }
    dst->add = addf;
    dst->sub = subf;
    dst->div = divf;
    dst->mul = mulf;
    dst->read = readf;
    dst->show = showf;
}

int main(void) {
    struct operations_t* ops = (struct operations_t*)malloc(3 * sizeof(struct operations_t));
    if (!ops) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    fill_operations(ops + 0, add_float, sub_float, div_float, mul_float, read_float, show_float);
    fill_operations(ops + 1, add_int, sub_int, div_int, mul_int, read_int, show_int);
    fill_operations(ops + 2, add_complex, sub_complex, div_complex, mul_complex, read_complex, show_complex);

    int exit_code = 0;

    printf("Enter data type: ");
    int type_value = 0;
    int rtype = scanf("%d", &type_value);
    if (rtype != 1) {
        printf("Incorrect input\n");
        free(ops);
        return 1;
    }
    if (!(type_value == 0 || type_value == 1 || type_value == 2)) {
        printf("Incorrect input\n");
        free(ops);
        return 1;
    }

    printf("Enter values: ");

    struct operations_t* op = ops + type_value;

    if (type_value == 0) {
        float a = 0.0f;
        float b = 0.0f;
        int rr = op->read(&a, &b);
        if (rr != 0) {
            printf("Incorrect input\n");
            free(ops);
            return 1;
        }
        void* res = find_extremum(&a, &b, op, is_smaller_float);
        if (!res) {
            printf("Failed to allocate memory\n");
            free(ops);
            return 8;
        }
        op->show(res);
        free(res);
    } else if (type_value == 1) {
        int a = 0;
        int b = 0;
        int rr = op->read(&a, &b);
        if (rr != 0) {
            printf("Incorrect input\n");
            free(ops);
            return 1;
        }
        void* res = find_extremum(&a, &b, op, is_smaller_int);
        if (!res) {
            printf("Failed to allocate memory\n");
            free(ops);
            return 8;
        }
        op->show(res);
        free(res);
    } else {
        struct complex_t a;
        struct complex_t b;
        int rr = op->read(&a, &b);
        if (rr != 0) {
            printf("Incorrect input\n");
            free(ops);
            return 1;
        }
        void* res = find_extremum(&a, &b, op, is_smaller_complex);
        if (!res) {
            printf("Failed to allocate memory\n");
            free(ops);
            return 8;
        }
        op->show(res);
        free(res);
    }

    free(ops);
    return exit_code;
}
