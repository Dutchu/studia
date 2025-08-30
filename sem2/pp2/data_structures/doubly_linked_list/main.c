// Interactive program for doubly linked list operations
#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

int main(void)
{
    struct doubly_linked_list_t *dll = dll_create();
    if (dll == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    for (;;)
    {
        int op;
        printf("Co chcesz zrobic? ");
        if (scanf("%d", &op) != 1)
        {
            printf("Incorrect input\n");
            dll_clear(dll);
            free(dll);
            return 1;
        }

        if (op == 0)
        {
            dll_clear(dll);
            free(dll);
            return 0;
        }
        else if (op == 1)
        {
            int value;
            printf("Podaj liczbe ");
            if (scanf("%d", &value) != 1)
            {
                printf("Incorrect input\n");
                dll_clear(dll);
                free(dll);
                return 1;
            }
            int rc = dll_push_back(dll, value);
            if (rc == 2)
            {
                printf("Failed to allocate memory\n");
                dll_clear(dll);
                free(dll);
                return 8;
            }
        }
        else if (op == 2)
        {
            if (dll_is_empty(dll) == 1)
            {
                printf("List is empty\n");
            }
            else
            {
                int e = 0;
                int v = dll_pop_back(dll, &e);
                if (e == 0)
                    printf("%d\n", v);
            }
        }
        else if (op == 3)
        {
            int value;
            printf("Podaj liczbe ");
            if (scanf("%d", &value) != 1)
            {
                printf("Incorrect input\n");
                dll_clear(dll);
                free(dll);
                return 1;
            }
            int rc = dll_push_front(dll, value);
            if (rc == 2)
            {
                printf("Failed to allocate memory\n");
                dll_clear(dll);
                free(dll);
                return 8;
            }
        }
        else if (op == 4)
        {
            if (dll_is_empty(dll) == 1)
            {
                printf("List is empty\n");
            }
            else
            {
                int e = 0;
                int v = dll_pop_front(dll, &e);
                if (e == 0)
                    printf("%d\n", v);
            }
        }
        else if (op == 5)
        {
            int value;
            unsigned int index;
            printf("Podaj liczbe ");
            if (scanf("%d", &value) != 1)
            {
                printf("Incorrect input\n");
                dll_clear(dll);
                free(dll);
                return 1;
            }
            printf("Podaj index ");
            if (scanf("%u", &index) != 1)
            {
                printf("Incorrect input\n");
                dll_clear(dll);
                free(dll);
                return 1;
            }
            int rc = dll_insert(dll, index, value);
            if (rc == 1)
            {
                printf("Index out of range\n");
            }
            else if (rc == 2)
            {
                printf("Failed to allocate memory\n");
                dll_clear(dll);
                free(dll);
                return 8;
            }
        }
        else if (op == 6)
        {
            if (dll_is_empty(dll) == 1)
            {
                printf("List is empty\n");
            }
            else
            {
                unsigned int index;
                printf("Podaj index ");
                if (scanf("%u", &index) != 1)
                {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                int err = 0;
                int v = dll_remove(dll, index, &err);
                if (err == 1)
                {
                    printf("Index out of range\n");
                }
                else
                {
                    printf("%d\n", v);
                }
            }
        }
        else if (op == 7)
        {
            if (dll_is_empty(dll) == 1)
            {
                printf("List is empty\n");
            }
            else
            {
                int e = 0;
                int v = dll_back(dll, &e);
                if (e == 0)
                    printf("%d\n", v);
            }
        }
        else if (op == 8)
        {
            if (dll_is_empty(dll) == 1)
            {
                printf("List is empty\n");
            }
            else
            {
                int e = 0;
                int v = dll_front(dll, &e);
                if (e == 0)
                    printf("%d\n", v);
            }
        }
        else if (op == 9)
        {
            int ie = dll_is_empty(dll);
            if (ie == 1) printf("1\n");
            else if (ie == 0) printf("0\n");
            else { dll_clear(dll); free(dll); return 1; }
        }
        else if (op == 10)
        {
            int sz = dll_size(dll);
            if (sz >= 0) printf("%d\n", sz);
            else { dll_clear(dll); free(dll); return 1; }
        }
        else if (op == 11)
        {
            dll_clear(dll);
        }
        else if (op == 12)
        {
            if (dll_is_empty(dll) == 1)
            {
                printf("List is empty\n");
            }
            else
            {
                unsigned int index;
                printf("Podaj index ");
                if (scanf("%u", &index) != 1)
                {
                    printf("Incorrect input\n");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                int e = 0;
                int v = dll_at(dll, index, &e);
                if (e == 1)
                {
                    printf("Index out of range\n");
                }
                else
                {
                    printf("%d\n", v);
                }
            }
        }
        else if (op == 13)
        {
            int ie = dll_is_empty(dll);
            if (ie == 1)
            {
                printf("List is empty\n");
            }
            else if (ie == 0)
            {
                dll_display(dll);
                printf("\n");
            }
            else { dll_clear(dll); free(dll); return 1; }
        }
        else if (op == 14)
        {
            int ie = dll_is_empty(dll);
            if (ie == 1)
            {
                printf("List is empty\n");
            }
            else if (ie == 0)
            {
                dll_display_reverse(dll);
                printf("\n");
            }
            else { dll_clear(dll); free(dll); return 1; }
        }
        else
        {
            printf("Incorrect input data\n");
        }
    }
}
