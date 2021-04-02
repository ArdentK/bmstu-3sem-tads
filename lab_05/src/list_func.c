#define __USE_MINGW_ANSI_STDIO 1

#include "list_func.h"

node_t *node_create(request_t *data)
{
    node_t *buf = malloc(sizeof(node_t));

    if (buf)
    {
        buf->data = *data;
        buf->next = NULL;
    }

    return buf;
}

void push_queue_list(request_t *new_elem, queue_list_t *list)
{
    node_t *new_tail = node_create(new_elem);

    if (list->tail)
    {
        list->tail->next = new_tail;
        list->tail = list->tail->next;
    }
    else
    {
        list->tail = new_tail;
        list->head = list->tail;
    }

    list->cur_len += 1;
}

void node_free(node_t *elem)
{
    free(elem);
}

void free_list(node_t *head)
{
    while (head)
    {
        node_t *next = head->next;
        node_free(head);
        head = next;
    }
}

queue_list_t *create_queue_list()
{
    queue_list_t *queue = malloc(sizeof(queue_list_t));
    queue->head = NULL;
    queue->tail = NULL;
    queue->cur_len = 0;

    return queue;
}

void make_empty_queue_list(queue_list_t *list)
{
    free_list(list->head);
    list->head = NULL;
    list->tail = NULL;
    list->cur_len = 0;
}

void free_queue_list(queue_list_t *list)
{
    free_list(list->head);
    free(list);
}

int is_empty_queue_list(queue_list_t *list)
{
    int err = !(list->head);

    return err;
}

int pop_queue_list(queue_list_t *list, request_t *item)
{
    if (is_empty_queue_list(list))
        return 0;

    node_t *del = list->head;

    if (item)
        *item = list->head->data;

    if (!(list->head = list->head->next))
        list->tail = NULL;

    node_free(del);
    list->cur_len -= 1;

    return 1;
}

size_t get_queue_list_memory_size(size_t len)
{
    size_t mem = sizeof(queue_list_t *) + sizeof(queue_list_t) + len * sizeof(node_t);

    return mem;
}