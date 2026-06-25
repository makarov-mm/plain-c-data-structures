#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include <stddef.h>

typedef struct DynamicArray {
    void** items;
    size_t count;
    size_t capacity;
} DynamicArray;

extern DynamicArray* DynamicArray_Create(void);
extern DynamicArray* DynamicArray_CreateWithCapacity(size_t capacity);
extern void DynamicArray_Clear(DynamicArray* array);
extern void DynamicArray_Delete(DynamicArray* array);

extern int DynamicArray_Add(DynamicArray* array, void* value);
extern void* DynamicArray_Get(const DynamicArray* array, size_t index);
extern int DynamicArray_Set(DynamicArray* array, size_t index, void* value);
extern void* DynamicArray_RemoveAt(DynamicArray* array, size_t index);

extern size_t DynamicArray_Count(const DynamicArray* array);
extern size_t DynamicArray_Capacity(const DynamicArray* array);

#endif
