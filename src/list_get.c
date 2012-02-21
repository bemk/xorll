#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
 * \fn node_get_next
 * \brief Return the next node from this
 * \param prev
 * \brief The previous pointer to be xor'd out of this->ptr
 * \param this
 * \brief The node holding the actual pointer
 * \return The next node pointed to by this as viewed by previous
 */
struct node*
node_get_next(struct node* prev, struct node* this)
{
        ulong l_prev = (ulong)prev;
        ulong l_this = (ulong)this->ptr;

        ulong l_next = l_prev ^ l_this;

        return (struct node*)l_next;
}

/**
 * \fn debug_list
 * \brief Dump all the nodes in the current list on stdout
 * \param lst
 * \brief the list to dump
 */
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

/** \file */
