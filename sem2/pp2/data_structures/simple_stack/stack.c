// Implementation of dynamic integer stack
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int stack_init(struct stack_t **stack, int N)
{
    if (stack == NULL || N <= 0)
        return 1;

    *stack = (struct stack_t *)malloc(sizeof(struct stack_t));
    if (*stack == NULL)
        return 2;

    (*stack)->data = (int *)malloc((size_t)N * sizeof(int));
    if ((*stack)->data == NULL)
    {
        free(*stack);
        *stack = NULL;
        return 2;
    }

    (*stack)->head = 0;
    (*stack)->capacity = N;
    return 0;
}

int stack_push(struct stack_t *stack, int value)
{
    if (stack == NULL || stack->data == NULL || stack->capacity <= 0 || stack->head < 0)
        return 1;
    if (stack->head > stack->capacity)
        return 1;

    if (stack->head >= stack->capacity)
    {
        int new_capacity = stack->capacity * 2;
        if (new_capacity <= 0)
            return 2;
        int *tmp = (int *)realloc(stack->data, (size_t)new_capacity * sizeof(int));
        if (tmp == NULL)
            return 2;
        stack->data = tmp;
        stack->capacity = new_capacity;
    }

    *(stack->data + stack->head) = value;
    stack->head += 1;
    return 0;
}

int stack_pop(struct stack_t *stack, int *err_code)
{
    if (stack == NULL || stack->data == NULL || stack->head < 0 || stack->capacity <= 0)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    if (stack->head > stack->capacity)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    if (stack->head == 0)
    {
        if (err_code) *err_code = 2;
        return 0;
    }

    stack->head -= 1;
    int value = *(stack->data + stack->head);
    if (err_code) *err_code = 0;
    return value;
}

void stack_display(const struct stack_t *stack)
{
    if (stack == NULL || stack->data == NULL || stack->head < 0 || stack->capacity <= 0)
        return;
    if (stack->head > stack->capacity)
        return;

    for (int i = stack->head - 1; i >= 0; --i)
    {
        int v = *(stack->data + i);
        printf("%d ", v);
    }
}

void stack_free(struct stack_t *stack)
{
    if (stack == NULL)
        return;
    free(stack->data);
    free(stack);
}
