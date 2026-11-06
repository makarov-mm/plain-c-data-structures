#include "single-linked-list.h"

#include <stdlib.h>

static SingleLinkedListNode* CreateNode(void* value, SingleLinkedListNode* next)
{
    SingleLinkedListNode* node = malloc(sizeof(*node));

    if (!node)
    {
        return nullptr;
    }

    node->value = value;
    node->next = next;

    return node;
}

SingleLinkedList* SingleLinkedList_Create(void)
{
    SingleLinkedList* list = malloc(sizeof(*list));

    if (list)
    {
        *list = (SingleLinkedList){};
    }

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

    *list = (SingleLinkedList){};
}

void SingleLinkedList_Delete(SingleLinkedList* list)
{
    SingleLinkedList_Clear(list);
    free(list);
}

SingleLinkedListNode* SingleLinkedList_Add(SingleLinkedList* list, void* value)
{
    if (!list)
    {
        return nullptr;
    }

    SingleLinkedListNode* node = CreateNode(value, nullptr);

    if (!node)
    {
        return nullptr;
    }

    if (list->tail)
    {
        list->tail->next = node;
    }
    else
    {
        list->head = node;
    }

    list->tail = node;
    ++list->count;

    return node;
}

SingleLinkedListNode* SingleLinkedList_AddFirst(SingleLinkedList* list, void* value)
{
    if (!list)
    {
        return nullptr;
    }

    SingleLinkedListNode* node = CreateNode(value, list->head);

    if (!node)
    {
        return nullptr;
    }

    list->head = node;

    if (!list->tail)
    {
        list->tail = node;
    }

    ++list->count;

    return node;
}

SingleLinkedListNode* SingleLinkedList_InsertAfter(SingleLinkedList* list, SingleLinkedListNode* target, void* value)
{
    if (!list || !target)
    {
        return nullptr;
    }

    SingleLinkedListNode* node = CreateNode(value, target->next);

    if (!node)
    {
        return nullptr;
    }

    target->next = node;

    if (list->tail == target)
    {
        list->tail = node;
    }

    ++list->count;

    return node;
}

void* SingleLinkedList_Remove(SingleLinkedList* list)
{
    if (!list || !list->tail)
    {
        return nullptr;
    }

    SingleLinkedListNode* old_tail = list->tail;
    void* value = old_tail->value;

    if (list->head == old_tail)
    {
        list->head = nullptr;
        list->tail = nullptr;
    }
    else
    {
        SingleLinkedListNode* before_tail = list->head;

        while (before_tail->next != old_tail)
        {
            before_tail = before_tail->next;
        }

        before_tail->next = nullptr;
        list->tail = before_tail;
    }

    free(old_tail);
    --list->count;

    return value;
}

void* SingleLinkedList_RemoveFirst(SingleLinkedList* list)
{
    if (!list || !list->head)
    {
        return nullptr;
    }

    SingleLinkedListNode* old_head = list->head;
    void* value = old_head->value;

    list->head = old_head->next;

    if (!list->head)
    {
        list->tail = nullptr;
    }

    free(old_head);
    --list->count;

    return value;
}

void SingleLinkedList_Foreach(const SingleLinkedList* list, SingleLinkedListCallback callback, void* context)
{
    if (!list || !callback)
    {
        return;
    }

    for (SingleLinkedListNode* node = list->head; node; node = node->next)
    {
        callback(node->value, context);
    }
}

size_t SingleLinkedList_Count(const SingleLinkedList* list)
{
    return list ? list->count : 0;
}
