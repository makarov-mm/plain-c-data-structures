#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct DoubleLinkedListNode
{
    void* value;
    struct DoubleLinkedListNode* next;
    struct DoubleLinkedListNode* prev;
} DoubleLinkedListNode;

// Nodes are owned by the list; values are not. Every operation here is O(1)
// except Clear and Foreach.
typedef struct DoubleLinkedList
{
    DoubleLinkedListNode* head;
    DoubleLinkedListNode* tail;
    size_t count;
} DoubleLinkedList;

typedef void (*DoubleLinkedListCallback)(void* value, void* context);

[[nodiscard]] DoubleLinkedList* DoubleLinkedList_Create(void);
// Resets a list that lives inside another object (no allocation).
void DoubleLinkedList_Init(DoubleLinkedList* list);
void DoubleLinkedList_Clear(DoubleLinkedList* list);
void DoubleLinkedList_Delete(DoubleLinkedList* list);

DoubleLinkedListNode* DoubleLinkedList_Add(DoubleLinkedList* list, void* value);
DoubleLinkedListNode* DoubleLinkedList_AddFirst(DoubleLinkedList* list, void* value);
DoubleLinkedListNode* DoubleLinkedList_InsertAfter(DoubleLinkedList* list, DoubleLinkedListNode* target, void* value);
DoubleLinkedListNode* DoubleLinkedList_InsertBefore(DoubleLinkedList* list, DoubleLinkedListNode* target, void* value);

// Remove the tail / head and return its value (nullptr when empty).
void* DoubleLinkedList_Remove(DoubleLinkedList* list);
void* DoubleLinkedList_RemoveFirst(DoubleLinkedList* list);
// Unlinks and frees any node of this list, returning its value.
void* DoubleLinkedList_RemoveNode(DoubleLinkedList* list, DoubleLinkedListNode* node);

// Value at the tail / head without removing it (nullptr when empty).
void* DoubleLinkedList_Last(const DoubleLinkedList* list);
void* DoubleLinkedList_First(const DoubleLinkedList* list);

void DoubleLinkedList_Foreach(const DoubleLinkedList* list, DoubleLinkedListCallback callback, void* context);
void DoubleLinkedList_ForeachReverse(const DoubleLinkedList* list, DoubleLinkedListCallback callback, void* context);

size_t DoubleLinkedList_Count(const DoubleLinkedList* list);
