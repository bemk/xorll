#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

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
