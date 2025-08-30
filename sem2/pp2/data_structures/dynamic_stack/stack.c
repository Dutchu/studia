// Linked-list based integer stack implementation
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int stack_init(struct stack_t **stack)
{
    if (stack == NULL)
        return 1;

    *stack = (struct stack_t *)malloc(sizeof(struct stack_t));
    if (*stack == NULL)
        return 2;

    (*stack)->head = NULL;
    return 0;
}

int stack_push(struct stack_t *stack, int value)
{
    if (stack == NULL)
        return 1;

    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));
    if (node == NULL)
        return 2;

    node->data = value;
    node->next = stack->head;
    stack->head = node;
    return 0;
}

int stack_pop(struct stack_t *stack, int *err_code)
{
    if (stack == NULL || stack->head == NULL)
    {
        if (err_code) *err_code = 1; // invalid input or empty stack
        return 0;
    }

    struct node_t *node = stack->head;
    int value = node->data;
    stack->head = node->next;
    free(node);
    if (err_code) *err_code = 0;
    return value;
}

int stack_empty(const struct stack_t *stack)
{
    if (stack == NULL)
        return 2;
    return stack->head == NULL ? 1 : 0;
}

void stack_display(const struct stack_t *stack)
{
    if (stack == NULL)
        return;
    const struct node_t *it = stack->head;
    while (it)
    {
        printf("%d ", it->data);
        it = it->next;
    }
}

void stack_destroy(struct stack_t **stack)
{
    if (stack == NULL || *stack == NULL)
        return;
    struct node_t *it = (*stack)->head;
    while (it)
    {
        struct node_t *next = it->next;
        free(it);
        it = next;
    }
    free(*stack);
    *stack = NULL;
}
