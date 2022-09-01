#include <stdio.h>

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

struct list
{
    int counter;
    struct node *head;
    struct node *tail;
};

void inserthead(struct list *list, int data)
{
    struct node *node;
    node = createnode(data);
    list->counter += 1;
    list->head = node;
    
    
}


struct node* createnode(int data)
{
    struct node *node;
    return node;
}

void printlist(struct list *list)
{
}

int main()
{
    struct list *list;
    for (int i = 0; i < 10; i++)
    {
        inserthead(list, (i + 3) / 2);
    }

    struct node n;
    n.data = 1;
    n.next =


    return 0;
}
