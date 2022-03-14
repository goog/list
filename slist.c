#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "slist.h"



typedef struct
{
    memory_allocate malloc;
    memory_free free;
} allocator_interface_t;

static allocator_interface_t interface = {0};


void list_set_mem_api(memory_allocate alloc_func, memory_free free_func)
{
    if(alloc_func == NULL || free_func == NULL)
    {
        // set default alloc function
        interface.malloc = malloc;
        interface.free = free;
    }
    else
    {
        interface.malloc = alloc_func;
        interface.free = free_func;
    }
   
}


int list_push(slist_t *list, void *data)
{
    if(list == NULL)
    {
        return -1;
    }
    
    slist_node_t *node = interface.malloc(sizeof(slist_node_t));
    if(node == NULL)
    {
        fprintf(stderr, "interface.malloc fail\n");
        return -1;
    }

    node->data = data;
    node->next = *list;
    *list = node;  // assign node to head pointer
    
    return 0;
}



slist_node_t *list_pop(slist_t *list)
{

    slist_node_t *prev = NULL, *cur = NULL, *next = NULL;
    if(list == NULL)
    {
        return NULL;
    }
    
    cur = *list;
    while(cur)
    {
        next = cur->next;
        if(next == NULL)
        {
            // reach the last node
            break;
        }

        prev = cur;
        cur = next;
    }

    // remove from link list
    if(prev != NULL)
    {
        prev->next = next;
    }

    if(cur == *list)  // only one node, change list head value
    {
        *list = NULL;
    }
    
    return cur;
}

int list_get_length(slist_t list)
{
    int length = 0;

    while(list)
    {
        length++;
        list = list->next;
    }

    return length;
}


void list_reverse(slist_t *list)
{

    if(list == NULL)
    {
        return;
    }
    
    slist_node_t *prev = NULL;
    slist_node_t *cur = *list;
    slist_node_t *next = NULL;
    while(cur)
    {
        next = cur->next;
        // begin to reverse cur node
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    *list = prev;
}


void *list_get_nth_data(slist_t list, unsigned int n)
{

    while(n-- > 0 && list)
    {
        list = list->next;
    }

    if(list)
        return list->data;
    else
        return NULL;
}


// cant free node in callback function
void list_foreach(slist_t list, iterator_func user_callback, void *user_data)
{
    if(user_callback == NULL)
    {
        return;
    }

    while(list)
    {
        user_callback(list, user_data);
        list = list->next;
    }
    
}


void list_free_node(slist_node_t *node, free_data_func func)
{
    if(node == NULL)
    {
        return;
    }

    if(func != NULL)
    {
        func(node->data);
    }
    
    free(node);
}


void list_destory(slist_t list, free_data_func func)
{
    while(list)
    {
        slist_t next = list->next;
        list_free_node(list, func);
        list = next;
    }

}

