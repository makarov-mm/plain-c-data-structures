#include "deque.h"

#include <stdlib.h>

Deque* Deque_Create(void)
{
    Deque* deque = malloc(sizeof(*deque));

    if (!deque)
    {
        return NULL;
    }

    deque->list = DoubleLinkedList_Create();

    if (!deque->list)
    {
        free(deque);
        return NULL;
    }

    return deque;
}

void Deque_Delete(Deque* deque)
{
    if (!deque)
    {
        return;
    }

    DoubleLinkedList_Delete(deque->list);
    free(deque);
}

void Deque_PushBack(Deque* deque, void* value)
{
    if (!deque)
    {
        return;
    }

    DoubleLinkedList_Add(deque->list, value);
}

void Deque_PushFront(Deque* deque, void* value)
{
    if (!deque)
    {
        return;
    }

    DoubleLinkedList_AddFirst(deque->list, value);
}

void* Deque_PopBack(Deque* deque)
{
    if (!deque)
    {
        return NULL;
    }

    return DoubleLinkedList_Remove(deque->list);
}

void* Deque_PopFront(Deque* deque)
{
    if (!deque)
    {
        return NULL;
    }

    return DoubleLinkedList_RemoveFirst(deque->list);
}

size_t Deque_Count(const Deque* deque)
{
    if (!deque)
    {
        return 0;
    }

    return DoubleLinkedList_Count(deque->list);
}
