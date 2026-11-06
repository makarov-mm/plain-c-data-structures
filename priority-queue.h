#pragma once

#include <stdbool.h>
#include <stddef.h>

// Returns < 0, 0 or > 0 like strcmp. Values that compare smaller come out first.
typedef int (*PriorityQueueCompare)(const void* left, const void* right);

// A min-priority queue: a binary heap of void* values. The heap buffer is
// owned; values are not.
typedef struct PriorityQueue
{
    void** items;
    PriorityQueueCompare compare;
    size_t count;
    size_t capacity;
} PriorityQueue;

[[nodiscard]] PriorityQueue* PriorityQueue_Create(PriorityQueueCompare compare);
[[nodiscard]] PriorityQueue* PriorityQueue_CreateWithCapacity(PriorityQueueCompare compare, size_t capacity);
void PriorityQueue_Clear(PriorityQueue* queue);
void PriorityQueue_Delete(PriorityQueue* queue);

// Grows the buffer to hold at least `capacity` values; false on failure.
bool PriorityQueue_Reserve(PriorityQueue* queue, size_t capacity);

// O(log n); false if memory ran out.
bool PriorityQueue_Enqueue(PriorityQueue* queue, void* value);
// The smallest value without removing it (nullptr when empty), O(1).
void* PriorityQueue_Peek(const PriorityQueue* queue);
// Removes and returns the smallest value (nullptr when empty), O(log n).
void* PriorityQueue_Dequeue(PriorityQueue* queue);

size_t PriorityQueue_Count(const PriorityQueue* queue);
size_t PriorityQueue_Capacity(const PriorityQueue* queue);
