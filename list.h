
#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

struct list;

struct node {
        void* ptr;
        int data;
        struct list* lst;
};

struct list {
        struct node* head;
        struct node* tail;
};

struct list* list_init();
struct node* node_init(struct list* lst);

#ifdef __cplusplus
}
#endif

#endif
