
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
int list_clean(struct list* lst);
int node_purge(struct node* this, struct node* prev);
int node_insert(struct node* prev, struct node* next, struct node* this);
int node_add_tail(struct list* lst, struct node* this);
int node_add_head(struct list* lst, struct node* this);
struct node* node_get_next(struct node* prev, struct node* this);
void debug_list(struct list* lst);
struct list* list_copy_list(struct list* parent, struct list* new);

#ifdef __cplusplus
}
#endif

#endif
