// RPN calculator using a linked-list double stack
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

static int eval_rpn_stream(struct stack_t *stack, FILE *in, double *out, int *alloc_fail)
{
    // Returns 0 on success (result in *out),
    // 1 on incorrect input (invalid characters),
    // 2 on incorrect expression (stack underflow/leftovers),
    // sets *alloc_fail=1 if memory allocation failed during evaluation.
    *alloc_fail = 0;

    for (;;)
    {
        int ch;
        // Skip whitespace but stop at newline
        do
        {
            ch = fgetc(in);
            if (ch == EOF || ch == '\n')
                goto finish_line;
        } while (isspace(ch));

        // Decide if this begins a number or an operator/invalid
        if (ch == '+' || ch == '-')
        {
            int next = fgetc(in);
            if (next == EOF || next == '\n')
            {
                // Standalone operator at EOL/EOF
                // Put next back if newline to ensure consistent handling
                if (next != EOF) ungetc(next, in);
                // operator token
                char c = (char)ch;
                int err1 = 0, err2 = 0;
                double b = stack_pop(stack, &err2);
                double a = stack_pop(stack, &err1);
                if (err1 != 0 || err2 != 0)
                    return 2;
                double r = (c == '+') ? (a + b) : (a - b);
                int prc = stack_push(stack, r);
                if (prc == 2)
                {
                    *alloc_fail = 1;
                    return 2;
                }
                else if (prc != 0)
                {
                    return 1;
                }
                continue;
            }

            if (isdigit(next) || next == '.')
            {
                // It's a signed number: push back next and parse number starting with sign
                ungetc(next, in);

                int sign = (ch == '-') ? -1 : 1;
                double value = 0.0;
                int saw_digit = 0;
                int frac_mode = 0;
                double frac_div = 10.0;

                while (1)
                {
                    int c2 = fgetc(in);
                    if (isdigit(c2))
                    {
                        saw_digit = 1;
                        if (!frac_mode)
                        {
                            value = value * 10.0 + (double)(c2 - '0');
                        }
                        else
                        {
                            value = value + ((double)(c2 - '0')) / frac_div;
                            frac_div *= 10.0;
                        }
                    }
                    else if (c2 == '.' && !frac_mode)
                    {
                        frac_mode = 1;
                    }
                    else
                    {
                        if (c2 != EOF)
                            ungetc(c2, in);
                        break;
                    }
                }

                if (!saw_digit)
                    return 1;

                value *= (double)sign;
                int prc = stack_push(stack, value);
                if (prc == 2)
                {
                    *alloc_fail = 1;
                    return 2;
                }
                else if (prc != 0)
                {
                    return 1;
                }
                continue;
            }
            else if (isspace(next))
            {
                // Operator followed by whitespace
                char c = (char)ch;
                int err1 = 0, err2 = 0;
                double b = stack_pop(stack, &err2);
                double a = stack_pop(stack, &err1);
                if (err1 != 0 || err2 != 0)
                    return 2;
                double r = (c == '+') ? (a + b) : (a - b);
                int prc = stack_push(stack, r);
                if (prc == 2)
                {
                    *alloc_fail = 1;
                    return 2;
                }
                else if (prc != 0)
                {
                    return 1;
                }
                continue;
            }
            else
            {
                // e.g. "+x" -> invalid input
                return 1;
            }
        }
        else if (isdigit(ch) || ch == '.')
        {
            // Number starting with digit or dot
            ungetc(ch, in);
            double value = 0.0;
            int saw_digit = 0;
            int frac_mode = 0;
            double frac_div = 10.0;

            while (1)
            {
                int c2 = fgetc(in);
                if (isdigit(c2))
                {
                    saw_digit = 1;
                    if (!frac_mode)
                    {
                        value = value * 10.0 + (double)(c2 - '0');
                    }
                    else
                    {
                        value = value + ((double)(c2 - '0')) / frac_div;
                        frac_div *= 10.0;
                    }
                }
                else if (c2 == '.' && !frac_mode)
                {
                    frac_mode = 1;
                }
                else
                {
                    if (c2 != EOF)
                        ungetc(c2, in);
                    break;
                }
            }

            if (!saw_digit)
                return 1;

            int prc = stack_push(stack, value);
            if (prc == 2)
            {
                *alloc_fail = 1;
                return 2;
            }
            else if (prc != 0)
            {
                return 1;
            }
            continue;
        }
        else if (ch == '*' || ch == '/')
        {
            int next = fgetc(in);
            if (next != EOF && !isspace(next))
            {
                // Token like "*x" invalid
                return 1;
            }
            if (next != EOF)
                ungetc(next, in);

            int err1 = 0, err2 = 0;
            double b = stack_pop(stack, &err2);
            double a = stack_pop(stack, &err1);
            if (err1 != 0 || err2 != 0)
                return 2;
            double r = (ch == '*') ? (a * b) : (a / b);
            int prc = stack_push(stack, r);
            if (prc == 2)
            {
                *alloc_fail = 1;
                return 2;
            }
            else if (prc != 0)
            {
                return 1;
            }
            continue;
        }
        else
        {
            // Invalid character
            return 1;
        }
    }

finish_line:
    {
        int sz = stack_size(stack);
        if (sz != 1)
        {
            return 2;
        }
        int e = 0;
        double res = stack_pop(stack, &e);
        if (e != 0)
            return 2;
        *out = res;
        return 0;
    }
}

int main(void)
{
    // Allocate the stack structure up front, so OOM is detected before prompting
    struct stack_t *stack = NULL;
    int init_rc = stack_init(&stack);
    if (init_rc == 2)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }
    else if (init_rc != 0)
    {
        return 1;
    }

    printf("Enter expression: ");

    double out = 0.0;
    int alloc_fail = 0;
    int rc = eval_rpn_stream(stack, stdin, &out, &alloc_fail);
    if (alloc_fail)
    {
        printf("Failed to allocate memory\n");
        stack_destroy(&stack);
        return 8;
    }
    if (rc == 1)
    {
        printf("Incorrect input\n");
        stack_destroy(&stack);
        return 1;
    }
    else if (rc == 2)
    {
        printf("Incorrect expression\n");
        stack_destroy(&stack);
        return 2;
    }

    printf("%f\n", out);
    stack_destroy(&stack);
    return 0;
}
