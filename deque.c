#include "deque.h"

#include <stdlib.h>

Deque* Deque_Create(void)
{
    Deque* deque = malloc(sizeof(*deque));

    if (deque)
    {
        DoubleLinkedList_Init(&deque->list);
    }

    return deque;
}

void Deque_Clear(Deque* deque)
{
    if (deque)
    {
        DoubleLinkedList_Clear(&deque->list);
    }
}

void Deque_Delete(Deque* deque)
{
    Deque_Clear(deque);
    free(deque);
}

bool Deque_PushBack(Deque* deque, void* value)
{
    return deque && DoubleLinkedList_Add(&deque->list, value) != nullptr;
}

bool Deque_PushFront(Deque* deque, void* value)
{
    return deque && DoubleLinkedList_AddFirst(&deque->list, value) != nullptr;
}

void* Deque_PopBack(Deque* deque)
{
    return deque ? DoubleLinkedList_Remove(&deque->list) : nullptr;
}

void* Deque_PopFront(Deque* deque)
{
    return deque ? DoubleLinkedList_RemoveFirst(&deque->list) : nullptr;
}

void* Deque_PeekBack(const Deque* deque)
{
    return deque ? DoubleLinkedList_Last(&deque->list) : nullptr;
}

void* Deque_PeekFront(const Deque* deque)
{
    return deque ? DoubleLinkedList_First(&deque->list) : nullptr;
}

size_t Deque_Count(const Deque* deque)
{
    return deque ? deque->list.count : 0;
}
