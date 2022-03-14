#ifndef __MY_SLISH_H
#define __MY_SLISH_H


// define function type
typedef void* (*memory_allocate) (size_t size);
typedef void  (*memory_free)     (void *p);
typedef void (*free_data_func)     (void *data);
typedef void  (*iterator_func)     (void *node, void *user_data);

typedef struct list_node
{
    void *data;  // custom data pointer
    struct list_node *next;
} *slist_t, slist_node_t;



void list_set_mem_api(memory_allocate alloc_func, memory_free free_func);

int list_push(slist_t *list, void *data);

// get from tail 
slist_node_t *list_pop(slist_t *list);

void list_foreach(slist_t list, iterator_func user_callback, void *user_data);

void *list_get_nth_data(slist_t list, unsigned int n);

int list_get_length(slist_t list);

void list_free_node(slist_node_t *node, free_data_func func);

void list_reverse(slist_t *list);

void list_destory(slist_t list, free_data_func func);
#endif