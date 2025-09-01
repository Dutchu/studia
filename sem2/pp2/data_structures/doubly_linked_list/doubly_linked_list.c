// Doubly linked list implementation
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

static struct node_t* make_node(int value)
{
    struct node_t *n = (struct node_t*)malloc(sizeof(struct node_t));
    if (n == NULL) return NULL;
    n->data = value;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

struct doubly_linked_list_t* dll_create()
{
    struct doubly_linked_list_t *dll = (struct doubly_linked_list_t*)malloc(sizeof(struct doubly_linked_list_t));
    if (dll == NULL) return NULL;
    dll->head = NULL;
    dll->tail = NULL;
    return dll;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value)
{
    if (dll == NULL) return 1;
    struct node_t *n = make_node(value);
    if (n == NULL) return 2;
    if (dll->tail == NULL)
    {
        dll->head = n;
        dll->tail = n;
    }
    else
    {
        n->prev = dll->tail;
        dll->tail->next = n;
        dll->tail = n;
    }
    return 0;
}

int dll_push_front(struct doubly_linked_list_t* dll, int value)
{
    if (dll == NULL) return 1;
    struct node_t *n = make_node(value);
    if (n == NULL) return 2;
    if (dll->head == NULL)
    {
        dll->head = n;
        dll->tail = n;
    }
    else
    {
        n->next = dll->head;
        dll->head->prev = n;
        dll->head = n;
    }
    return 0;
}

int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code)
{
    if (dll == NULL || dll->head == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    struct node_t *n = dll->head;
    int value = n->data;
    dll->head = n->next;
    if (dll->head)
        dll->head->prev = NULL;
    else
        dll->tail = NULL;
    free(n);
    if (err_code) *err_code = 0;
    return value;
}

int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code)
{
    if (dll == NULL || dll->tail == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    struct node_t *n = dll->tail;
    int value = n->data;
    dll->tail = n->prev;
    if (dll->tail)
        dll->tail->next = NULL;
    else
        dll->head = NULL;
    free(n);
    if (err_code) *err_code = 0;
    return value;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code)
{
    if (dll == NULL || dll->tail == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    if (err_code) *err_code = 0;
    return dll->tail->data;
}

int dll_front(const struct doubly_linked_list_t* dll, int *err_code)
{
    if (dll == NULL || dll->head == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    if (err_code) *err_code = 0;
    return dll->head->data;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll)
{
    if (dll == NULL) return NULL;
    return dll->head;
}

struct node_t* dll_end(struct doubly_linked_list_t* dll)
{
    if (dll == NULL) return NULL;
    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t* dll)
{
    if (dll == NULL) return -1;
    int count = 0;
    const struct node_t *it = dll->head;
    while (it)
    {
        count += 1;
        it = it->next;
    }
    return count;
}

int dll_is_empty(const struct doubly_linked_list_t* dll)
{
    if (dll == NULL) return -1;
    return dll->head == NULL ? 1 : 0;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code)
{
    if (dll == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    const struct node_t *it = dll->head;
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

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value)
{
    if (dll == NULL) return 1;
    int sz = dll_size(dll);
    if (sz < 0) return 1;
    if ((unsigned int)sz < index) return 1;

    if (index == 0)
        return dll_push_front(dll, value);
    if ((unsigned int)sz == index)
        return dll_push_back(dll, value);

    struct node_t *it = dll->head;
    unsigned int i = 0;
    while (it && i < index)
    {
        it = it->next;
        i += 1;
    }
    if (it == NULL) return 1;

    struct node_t *n = make_node(value);
    if (n == NULL) return 2;

    n->prev = it->prev;
    n->next = it;
    if (it->prev) it->prev->next = n;
    it->prev = n;
    if (index == 0) dll->head = n; // redundant safety
    return 0;
}

int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code)
{
    if (dll == NULL)
    {
        if (err_code) *err_code = 1;
        return 0;
    }
    int sz = dll_size(dll);
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
        return dll_pop_front(dll, err_code);
    if ((unsigned int)(sz - 1) == index)
        return dll_pop_back(dll, err_code);

    struct node_t *it = dll->head;
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
    int value = it->data;
    if (it->prev) it->prev->next = it->next;
    if (it->next) it->next->prev = it->prev;
    free(it);
    if (err_code) *err_code = 0;
    return value;
}

void dll_clear(struct doubly_linked_list_t* dll)
{
    if (dll == NULL) return;
    struct node_t *it = dll->head;
    while (it)
    {
        struct node_t *next = it->next;
        free(it);
        it = next;
    }
    dll->head = NULL;
    dll->tail = NULL;
}

void dll_display(const struct doubly_linked_list_t* dll)
{
    if (dll == NULL || dll->head == NULL) return;
    const struct node_t *it = dll->head;
    while (it)
    {
        printf("%d ", it->data);
        it = it->next;
    }
}

void dll_display_reverse(const struct doubly_linked_list_t* dll)
{
    if (dll == NULL || dll->tail == NULL) return;
    const struct node_t *it = dll->tail;
    while (it)
    {
        printf("%d ", it->data);
        it = it->prev;
    }
}

