#pragma once

#include <stddef.h>

#include "double-linked-list.h"

// Double-ended queue over a doubly linked list; every operation is O(1).
typedef struct Deque
{
    DoubleLinkedList list;
} Deque;

[[nodiscard]] Deque* Deque_Create(void);
void Deque_Clear(Deque* deque);
void Deque_Delete(Deque* deque);

// Return false if the node could not be allocated.
bool Deque_PushBack(Deque* deque, void* value);
bool Deque_PushFront(Deque* deque, void* value);

// Remove and return a value from either end (nullptr when empty).
void* Deque_PopBack(Deque* deque);
void* Deque_PopFront(Deque* deque);

// The value at either end without removing it (nullptr when empty).
void* Deque_PeekBack(const Deque* deque);
void* Deque_PeekFront(const Deque* deque);

size_t Deque_Count(const Deque* deque);
