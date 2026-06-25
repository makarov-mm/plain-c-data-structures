#ifndef QUEUE
#define QUEUE

#include <stddef.h>
#include "double-linked-list.h"

typedef struct Queue {
    struct DoubleLinkedList* list;
} Queue;

extern Queue* Queue_Create(void);
extern void Queue_Delete(Queue* queue);

extern void Queue_Enqueue(Queue* queue, void* value);
extern void* Queue_Dequeue(Queue* queue);

extern size_t Queue_Count(const Queue* queue);

#endif
