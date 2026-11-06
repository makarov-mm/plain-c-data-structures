#pragma once

#include <stdbool.h>
#include <stddef.h>

// A resizable array of void* values. The array buffer is owned; values are not.
typedef struct DynamicArray
{
    void** items;
    size_t count;
    size_t capacity;
} DynamicArray;

typedef void (*DynamicArrayCallback)(void* value, void* context);

[[nodiscard]] DynamicArray* DynamicArray_Create(void);
[[nodiscard]] DynamicArray* DynamicArray_CreateWithCapacity(size_t capacity);
// Drops the values but keeps the buffer.
void DynamicArray_Clear(DynamicArray* array);
void DynamicArray_Delete(DynamicArray* array);

// Grows the buffer to hold at least `capacity` values; false on failure.
bool DynamicArray_Reserve(DynamicArray* array, size_t capacity);

// Appends a value, amortized O(1); false if memory ran out.
bool DynamicArray_Add(DynamicArray* array, void* value);
// Inserts at `index` (0..count), shifting the rest up; false if out of range or out of memory.
bool DynamicArray_Insert(DynamicArray* array, size_t index, void* value);
// nullptr when the index is out of range.
void* DynamicArray_Get(const DynamicArray* array, size_t index);
// False when the index is out of range.
bool DynamicArray_Set(DynamicArray* array, size_t index, void* value);
// Removes the value at `index`, shifting the rest down, and returns it (nullptr if out of range).
void* DynamicArray_RemoveAt(DynamicArray* array, size_t index);
// Removes and returns the last value (nullptr when empty).
void* DynamicArray_RemoveLast(DynamicArray* array);

void DynamicArray_Foreach(const DynamicArray* array, DynamicArrayCallback callback, void* context);

size_t DynamicArray_Count(const DynamicArray* array);
size_t DynamicArray_Capacity(const DynamicArray* array);
