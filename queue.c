#include "queue.h"

#include <stdlib.h>

Queue* Queue_Create(void)
{
    Queue* queue = malloc(sizeof(*queue));

    if (!queue)
    {
        return NULL;
    }

    queue->list = DoubleLinkedList_Create();

    if (!queue->list)
    {
        free(queue);
        return NULL;
    }

    return queue;
}

void Queue_Delete(Queue* queue)
{
    if (!queue)
    {
        return;
    }

    DoubleLinkedList_Delete(queue->list);
    free(queue);
}

void Queue_Enqueue(Queue* queue, void* value)
{
    if (!queue)
    {
        return;
    }

    DoubleLinkedList_Add(queue->list, value);
}

void* Queue_Dequeue(Queue* queue)
{
    if (!queue)
    {
        return NULL;
    }

    return DoubleLinkedList_RemoveFirst(queue->list);
}

size_t Queue_Count(const Queue* queue)
{
    if (!queue)
    {
        return 0;
    }

    return DoubleLinkedList_Count(queue->list);
}
