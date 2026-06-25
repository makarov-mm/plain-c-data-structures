#include "stack.h"

#include <stdlib.h>

Stack* Stack_Create(void)
{
    Stack* stack = malloc(sizeof(*stack));

    if (!stack)
    {
        return NULL;
    }

    stack->list = DoubleLinkedList_Create();

    if (!stack->list)
    {
        free(stack);
        return NULL;
    }

    return stack;
}

void Stack_Delete(Stack* stack)
{
    if (!stack)
    {
        return;
    }

    DoubleLinkedList_Delete(stack->list);
    free(stack);
}

void Stack_Push(Stack* stack, void* value)
{
    if (!stack)
    {
        return;
    }

    DoubleLinkedList_Add(stack->list, value);
}

void* Stack_Pop(Stack* stack)
{
    if (!stack)
    {
        return NULL;
    }

    return DoubleLinkedList_Remove(stack->list);
}

size_t Stack_Count(const Stack* stack)
{
    if (!stack)
    {
        return 0;
    }

    return DoubleLinkedList_Count(stack->list);
}
