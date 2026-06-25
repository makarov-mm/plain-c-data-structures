#ifndef SINGLE_LINKED_LIST
#define SINGLE_LINKED_LIST

#include <stddef.h>
#include "single-linked-list-node.h"

typedef struct SingleLinkedList {
    struct SingleLinkedListNode* head;
    struct SingleLinkedListNode* tail;
} SingleLinkedList;

extern SingleLinkedList* SingleLinkedList_Create(void);
extern void SingleLinkedList_Clear(SingleLinkedList* list);
extern void SingleLinkedList_Delete(SingleLinkedList* list);

extern void SingleLinkedList_Foreach(SingleLinkedList* list, void (*callback)(void* value));

extern SingleLinkedListNode* SingleLinkedList_Add(SingleLinkedList* list, void* value);
extern void* SingleLinkedList_Remove(SingleLinkedList* list);

extern SingleLinkedListNode* SingleLinkedList_InsertAfter(
    SingleLinkedList* list,
    SingleLinkedListNode* target,
    void* value
);

extern size_t SingleLinkedList_Count(const SingleLinkedList* list);

#endif
