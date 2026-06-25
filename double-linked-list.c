#include "double-linked-list.h"

#include <stdlib.h>

DoubleLinkedList* DoubleLinkedList_Create(void)
{
    DoubleLinkedList* list = malloc(sizeof(*list));

    if (!list)
    {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
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

    list->head = NULL;
    list->tail = NULL;
}

void DoubleLinkedList_Delete(DoubleLinkedList* list)
{
    if (!list)
    {
        return;
    }

    DoubleLinkedList_Clear(list);
    free(list);
}

void DoubleLinkedList_Foreach(DoubleLinkedList* list, void (*callback)(void* value))
{
    if (!list || !callback)
    {
        return;
    }

    DoubleLinkedListNode* current = list->head;

    while (current)
    {
        callback(current->value);
        current = current->next;
    }
}

void DoubleLinkedList_ForeachReverse(DoubleLinkedList* list, void (*callback)(void* value))
{
    if (!list || !callback)
    {
        return;
    }

    DoubleLinkedListNode* current = list->tail;

    while (current)
    {
        callback(current->value);
        current = current->prev;
    }
}

DoubleLinkedListNode* DoubleLinkedList_Add(DoubleLinkedList* list, void* value)
{
    if (!list)
    {
        return NULL;
    }

    DoubleLinkedListNode* node = malloc(sizeof(*node));

    if (!node)
    {
        return NULL;
    }

    node->next = NULL;
    node->prev = list->tail;
    node->value = value;

    if (!list->tail)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }

    return node;
}

DoubleLinkedListNode* DoubleLinkedList_AddFirst(DoubleLinkedList* list, void* value)
{
    if (!list)
    {
        return NULL;
    }

    DoubleLinkedListNode* node = malloc(sizeof(*node));

    if (!node)
    {
        return NULL;
    }

    node->next = list->head;
    node->prev = NULL;
    node->value = value;

    if (list->head)
    {
        list->head->prev = node;
    }
    else
    {
        list->tail = node;
    }

    list->head = node;

    return node;
}

void* DoubleLinkedList_Remove(DoubleLinkedList* list)
{
    if (!list || !list->tail)
    {
        return NULL;
    }

    DoubleLinkedListNode* old_tail = list->tail;
    void* value = old_tail->value;

    list->tail = old_tail->prev;

    if (list->tail)
    {
        list->tail->next = NULL;
    }
    else
    {
        list->head = NULL;
    }

    free(old_tail);
    return value;
}

void* DoubleLinkedList_RemoveFirst(DoubleLinkedList* list)
{
    if (!list || !list->head)
    {
        return NULL;
    }

    DoubleLinkedListNode* old_head = list->head;
    void* value = old_head->value;

    list->head = old_head->next;

    if (list->head)
    {
        list->head->prev = NULL;
    }
    else
    {
        list->tail = NULL;
    }

    free(old_head);
    return value;
}

DoubleLinkedListNode* DoubleLinkedList_InsertAfter(
    DoubleLinkedList* list,
    DoubleLinkedListNode* target,
    void* value)
{
    if (!list || !target)
    {
        return NULL;
    }

    DoubleLinkedListNode* node = malloc(sizeof(*node));

    if (!node)
    {
        return NULL;
    }

    node->next = target->next;
    node->prev = target;
    node->value = value;

    if (target->next)
    {
        target->next->prev = node;
    }
    else
    {
        list->tail = node;
    }

    target->next = node;

    return node;
}

size_t DoubleLinkedList_Count(const DoubleLinkedList* list)
{
    if (!list)
    {
        return 0;
    }

    size_t count = 0;
    const DoubleLinkedListNode* current = list->head;

    while (current)
    {
        ++count;
        current = current->next;
    }

    return count;
}
