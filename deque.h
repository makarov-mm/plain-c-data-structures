#ifndef DEQUE
#define DEQUE

#include <stddef.h>
#include "double-linked-list.h"

typedef struct Deque {
    struct DoubleLinkedList* list;
} Deque;

extern Deque* Deque_Create(void);
extern void Deque_Delete(Deque* deque);

extern void Deque_PushBack(Deque* deque, void* value);
extern void Deque_PushFront(Deque* deque, void* value);

extern void* Deque_PopBack(Deque* deque);
extern void* Deque_PopFront(Deque* deque);

extern size_t Deque_Count(const Deque* deque);

#endif
