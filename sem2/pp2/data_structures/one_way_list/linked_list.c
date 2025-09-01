// Singly linked list implementation
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

static struct node_t* make_node(int value)
{
    struct node_t *n = (struct node_t*)malloc(sizeof(struct node_t));
    if (n == NULL) return NULL;
    n->data = value;
    n->next = NULL;
    return n;
}

struct linked_list_t* ll_create()
{
    struct linked_list_t *ll = (struct linked_list_t*)malloc(sizeof(struct linked_list_t));
    if (ll == NULL) return NULL;
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}

int ll_push_back(struct linked_list_t* ll, int value)
{
    if (ll == NULL) return 1;
    struct node_t *n = make_node(value);
    if (n == NULL) return 2;
    if (ll->tail == NULL)
    {
        ll->head = n;
        ll->tail = n;
    }
    else
    {
        ll->tail->next = n;
        ll->tail = n;
    }
    return 0;
}

int ll_push_front(struct linked_list_t* ll, int value)
{
    if (ll == NULL) return 1;
    struct node_t *n = make_node(value);
    if (n == NULL) return 2;
    if (ll->head == NULL)
    {
        ll->head = n;
        ll->tail = n;
    }
    else
    {
        n->next = ll->head;
        ll->head = n;
    }
    return 0;
}

int ll_pop_front(struct linked_list_t* ll, int *err_code)
{
    if (ll == NULL || ll->head == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    struct node_t *n = ll->head;
    int value = n->data;
    ll->head = n->next;
    if (ll->head == NULL)
        ll->tail = NULL;
    free(n);
    if (err_code) *err_code = 0;
    return value;
}

int ll_pop_back(struct linked_list_t* ll, int *err_code)
{
    if (ll == NULL || ll->tail == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    struct node_t *prev = NULL;
    struct node_t *it = ll->head;
    while (it && it->next)
    {
        prev = it;
        it = it->next;
    }

    int value = it->data;
    if (prev == NULL)
    {
        // Only one element
        ll->head = NULL;
        ll->tail = NULL;
    }
    else
    {
        prev->next = NULL;
        ll->tail = prev;
    }
    free(it);
    if (err_code) *err_code = 0;
    return value;
}

int ll_back(const struct linked_list_t* ll, int *err_code)
{
    if (ll == NULL || ll->tail == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    if (err_code) *err_code = 0;
    return ll->tail->data;
}

int ll_front(const struct linked_list_t* ll, int *err_code)
{
    if (ll == NULL || ll->head == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    if (err_code) *err_code = 0;
    return ll->head->data;
}

struct node_t* ll_begin(struct linked_list_t* ll)
{
    if (ll == NULL) return NULL;
    return ll->head;
}

struct node_t* ll_end(struct linked_list_t* ll)
{
    if (ll == NULL) return NULL;
    return ll->tail;
}

int ll_size(const struct linked_list_t* ll)
{
    if (ll == NULL) return -1;
    int count = 0;
    const struct node_t *it = ll->head;
    while (it)
    {
        count += 1;
        it = it->next;
    }
    return count;
}

int ll_is_empty(const struct linked_list_t* ll)
{
    if (ll == NULL) return -1;
    return ll->head == NULL ? 1 : 0;
}

int ll_at(const struct linked_list_t* ll, unsigned int index, int *err_code)
{
    if (ll == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    const struct node_t *it = ll->head;
    unsigned int i = 0;
    while (it && i < index)
    {
        it = it->next;
        i += 1;
    }
    if (it == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    if (err_code) *err_code = 0;
    return it->data;
}

int ll_insert(struct linked_list_t* ll, unsigned int index, int value)
{
    if (ll == NULL) return 1;
    int sz = ll_size(ll);
    if (sz < 0) return 1;
    if ((unsigned int)sz < index) return 1;

    if (index == 0)
        return ll_push_front(ll, value);
    if ((unsigned int)sz == index)
        return ll_push_back(ll, value);

    // Insert before node at position index, so link after node at index-1
    struct node_t *prev = ll->head;
    unsigned int i = 1; // prev at index 0 initially
    while (prev && i < index)
    {
        prev = prev->next;
        i += 1;
    }
    if (prev == NULL) return 1;

    struct node_t *n = make_node(value);
    if (n == NULL) return 2;
    n->next = prev->next;
    prev->next = n;
    if (n->next == NULL) ll->tail = n;
    return 0;
}

int ll_remove(struct linked_list_t* ll, unsigned int index, int *err_code)
{
    if (ll == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    int sz = ll_size(ll);
    if (sz <= 0)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    if ((unsigned int)sz <= index)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    if (index == 0)
        return ll_pop_front(ll, err_code);
    if ((unsigned int)(sz - 1) == index)
        return ll_pop_back(ll, err_code);

    struct node_t *prev = ll->head;
    unsigned int i = 1; // prev is at index 0
    while (prev && i < index)
    {
        prev = prev->next;
        i += 1;
    }
    if (prev == NULL || prev->next == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }

    struct node_t *rem = prev->next;
    int value = rem->data;
    prev->next = rem->next;
    if (prev->next == NULL) ll->tail = prev;
    free(rem);
    if (err_code) *err_code = 0;
    return value;
}

void ll_clear(struct linked_list_t* ll)
{
    if (ll == NULL) return;
    struct node_t *it = ll->head;
    while (it)
    {
        struct node_t *next = it->next;
        free(it);
        it = next;
    }
    ll->head = NULL;
    ll->tail = NULL;
}

void ll_display(const struct linked_list_t* ll)
{
    if (ll == NULL || ll->head == NULL) return;
    const struct node_t *it = ll->head;
    while (it)
    {
        printf("%d ", it->data);
        it = it->next;
    }
}

