#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct SingleLinkedListNode
{
    void* value;
    struct SingleLinkedListNode* next;
} SingleLinkedListNode;

// Nodes are owned by the list; values are not.
typedef struct SingleLinkedList
{
    SingleLinkedListNode* head;
    SingleLinkedListNode* tail;
    size_t count;
} SingleLinkedList;

typedef void (*SingleLinkedListCallback)(void* value, void* context);

[[nodiscard]] SingleLinkedList* SingleLinkedList_Create(void);
void SingleLinkedList_Clear(SingleLinkedList* list);
void SingleLinkedList_Delete(SingleLinkedList* list);

// Appends at the tail, O(1).
SingleLinkedListNode* SingleLinkedList_Add(SingleLinkedList* list, void* value);
// Prepends at the head, O(1).
SingleLinkedListNode* SingleLinkedList_AddFirst(SingleLinkedList* list, void* value);
// Inserts after a node of this list, O(1).
SingleLinkedListNode* SingleLinkedList_InsertAfter(SingleLinkedList* list, SingleLinkedListNode* target, void* value);

// Removes the tail and returns its value (nullptr when empty). O(n): a
// singly linked list has to walk to the node before the tail.
void* SingleLinkedList_Remove(SingleLinkedList* list);
// Removes the head and returns its value (nullptr when empty), O(1).
void* SingleLinkedList_RemoveFirst(SingleLinkedList* list);

void SingleLinkedList_Foreach(const SingleLinkedList* list, SingleLinkedListCallback callback, void* context);

size_t SingleLinkedList_Count(const SingleLinkedList* list);
