#include "dynamic-array.h"

#include <stdlib.h>

#define DYNAMIC_ARRAY_DEFAULT_CAPACITY 4

static int DynamicArray_EnsureCapacity(DynamicArray* array, size_t required_capacity)
{
    if (!array)
    {
        return 0;
    }

    if (array->capacity >= required_capacity)
    {
        return 1;
    }

    size_t new_capacity = array->capacity ? array->capacity : DYNAMIC_ARRAY_DEFAULT_CAPACITY;

    while (new_capacity < required_capacity)
    {
        new_capacity *= 2;
    }

    void** new_items = realloc(array->items, new_capacity * sizeof(*new_items));

    if (!new_items)
    {
        return 0;
    }

    array->items = new_items;
    array->capacity = new_capacity;

    return 1;
}

DynamicArray* DynamicArray_Create(void)
{
    return DynamicArray_CreateWithCapacity(DYNAMIC_ARRAY_DEFAULT_CAPACITY);
}

DynamicArray* DynamicArray_CreateWithCapacity(size_t capacity)
{
    DynamicArray* array = malloc(sizeof(*array));

    if (!array)
    {
        return NULL;
    }

    array->items = NULL;
    array->count = 0;
    array->capacity = 0;

    if (capacity && !DynamicArray_EnsureCapacity(array, capacity))
    {
        free(array);
        return NULL;
    }

    return array;
}

void DynamicArray_Clear(DynamicArray* array)
{
    if (!array)
    {
        return;
    }

    array->count = 0;
}

void DynamicArray_Delete(DynamicArray* array)
{
    if (!array)
    {
        return;
    }

    free(array->items);
    free(array);
}

int DynamicArray_Add(DynamicArray* array, void* value)
{
    if (!array || !DynamicArray_EnsureCapacity(array, array->count + 1))
    {
        return 0;
    }

    array->items[array->count] = value;
    ++array->count;

    return 1;
}

void* DynamicArray_Get(const DynamicArray* array, size_t index)
{
    if (!array || index >= array->count)
    {
        return NULL;
    }

    return array->items[index];
}

int DynamicArray_Set(DynamicArray* array, size_t index, void* value)
{
    if (!array || index >= array->count)
    {
        return 0;
    }

    array->items[index] = value;
    return 1;
}

void* DynamicArray_RemoveAt(DynamicArray* array, size_t index)
{
    if (!array || index >= array->count)
    {
        return NULL;
    }

    void* value = array->items[index];

    for (size_t i = index + 1; i < array->count; ++i)
    {
        array->items[i - 1] = array->items[i];
    }

    --array->count;

    return value;
}

size_t DynamicArray_Count(const DynamicArray* array)
{
    if (!array)
    {
        return 0;
    }

    return array->count;
}

size_t DynamicArray_Capacity(const DynamicArray* array)
{
    if (!array)
    {
        return 0;
    }

    return array->capacity;
}
