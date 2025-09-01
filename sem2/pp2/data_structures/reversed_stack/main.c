// Reverse sentences in files using a stack of sentences
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char **argv)
{
    // Preflight: verify we can allocate at least 1 byte before any output
    void *probe = malloc(1);
    if (probe == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }
    free(probe);

    if (argc < 2)
    {
        printf("Not enough arguments\n");
        return 9;
    }

    int i = 1;
    while (i < argc)
    {
        const char *name = *(argv + i);
        struct stack_t *stack = NULL;
        int lrc = stack_load(&stack, name);
        if (lrc == 2)
        {
            printf("Couldn't open file %s\n", name);
            i += 1;
            continue;
        }
        else if (lrc == 3)
        {
            printf("Failed to allocate memory\n");
            return 8;
        }
        else if (lrc == 1)
        {
            // invalid input pointers; treat as fatal generic error
            stack_destroy(&stack);
            return 1;
        }

        int src = stack_save(stack, name);
        if (src == 2)
        {
            stack_destroy(&stack);
            printf("Couldn't create file\n");
            return 5;
        }
        else if (src == 1)
        {
            stack_destroy(&stack);
            return 1;
        }

        stack_destroy(&stack);
        printf("File %s saved\n", name);
        i += 1;
    }

    return 0;
}
