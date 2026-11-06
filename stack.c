#include "stack.h"

#include <stdlib.h>

Stack* Stack_Create(void)
{
    Stack* stack = malloc(sizeof(*stack));

    if (stack)
    {
        DoubleLinkedList_Init(&stack->list);
    }

    return stack;
}

void Stack_Clear(Stack* stack)
{
    if (stack)
    {
        DoubleLinkedList_Clear(&stack->list);
    }
}

void Stack_Delete(Stack* stack)
{
    Stack_Clear(stack);
    free(stack);
}

bool Stack_Push(Stack* stack, void* value)
{
    return stack && DoubleLinkedList_Add(&stack->list, value) != nullptr;
}

void* Stack_Pop(Stack* stack)
{
    return stack ? DoubleLinkedList_Remove(&stack->list) : nullptr;
}

void* Stack_Peek(const Stack* stack)
{
    return stack ? DoubleLinkedList_Last(&stack->list) : nullptr;
}

size_t Stack_Count(const Stack* stack)
{
    return stack ? stack->list.count : 0;
}
