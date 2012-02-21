#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

struct list*
list_copy_list(struct list* parent, struct list* new)
{
        if (new == NULL || parent == NULL || parent->head == NULL)
        {
                fprintf(stderr, "NULL POINTER!\n");
                exit(1);
        }

        struct node* carriage = parent->head;
        struct node* last = NULL;
        struct node* next = NULL;
        struct node* tmp = NULL;

        while(carriage != NULL)
        {
                tmp = node_init(new);
                memcpy(tmp, carriage, sizeof(*tmp));
                tmp->ptr = NULL;
                tmp->lst = new;

                node_add_tail(new, tmp);

                next = node_get_next(last, carriage);
                last = carriage;
                carriage = next;
        }

        return new;
}

int main(int argc, char** argv)
{
        struct list* lst = list_init();
        struct list* lst2 = list_init();
        struct node* n1 = node_init(lst);
        struct node* n2 = node_init(lst);
        struct node* n3 = node_init(lst);

        memset(n1, 0, sizeof(*n1));
        memset(n2, 0, sizeof(*n2));
        memset(n3, 0, sizeof(*n3));

        n1->ptr = n2;
        n2->ptr = n1;

        n1->lst = lst;
        n2->lst = lst;
        n3->lst = lst;

        n1->data = 0xC0DEBABE;
        n2->data = 0xDEADBEEF;
        n3->data = 0xCAFEBEA8;

        lst->head = n1;
        lst->tail = n2;

        debug_list(lst);
        node_add_tail(lst, n3);
        debug_list(lst);
        list_copy_list(lst, lst2);
        debug_list(lst2);
        node_purge(n3, n2);
        debug_list(lst);
        list_clean(lst);

        return EXIT_SUCCESS;
}