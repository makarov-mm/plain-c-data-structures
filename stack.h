#ifndef STACK
#define STACK

#include <stddef.h>
#include "double-linked-list.h"

typedef struct Stack {
    struct DoubleLinkedList* list;
} Stack;

extern Stack* Stack_Create(void);
extern void Stack_Delete(Stack* stack);

extern void Stack_Push(Stack* stack, void* value);
extern void* Stack_Pop(Stack* stack);

extern size_t Stack_Count(const Stack* stack);

#endif
