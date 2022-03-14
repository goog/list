#include <stdio.h>
#include <stdlib.h>
#include "slist.h"


void free_data(void *p)
{
    if(p)
    {
        free(p);
    }
}


void user_cb(void *node, void *user_data)
{

    if(node)
    {
        slist_node_t * p = (slist_node_t *)node;
        int *data = p->data;
        printf("foreach node data %d\n", *data);
    }

}


int main()
{

    list_set_mem_api(NULL, NULL);

    slist_t head = NULL;
    int *p1 = malloc(sizeof(int));
    int *p2 = malloc(sizeof(int));
    int *p3 = malloc(sizeof(int));
    int *p4 = malloc(sizeof(int));
    // skip check null
    *p1 = 8;
    *p2 = 9;
    *p3 = 18;
    *p4 = 48;
    list_push(&head, p1);
    list_push(&head, p2);
    list_push(&head, p3);
    list_push(&head, p4);
    printf("list length %d\n", list_get_length(head));
    list_foreach(head, user_cb, NULL);
    printf("foreach end\n");

    printf("after reverse\n");
    list_reverse(&head);
    list_foreach(head, user_cb, NULL);
    
    
    int *data = list_get_nth_data(head, 4);
    printf("get data %p\n", data);
    slist_node_t *temp = list_pop(&head);
    printf("poped data %d\n", *(int *)(temp->data));
    list_free_node(temp, free_data);

    temp = list_pop(&head);
    printf("poped data %d\n", *(int *)(temp->data));
    printf("list length %d\n", list_get_length(head));
    list_free_node(temp, free_data);

    list_destory(head, free_data);
}
