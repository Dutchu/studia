#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void)
{
    struct stack_t *stack = NULL;
    int rc = stack_init(&stack, 10);
    if (rc == 2)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }
    else if (rc != 0)
    {
        // Should not happen with valid arguments; treat as fatal
        return 1;
    }

    for (;;)
    {
        int op;
        printf("Co chcesz zrobic? ");
        if (scanf("%d", &op) != 1)
        {
            printf("Incorrect input\n");
            stack_free(stack);
            return 1;
        }

        if (op == 0)
        {
            stack_free(stack);
            return 0;
        }
        else if (op == 1)
        {
            int value;
            printf("Podaj liczbe ");
            if (scanf("%d", &value) != 1)
            {
                printf("Incorrect input\n");
                stack_free(stack);
                return 1;
            }

            int prc = stack_push(stack, value);
            if (prc == 2)
            {
                printf("Failed to allocate memory\n");
                stack_free(stack);
                return 8;
            }
            // For prc == 1 (invalid data), ignore; not expected in normal flow
        }
        else if (op == 2)
        {
            int err = 0;
            int v = stack_pop(stack, &err);
            if (err == 2)
            {
                printf("Stack is empty\n");
            }
            else if (err == 0)
            {
                printf("%d\n", v);
            }
            // err == 1 -> invalid data; ignore
        }
        else if (op == 3)
        {
            if (stack && stack->head == 0)
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
