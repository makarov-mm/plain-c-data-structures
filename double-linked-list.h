#ifndef DOUBLE_LINKED_LIST
#define DOUBLE_LINKED_LIST

#include <stddef.h>
#include "double-linked-list-node.h"

typedef struct DoubleLinkedList {
    struct DoubleLinkedListNode* head;
    struct DoubleLinkedListNode* tail;
} DoubleLinkedList;

extern DoubleLinkedList* DoubleLinkedList_Create(void);
extern void DoubleLinkedList_Clear(DoubleLinkedList* list);
extern void DoubleLinkedList_Delete(DoubleLinkedList* list);

extern void DoubleLinkedList_Foreach(DoubleLinkedList* list, void (*callback)(void* value));
extern void DoubleLinkedList_ForeachReverse(DoubleLinkedList* list, void (*callback)(void* value));

extern DoubleLinkedListNode* DoubleLinkedList_Add(DoubleLinkedList* list, void* value);
extern DoubleLinkedListNode* DoubleLinkedList_AddFirst(DoubleLinkedList* list, void* value);

extern void* DoubleLinkedList_Remove(DoubleLinkedList* list);
extern void* DoubleLinkedList_RemoveFirst(DoubleLinkedList* list);

extern DoubleLinkedListNode* DoubleLinkedList_InsertAfter(
    DoubleLinkedList* list,
    DoubleLinkedListNode* target,
    void* value
);

extern size_t DoubleLinkedList_Count(const DoubleLinkedList* list);

#endif
