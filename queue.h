#pragma once

#include <stddef.h>

#include "double-linked-list.h"

// FIFO container over a doubly linked list; every operation is O(1).
typedef struct Queue
{
    DoubleLinkedList list;
} Queue;

[[nodiscard]] Queue* Queue_Create(void);
void Queue_Clear(Queue* queue);
void Queue_Delete(Queue* queue);

// Returns false if the node could not be allocated.
bool Queue_Enqueue(Queue* queue, void* value);
// Removes and returns the oldest value (nullptr when empty).
void* Queue_Dequeue(Queue* queue);
// The oldest value without removing it (nullptr when empty).
void* Queue_Peek(const Queue* queue);

size_t Queue_Count(const Queue* queue);
