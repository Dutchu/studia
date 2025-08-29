//
// Created by Bartek on 29.08.2025.
//

#ifndef FUNCTION_POINTERS_INT_OPERATIONS_H
#define FUNCTION_POINTERS_INT_OPERATIONS_H

int add_int(int a, int b);

int sub_int(int a, int b);

int div_int(int a, int b);

int mul_int(int a, int b);

enum operations_t {
    op_add, op_sub, op_div, op_mul
};

typedef int (*binary_operation)(int, int);

int calculate(int a, int b, binary_operation op);

binary_operation get_function(enum operations_t op);

#endif //FUNCTION_POINTERS_INT_OPERATIONS_H
