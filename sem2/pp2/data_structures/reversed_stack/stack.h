// Sentence-reversing stack interface (single-node struct)
#ifndef REVERSED_STACK_STACK_H
#define REVERSED_STACK_STACK_H

struct stack_t
{
    char *sentence;           // pointer to a sentence (C-string, ends with '.')
    struct stack_t *prev;     // next lower element; NULL at bottom
};

int stack_push(struct stack_t **stack, char *value);
char *stack_pop(struct stack_t **stack, int *err_code);
void stack_destroy(struct stack_t **stack);
int stack_load(struct stack_t **stack, const char *filename);
int stack_save(const struct stack_t *stack, const char *filename);

#endif // REVERSED_STACK_STACK_H
