#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void)
{
    struct stack_t *stack = NULL;
    int rc = stack_init(&stack);
    if (rc == 2)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }
    else if (rc != 0)
    {
        return 1;
    }

    for (;;)
    {
        int op;
        printf("Co chcesz zrobic? ");
        if (scanf("%d", &op) != 1)
        {
            printf("Incorrect input\n");
            stack_destroy(&stack);
            return 1;
        }

        if (op == 0)
        {
            stack_destroy(&stack);
            return 0;
        }
        else if (op == 1)
        {
            int value;
            printf("Podaj liczbe ");
            if (scanf("%d", &value) != 1)
            {
                printf("Incorrect input\n");
                stack_destroy(&stack);
                return 1;
            }

            int prc = stack_push(stack, value);
            if (prc == 2)
            {
                printf("Failed to allocate memory\n");
                stack_destroy(&stack);
                return 8;
            }
        }
        else if (op == 2)
        {
            int err = 0;
            int v = stack_pop(stack, &err);
            if (err == 1)
            {
                printf("Stack is empty\n");
            }
            else
            {
                printf("%d\n", v);
            }
        }
        else if (op == 3)
        {
            int e = stack_empty(stack);
            if (e == 2)
            {
                // invalid input; treat as fatal to keep behavior deterministic
                stack_destroy(&stack);
                return 1;
            }
            printf(e == 1 ? "1\n" : "0\n");
        }
        else if (op == 4)
        {
            int e = stack_empty(stack);
            if (e == 2)
            {
                stack_destroy(&stack);
                return 1;
            }
            if (e == 1)
            {
                printf("Stack is empty\n");
            }
            else
            {
                stack_display(stack);
                printf("\n");
            }
        }
        else
        {
            printf("Incorrect input data\n");
        }
    }
}
