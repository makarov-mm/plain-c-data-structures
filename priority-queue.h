#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <stddef.h>

typedef int (*PriorityQueueCompare)(const void* left, const void* right);

typedef struct PriorityQueue {
    void** items;
    PriorityQueueCompare compare;
    size_t count;
    size_t capacity;
} PriorityQueue;

extern PriorityQueue* PriorityQueue_Create(PriorityQueueCompare compare);
extern PriorityQueue* PriorityQueue_CreateWithCapacity(
    PriorityQueueCompare compare,
    size_t capacity
);
extern void PriorityQueue_Clear(PriorityQueue* queue);
extern void PriorityQueue_Delete(PriorityQueue* queue);

extern int PriorityQueue_Enqueue(PriorityQueue* queue, void* value);
extern void* PriorityQueue_Peek(const PriorityQueue* queue);
extern void* PriorityQueue_Dequeue(PriorityQueue* queue);

extern size_t PriorityQueue_Count(const PriorityQueue* queue);
extern size_t PriorityQueue_Capacity(const PriorityQueue* queue);

#endif
