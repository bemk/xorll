#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct node*
node_get_next(struct node* prev, struct node* this)
{
        ulong l_prev = (ulong)prev;
        ulong l_this = (ulong)this->ptr;

        ulong l_next = l_prev ^ l_this;

        return (struct node*)l_next;
}

void debug_list(struct list* lst)
{
        struct node* carriage = lst->head;
        struct node* last = NULL;
        struct node* new;
        int i = 0;

        while (carriage != NULL)
        {
                fprintf(stdout, "%d) Current data %X\n", i, carriage->data);
                new = node_get_next(last, carriage);
                last = carriage;
                carriage = new;
                i++;
        }
        fprintf(stdout, "\n");
}
