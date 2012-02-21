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


int
node_insert(prev, next, this)
struct node* prev;
struct node* next;
struct node* this;
{
        if (this == NULL)
        {
                fprintf(stderr, "NULL POINTER!\n");
                exit(1);
        }
        ulong prev_next = (ulong)next;
        ulong prev_ptr = (prev) ? (ulong)prev->ptr ^ prev_next : 0;
        ulong prev_a = (ulong)prev;

        ulong next_prev = (ulong)prev;
        ulong next_ptr = (next) ? (ulong)next->ptr ^ next_prev : 0;
        ulong next_a = (ulong)next;

        ulong this_a = (ulong) this;

        this->ptr = (void*)(next_a ^ prev_a);
        prev_ptr ^= this_a;
        next_ptr ^= this_a;

        if (prev && prev->ptr != prev)
                prev->ptr = (void*)prev_ptr;
        else
                this->lst->head = this;
        if (next && next->ptr != next)
                next->ptr = (void*)next_ptr;
        else
                this->lst->tail = this;

        return 0;
}

int
node_add_tail(struct list* lst, struct node* this)
{
        if (lst->tail == NULL)
        {
                if (lst->head != NULL)
                {
                        fprintf(stderr, "List corrupted\n");
                        exit(1);
                }
                else
                {
                        lst->head = this;
                        lst->tail = this;
                        return 0;
                }
        }
        node_insert(lst->tail, NULL, this);
        return 0;
}

int node_add_head(struct list* lst, struct node* this)
{
        if (lst->head == NULL)
        {
                if (lst->tail != NULL)
                {
                        fprintf(stderr, "List corrupted\n");
                        exit(1);
                }
                else
                {
                        lst->head = this;
                        lst->tail = this;
                        return 0;
                }
        }
        node_insert(NULL, lst->head, this);
        return 0;
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