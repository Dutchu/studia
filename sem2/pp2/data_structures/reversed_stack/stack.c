// Sentence stack implementation for reversing file sentences
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int stack_push(struct stack_t **stack, char *value)
{
    if (stack == NULL || value == NULL)
        return 1;

    struct stack_t *node = (struct stack_t *)malloc(sizeof(struct stack_t));
    if (node == NULL)
        return 2;

    node->sentence = value;
    node->prev = *stack;
    *stack = node;
    return 0;
}

char *stack_pop(struct stack_t **stack, int *err_code)
{
    if (stack == NULL || *stack == NULL)
    {
        if (err_code) *err_code = 1;
        return NULL;
    }
    struct stack_t *node = *stack;
    char *value = node->sentence;
    *stack = node->prev;
    free(node);
    if (err_code) *err_code = 0;
    return value;
}

void stack_destroy(struct stack_t **stack)
{
    if (stack == NULL || *stack == NULL)
        return;
    struct stack_t *it = *stack;
    while (it)
    {
        struct stack_t *prev = it->prev;
        free(it->sentence);
        free(it);
        it = prev;
    }
    *stack = NULL;
}

int stack_load(struct stack_t **stack, const char *filename)
{
    if (stack == NULL || filename == NULL)
        return 1;
    // Must load into an empty stack (top pointer must be NULL)
    if (*stack != NULL)
        return 1;

    FILE *f = fopen(filename, "rb");
    if (f == NULL)
        return 2;

    char *buf = NULL;
    size_t len = 0;

    for (;;)
    {
        int ch = fgetc(f);
        if (ch == EOF)
            break;

        // append character
        char *tmp = (char *)realloc(buf, len + 1);
        if (tmp == NULL)
        {
            free(buf);
            fclose(f);
            stack_destroy(stack);
            return 3;
        }
        buf = tmp;
        *(buf + len) = (char)ch;
        len += 1;

        if (ch == '.')
        {
            // finalize current sentence by adding NUL terminator
            char *tmp2 = (char *)realloc(buf, len + 1);
            if (tmp2 == NULL)
            {
                free(buf);
                fclose(f);
                stack_destroy(stack);
                return 3;
            }
            buf = tmp2;
            *(buf + len) = '\0';

            int prc = stack_push(stack, buf);
            if (prc == 2)
            {
                free(buf);
                fclose(f);
                stack_destroy(stack);
                return 3;
            }
            else if (prc != 0)
            {
                free(buf);
                fclose(f);
                stack_destroy(stack);
                return 1;
            }

            // reset buffer to start reading next sentence
            buf = NULL;
            len = 0;
        }
    }

    // discard incomplete tail if any
    free(buf);
    fclose(f);
    return 0;
}

int stack_save(const struct stack_t *stack, const char *filename)
{
    if (stack == NULL || filename == NULL)
        return 1;

    FILE *f = fopen(filename, "wb");
    if (f == NULL)
        return 2;

    const struct stack_t *it = stack;
    while (it)
    {
        const char *p = it->sentence;
        if (p)
        {
            while (*p)
            {
                if (fputc((unsigned char)*p, f) == EOF)
                {
                    // On write error treat as create/open failure
                    fclose(f);
                    return 2;
                }
                p += 1;
            }
        }
        it = it->prev;
    }

    fclose(f);
    return 0;
}
