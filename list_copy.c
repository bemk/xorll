#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

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
