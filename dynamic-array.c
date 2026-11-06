#include "dynamic-array.h"

#include <stdlib.h>
#include <string.h>

#include "capacity.h"

enum { kDefaultCapacity = 4 };

DynamicArray* DynamicArray_Create(void)
{
    return DynamicArray_CreateWithCapacity(kDefaultCapacity);
}

DynamicArray* DynamicArray_CreateWithCapacity(size_t capacity)
{
    DynamicArray* array = malloc(sizeof(*array));

    if (!array)
    {
        return nullptr;
    }

    *array = (DynamicArray){};

    if (!DynamicArray_Reserve(array, capacity))
    {
        free(array);
        return nullptr;
    }

    return array;
}

void DynamicArray_Clear(DynamicArray* array)
{
    if (array)
    {
        array->count = 0;
    }
}

void DynamicArray_Delete(DynamicArray* array)
{
    if (array)
    {
        free(array->items);
        free(array);
    }
}

bool DynamicArray_Reserve(DynamicArray* array, size_t capacity)
{
    return array && GrowPointerArray(&array->items, &array->capacity, capacity, kDefaultCapacity);
}

bool DynamicArray_Add(DynamicArray* array, void* value)
{
    if (!array || !DynamicArray_Reserve(array, array->count + 1))
    {
        return false;
    }

    array->items[array->count++] = value;

    return true;
}

bool DynamicArray_Insert(DynamicArray* array, size_t index, void* value)
{
    if (!array || index > array->count || !DynamicArray_Reserve(array, array->count + 1))
    {
        return false;
    }

    memmove(&array->items[index + 1], &array->items[index], (array->count - index) * sizeof(*array->items));
    array->items[index] = value;
    ++array->count;

    return true;
}

void* DynamicArray_Get(const DynamicArray* array, size_t index)
{
    return array && index < array->count ? array->items[index] : nullptr;
}

bool DynamicArray_Set(DynamicArray* array, size_t index, void* value)
{
    if (!array || index >= array->count)
    {
        return false;
    }

    array->items[index] = value;

    return true;
}

void* DynamicArray_RemoveAt(DynamicArray* array, size_t index)
{
    if (!array || index >= array->count)
    {
        return nullptr;
    }

    void* value = array->items[index];
    --array->count;
    memmove(&array->items[index], &array->items[index + 1], (array->count - index) * sizeof(*array->items));

    return value;
}

void* DynamicArray_RemoveLast(DynamicArray* array)
{
    return array && array->count ? array->items[--array->count] : nullptr;
}

void DynamicArray_Foreach(const DynamicArray* array, DynamicArrayCallback callback, void* context)
{
    if (!array || !callback)
    {
        return;
    }

    for (size_t i = 0; i < array->count; ++i)
    {
        callback(array->items[i], context);
    }
}

size_t DynamicArray_Count(const DynamicArray* array)
{
    return array ? array->count : 0;
}

size_t DynamicArray_Capacity(const DynamicArray* array)
{
    return array ? array->capacity : 0;
}
