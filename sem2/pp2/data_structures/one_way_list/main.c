#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main(void)
{
    struct linked_list_t *ll = ll_create();
    if (ll == NULL)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    for (;;)
    {
        printf("Co chcesz zrobic? ");
        int op;
        if (scanf("%d", &op) != 1)
        {
            printf("Incorrect input\n");
            ll_clear(ll);
            free(ll);
            return 1;
        }

        if (op == 0)
        {
            ll_clear(ll);
            free(ll);
            return 0;
        }
        else if (op == 1)
        {
            int value;
            printf("Podaj liczbe ");
            if (scanf("%d", &value) != 1)
            {
                printf("Incorrect input\n");
                ll_clear(ll);
                free(ll);
                return 1;
            }
            int rc = ll_push_back(ll, value);
            if (rc == 2)
            {
                printf("Failed to allocate memory\n");
                ll_clear(ll);
                free(ll);
                return 8;
            }
        }
        else if (op == 2)
        {
            if (ll_is_empty(ll) == 1)
            {
                printf("List is empty\n");
            }
            else
            {
                int e = 0;
                int v = ll_pop_back(ll, &e);
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
                ll_clear(ll);
                free(ll);
                return 1;
            }
            int rc = ll_push_front(ll, value);
            if (rc == 2)
            {
                printf("Failed to allocate memory\n");
                ll_clear(ll);
                free(ll);
                return 8;
            }
        }
        else if (op == 4)
        {
            if (ll_is_empty(ll) == 1)
            {
                printf("List is empty\n");
            }
            else
            {
                int e = 0;
                int v = ll_pop_front(ll, &e);
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
                ll_clear(ll);
                free(ll);
                return 1;
            }
            printf("Podaj index ");
            if (scanf("%u", &index) != 1)
            {
                printf("Incorrect input\n");
                ll_clear(ll);
                free(ll);
                return 1;
            }
            int rc = ll_insert(ll, index, value);
            if (rc == 1)
            {
                printf("Index out of range\n");
            }
            else if (rc == 2)
            {
                printf("Failed to allocate memory\n");
                ll_clear(ll);
                free(ll);
                return 8;
            }
        }
        else if (op == 6)
        {
            if (ll_is_empty(ll) == 1)
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
                    ll_clear(ll);
                    free(ll);
                    return 1;
                }
                int err = 0;
                int v = ll_remove(ll, index, &err);
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
            if (ll_is_empty(ll) == 1)
            {
                printf("List is empty\n");
            }
            else
            {
                int e = 0;
                int v = ll_back(ll, &e);
                if (e == 0)
                    printf("%d\n", v);
            }
        }
        else if (op == 8)
        {
            if (ll_is_empty(ll) == 1)
            {
                printf("List is empty\n");
            }
            else
            {
                int e = 0;
                int v = ll_front(ll, &e);
                if (e == 0)
                    printf("%d\n", v);
            }
        }
        else if (op == 9)
        {
            int ie = ll_is_empty(ll);
            if (ie == 1) printf("1\n");
            else if (ie == 0) printf("0\n");
            else { ll_clear(ll); free(ll); return 1; }
        }
        else if (op == 10)
        {
            int sz = ll_size(ll);
            if (sz >= 0) printf("%d\n", sz);
            else { ll_clear(ll); free(ll); return 1; }
        }
        else if (op == 11)
        {
            ll_clear(ll);
        }
        else if (op == 12)
        {
            if (ll_is_empty(ll) == 1)
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
                    ll_clear(ll);
                    free(ll);
                    return 1;
                }
                int e = 0;
                int v = ll_at(ll, index, &e);
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
            int ie = ll_is_empty(ll);
            if (ie == 1)
            {
                printf("List is empty\n");
            }
            else if (ie == 0)
            {
                ll_display(ll);
                printf("\n");
            }
            else { ll_clear(ll); free(ll); return 1; }
        }
        else
        {
            printf("Incorrect input data\n");
        }
    }
}
