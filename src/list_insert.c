#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
 * \fn node_insert
 * \brief Insert a node into the list between two other nodes
 * \param prev
 * \brief The node to go before the inserted node
 * \param next
 * \brief The node to go after the inserted node
 * \param this
 * \brief The node to be inserted
 * \warning The prev and next nodes MUST be adjacent in the list
 * \return Error code
 */
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

/**
 * \fn node_add_tail
 * \brief Add a node to the end of the list
 * \param lst
 * \brief The list to insert the node into
 * \param this
 * \brief the node to be inserted
 * \return Error code
 */
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

/**
 * \fn node_add_head
 * \brief Add a node to the head of the list
 * \param lst
 * \brief The list ot insert the node into
 * \param this
 * \brief The node to be inserted
 * \return Error code
 */
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

/** \file */
