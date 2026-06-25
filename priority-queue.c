#include "priority-queue.h"

#include <stdlib.h>

#define PRIORITY_QUEUE_DEFAULT_CAPACITY 4

static int PriorityQueue_EnsureCapacity(PriorityQueue* queue, size_t required_capacity)
{
    if (!queue)
    {
        return 0;
    }

    if (queue->capacity >= required_capacity)
    {
        return 1;
    }

    size_t new_capacity = queue->capacity ? queue->capacity : PRIORITY_QUEUE_DEFAULT_CAPACITY;

    while (new_capacity < required_capacity)
    {
        new_capacity *= 2;
    }

    void** new_items = realloc(queue->items, new_capacity * sizeof(*new_items));

    if (!new_items)
    {
        return 0;
    }

    queue->items = new_items;
    queue->capacity = new_capacity;

    return 1;
}

static void PriorityQueue_Swap(void** left, void** right)
{
    void* temporary = *left;
    *left = *right;
    *right = temporary;
}

static void PriorityQueue_SiftUp(PriorityQueue* queue, size_t index)
{
    while (index > 0)
    {
        size_t parent_index = (index - 1) / 2;

        if (queue->compare(queue->items[index], queue->items[parent_index]) >= 0)
        {
            break;
        }

        PriorityQueue_Swap(&queue->items[index], &queue->items[parent_index]);
        index = parent_index;
    }
}

static void PriorityQueue_SiftDown(PriorityQueue* queue, size_t index)
{
    for (;;)
    {
        size_t left_child_index = index * 2 + 1;
        size_t right_child_index = index * 2 + 2;
        size_t smallest_index = index;

        if (left_child_index < queue->count &&
            queue->compare(queue->items[left_child_index], queue->items[smallest_index]) < 0)
        {
            smallest_index = left_child_index;
        }

        if (right_child_index < queue->count &&
            queue->compare(queue->items[right_child_index], queue->items[smallest_index]) < 0)
        {
            smallest_index = right_child_index;
        }

        if (smallest_index == index)
        {
            break;
        }

        PriorityQueue_Swap(&queue->items[index], &queue->items[smallest_index]);
        index = smallest_index;
    }
}

PriorityQueue* PriorityQueue_Create(PriorityQueueCompare compare)
{
    return PriorityQueue_CreateWithCapacity(compare, PRIORITY_QUEUE_DEFAULT_CAPACITY);
}

PriorityQueue* PriorityQueue_CreateWithCapacity(PriorityQueueCompare compare, size_t capacity)
{
    if (!compare)
    {
        return NULL;
    }

    PriorityQueue* queue = malloc(sizeof(*queue));

    if (!queue)
    {
        return NULL;
    }

    queue->items = NULL;
    queue->compare = compare;
    queue->count = 0;
    queue->capacity = 0;

    if (capacity && !PriorityQueue_EnsureCapacity(queue, capacity))
    {
        free(queue);
        return NULL;
    }

    return queue;
}

void PriorityQueue_Clear(PriorityQueue* queue)
{
    if (!queue)
    {
        return;
    }

    queue->count = 0;
}

void PriorityQueue_Delete(PriorityQueue* queue)
{
    if (!queue)
    {
        return;
    }

    free(queue->items);
    free(queue);
}

int PriorityQueue_Enqueue(PriorityQueue* queue, void* value)
{
    if (!queue || !PriorityQueue_EnsureCapacity(queue, queue->count + 1))
    {
        return 0;
    }

    queue->items[queue->count] = value;
    PriorityQueue_SiftUp(queue, queue->count);
    ++queue->count;

    return 1;
}

void* PriorityQueue_Peek(const PriorityQueue* queue)
{
    if (!queue || queue->count == 0)
    {
        return NULL;
    }

    return queue->items[0];
}

void* PriorityQueue_Dequeue(PriorityQueue* queue)
{
    if (!queue || queue->count == 0)
    {
        return NULL;
    }

    void* value = queue->items[0];
    --queue->count;

    if (queue->count > 0)
    {
        queue->items[0] = queue->items[queue->count];
        PriorityQueue_SiftDown(queue, 0);
    }

    return value;
}

size_t PriorityQueue_Count(const PriorityQueue* queue)
{
    if (!queue)
    {
        return 0;
    }

    return queue->count;
}

size_t PriorityQueue_Capacity(const PriorityQueue* queue)
{
    if (!queue)
    {
        return 0;
    }

    return queue->capacity;
}
