#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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