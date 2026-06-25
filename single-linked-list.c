#include "single-linked-list.h"

#include <stdlib.h>

SingleLinkedList* SingleLinkedList_Create(void)
{
    SingleLinkedList* list = malloc(sizeof(*list));

    if (!list)
    {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
}

void SingleLinkedList_Clear(SingleLinkedList* list)
{
    if (!list)
    {
        return;
    }

    SingleLinkedListNode* current = list->head;

    while (current)
    {
        SingleLinkedListNode* next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
}

void SingleLinkedList_Delete(SingleLinkedList* list)
{
    if (!list)
    {
        return;
    }

    SingleLinkedList_Clear(list);
    free(list);
}

void SingleLinkedList_Foreach(SingleLinkedList* list, void (*callback)(void* value))
{
    if (!list || !callback)
    {
        return;
    }

    SingleLinkedListNode* current = list->head;

    while (current)
    {
        callback(current->value);
        current = current->next;
    }
}

SingleLinkedListNode* SingleLinkedList_Add(SingleLinkedList* list, void* value)
{
    if (!list)
    {
        return NULL;
    }

    SingleLinkedListNode* node = malloc(sizeof(*node));

    if (!node)
    {
        return NULL;
    }

    node->next = NULL;
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

void* SingleLinkedList_Remove(SingleLinkedList* list)
{
    if (!list || !list->tail)
    {
        return NULL;
    }

    SingleLinkedListNode* old_tail = list->tail;
    void* value = old_tail->value;

    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        SingleLinkedListNode* current = list->head;

        while (current->next != list->tail)
        {
            current = current->next;
        }

        current->next = NULL;
        list->tail = current;
    }

    free(old_tail);
    return value;
}

SingleLinkedListNode* SingleLinkedList_InsertAfter(
    SingleLinkedList* list,
    SingleLinkedListNode* target,
    void* value)
{
    if (!list || !target)
    {
        return NULL;
    }

    SingleLinkedListNode* node = malloc(sizeof(*node));

    if (!node)
    {
        return NULL;
    }

    node->next = target->next;
    node->value = value;
    target->next = node;

    if (list->tail == target)
    {
        list->tail = node;
    }

    return node;
}

size_t SingleLinkedList_Count(const SingleLinkedList* list)
{
    if (!list)
    {
        return 0;
    }

    size_t count = 0;
    const SingleLinkedListNode* current = list->head;

    while (current)
    {
        ++count;
        current = current->next;
    }

    return count;
}
