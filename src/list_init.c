#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

/**
 * \fn list_init
 * \brief Initialise a new list
 * \return The newly created list element
 */
struct list*
list_init()
{
        struct list* lst = malloc(sizeof(*lst));
        if (lst == NULL)
        {
                fprintf(stderr, "OUT OF MEMORY!\n");
                exit(1);
        }
        memset(lst, 0, sizeof(*lst));
        return lst;
}

/**
 * \fn node_init
 * \brief Create a new node
 * \param lst
 * \brief The list of which the node will eventually be part
 * \return The newly created node
 */
struct node*
node_init(struct list* lst)
{
        struct node* n = malloc(sizeof(*n));
        if (n == NULL)
        {
                fprintf(stderr, "OUT OF MEMORY!\n");
                exit(1);
        }
        memset(n, 0, sizeof(*n));
        n->lst = lst;
        return n;
}
