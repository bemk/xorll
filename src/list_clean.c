#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/**
 * \fn list_clean
 * \brief Clean up the entire list
 * \param lst
 * \brief The list to clean up
 * \return An error code
 */
int
list_clean(struct list* lst)
{
        while (lst->head != NULL)
                node_purge(lst->head, NULL);

        free(lst);
        return 0;
}

/**
 * \fn node_purge
 * \brief Purge a node from the list
 * \param this
 * \brief The node to purge
 * \param prev
 * \brief The node before the this node
 * \return Error code
 */
int
node_purge(this, prev)
struct node* this;
struct node* prev;
{
        if (this == NULL)
        {
                fprintf(stderr, "NULL PTR");
                exit(1);
        }
        ulong this_prev = (ulong)prev;
        ulong this_next = (ulong)this->ptr ^ this_prev;
        ulong this_a = (ulong)this;

        struct node* next = (void*)this_next;

        if (this->ptr == NULL)
        {
                this->lst->head = NULL;
                this->lst->tail = NULL;
                free(this);
                return 0;
        }

        ulong prev_ptr = ((prev) ? (ulong)prev->ptr : 0) ^ this_a ^ (ulong)next;
        ulong next_ptr = ((next) ? (ulong)next->ptr : 0) ^ this_a ^ (ulong)prev;

        if (next && next_ptr != (ulong)next)
                next->ptr = (void*)next_ptr;
        else if (next)
                this->lst->tail = next;
        else
                this->lst->tail = prev;

        if (prev && prev_ptr != (ulong)prev)
                prev->ptr = (void*)prev_ptr;
        else if (prev)
                this->lst->head = prev;
        else
                this->lst->head = next;

        free(this);

        return 0;
}
