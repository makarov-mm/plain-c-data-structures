#pragma once

#include <stddef.h>

#include "double-linked-list.h"

// LIFO container over a doubly linked list; every operation is O(1).
typedef struct Stack
{
    DoubleLinkedList list;
} Stack;

[[nodiscard]] Stack* Stack_Create(void);
void Stack_Clear(Stack* stack);
void Stack_Delete(Stack* stack);

// Returns false if the node could not be allocated.
bool Stack_Push(Stack* stack, void* value);
// Removes and returns the top value (nullptr when empty).
void* Stack_Pop(Stack* stack);
// The top value without removing it (nullptr when empty).
void* Stack_Peek(const Stack* stack);

size_t Stack_Count(const Stack* stack);
