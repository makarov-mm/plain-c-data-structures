#include "queue.h"

#include <stdlib.h>

Queue* Queue_Create(void)
{
    Queue* queue = malloc(sizeof(*queue));

    if (queue)
    {
        DoubleLinkedList_Init(&queue->list);
    }

    return queue;
}

void Queue_Clear(Queue* queue)
{
    if (queue)
    {
        DoubleLinkedList_Clear(&queue->list);
    }
}

void Queue_Delete(Queue* queue)
{
    Queue_Clear(queue);
    free(queue);
}

bool Queue_Enqueue(Queue* queue, void* value)
{
    return queue && DoubleLinkedList_Add(&queue->list, value) != nullptr;
}

void* Queue_Dequeue(Queue* queue)
{
    return queue ? DoubleLinkedList_RemoveFirst(&queue->list) : nullptr;
}

void* Queue_Peek(const Queue* queue)
{
    return queue ? DoubleLinkedList_First(&queue->list) : nullptr;
}

size_t Queue_Count(const Queue* queue)
{
    return queue ? queue->list.count : 0;
}
