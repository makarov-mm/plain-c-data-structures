#include "priority-queue.h"

#include <stdlib.h>

#include "capacity.h"

enum { kDefaultCapacity = 4 };

// Moves the hole at `index` up until `value` fits, then drops it in.
static void SiftUp(PriorityQueue* queue, size_t index, void* value)
{
    while (index > 0)
    {
        size_t parent = (index - 1) / 2;

        if (queue->compare(value, queue->items[parent]) >= 0)
        {
            break;
        }

        queue->items[index] = queue->items[parent];
        index = parent;
    }

    queue->items[index] = value;
}

// Moves the hole at `index` down until `value` fits, then drops it in.
static void SiftDown(PriorityQueue* queue, size_t index, void* value)
{
    for (;;)
    {
        size_t child = index * 2 + 1;

        if (child >= queue->count)
        {
            break;
        }

        if (child + 1 < queue->count && queue->compare(queue->items[child + 1], queue->items[child]) < 0)
        {
            ++child;
        }

        if (queue->compare(queue->items[child], value) >= 0)
        {
            break;
        }

        queue->items[index] = queue->items[child];
        index = child;
    }

    queue->items[index] = value;
}

PriorityQueue* PriorityQueue_Create(PriorityQueueCompare compare)
{
    return PriorityQueue_CreateWithCapacity(compare, kDefaultCapacity);
}

PriorityQueue* PriorityQueue_CreateWithCapacity(PriorityQueueCompare compare, size_t capacity)
{
    if (!compare)
    {
        return nullptr;
    }

    PriorityQueue* queue = malloc(sizeof(*queue));

    if (!queue)
    {
        return nullptr;
    }

    *queue = (PriorityQueue){.compare = compare};

    if (!PriorityQueue_Reserve(queue, capacity))
    {
        free(queue);
        return nullptr;
    }

    return queue;
}

void PriorityQueue_Clear(PriorityQueue* queue)
{
    if (queue)
    {
        queue->count = 0;
    }
}

void PriorityQueue_Delete(PriorityQueue* queue)
{
    if (queue)
    {
        free(queue->items);
        free(queue);
    }
}

bool PriorityQueue_Reserve(PriorityQueue* queue, size_t capacity)
{
    return queue && GrowPointerArray(&queue->items, &queue->capacity, capacity, kDefaultCapacity);
}

bool PriorityQueue_Enqueue(PriorityQueue* queue, void* value)
{
    if (!queue || !PriorityQueue_Reserve(queue, queue->count + 1))
    {
        return false;
    }

    SiftUp(queue, queue->count++, value);

    return true;
}

void* PriorityQueue_Peek(const PriorityQueue* queue)
{
    return queue && queue->count ? queue->items[0] : nullptr;
}

void* PriorityQueue_Dequeue(PriorityQueue* queue)
{
    if (!queue || queue->count == 0)
    {
        return nullptr;
    }

    void* value = queue->items[0];
    --queue->count;

    if (queue->count > 0)
    {
        SiftDown(queue, 0, queue->items[queue->count]);
    }

    return value;
}

size_t PriorityQueue_Count(const PriorityQueue* queue)
{
    return queue ? queue->count : 0;
}

size_t PriorityQueue_Capacity(const PriorityQueue* queue)
{
    return queue ? queue->capacity : 0;
}
