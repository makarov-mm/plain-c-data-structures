#include "double-linked-list.h"

#include <stdlib.h>

// Links a fresh node between `prev` and `next` (either may be null).
static DoubleLinkedListNode* LinkNode(DoubleLinkedList* list, DoubleLinkedListNode* prev, DoubleLinkedListNode* next,
                                      void* value)
{
    DoubleLinkedListNode* node = malloc(sizeof(*node));

    if (!node)
    {
        return nullptr;
    }

    node->value = value;
    node->prev = prev;
    node->next = next;

    if (prev)
    {
        prev->next = node;
    }
    else
    {
        list->head = node;
    }

    if (next)
    {
        next->prev = node;
    }
    else
    {
        list->tail = node;
    }

    ++list->count;

    return node;
}

DoubleLinkedList* DoubleLinkedList_Create(void)
{
    DoubleLinkedList* list = malloc(sizeof(*list));

    if (list)
    {
        DoubleLinkedList_Init(list);
    }

    return list;
}

void DoubleLinkedList_Init(DoubleLinkedList* list)
{
    if (list)
    {
        *list = (DoubleLinkedList){};
    }
}

void DoubleLinkedList_Clear(DoubleLinkedList* list)
{
    if (!list)
    {
        return;
    }

    DoubleLinkedListNode* current = list->head;

    while (current)
    {
        DoubleLinkedListNode* next = current->next;
        free(current);
        current = next;
    }

    *list = (DoubleLinkedList){};
}

void DoubleLinkedList_Delete(DoubleLinkedList* list)
{
    DoubleLinkedList_Clear(list);
    free(list);
}

DoubleLinkedListNode* DoubleLinkedList_Add(DoubleLinkedList* list, void* value)
{
    return list ? LinkNode(list, list->tail, nullptr, value) : nullptr;
}

DoubleLinkedListNode* DoubleLinkedList_AddFirst(DoubleLinkedList* list, void* value)
{
    return list ? LinkNode(list, nullptr, list->head, value) : nullptr;
}

DoubleLinkedListNode* DoubleLinkedList_InsertAfter(DoubleLinkedList* list, DoubleLinkedListNode* target, void* value)
{
    return list && target ? LinkNode(list, target, target->next, value) : nullptr;
}

DoubleLinkedListNode* DoubleLinkedList_InsertBefore(DoubleLinkedList* list, DoubleLinkedListNode* target, void* value)
{
    return list && target ? LinkNode(list, target->prev, target, value) : nullptr;
}

void* DoubleLinkedList_RemoveNode(DoubleLinkedList* list, DoubleLinkedListNode* node)
{
    if (!list || !node)
    {
        return nullptr;
    }

    if (node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        list->head = node->next;
    }

    if (node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        list->tail = node->prev;
    }

    void* value = node->value;
    free(node);
    --list->count;

    return value;
}

void* DoubleLinkedList_Remove(DoubleLinkedList* list)
{
    return list ? DoubleLinkedList_RemoveNode(list, list->tail) : nullptr;
}

void* DoubleLinkedList_RemoveFirst(DoubleLinkedList* list)
{
    return list ? DoubleLinkedList_RemoveNode(list, list->head) : nullptr;
}

void* DoubleLinkedList_Last(const DoubleLinkedList* list)
{
    return list && list->tail ? list->tail->value : nullptr;
}

void* DoubleLinkedList_First(const DoubleLinkedList* list)
{
    return list && list->head ? list->head->value : nullptr;
}

void DoubleLinkedList_Foreach(const DoubleLinkedList* list, DoubleLinkedListCallback callback, void* context)
{
    if (!list || !callback)
    {
        return;
    }

    for (DoubleLinkedListNode* node = list->head; node; node = node->next)
    {
        callback(node->value, context);
    }
}

void DoubleLinkedList_ForeachReverse(const DoubleLinkedList* list, DoubleLinkedListCallback callback, void* context)
{
    if (!list || !callback)
    {
        return;
    }

    for (DoubleLinkedListNode* node = list->tail; node; node = node->prev)
    {
        callback(node->value, context);
    }
}

size_t DoubleLinkedList_Count(const DoubleLinkedList* list)
{
    return list ? list->count : 0;
}
