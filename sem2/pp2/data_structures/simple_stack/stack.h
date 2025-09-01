// Stack interface
#ifndef SIMPLE_STACK_STACK_H
#define SIMPLE_STACK_STACK_H

struct stack_t
{
    int head;      // index of first free slot (size)
    int capacity;  // allocated capacity
    int *data;     // pointer to elements buffer
};

int stack_init(struct stack_t **stack, int N);
int stack_push(struct stack_t *stack, int value);
int stack_pop(struct stack_t *stack, int *err_code);
void stack_display(const struct stack_t *stack);
void stack_free(struct stack_t *stack);

#endif // SIMPLE_STACK_STACK_H

