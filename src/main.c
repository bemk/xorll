#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/**
 * \fn main
 * \brief Entry point and test-suite for the linked-list
 * \param argc
 * \brief Number of arguments
 * \param argv
 * \brief array of arguments
 * \return Error code!
 */
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

/** \file */
