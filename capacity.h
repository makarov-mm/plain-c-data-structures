// Growth policy shared by the array-backed containers. Internal header.
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Grows `*items` (an array of `*capacity` pointers) so it holds at least
// `required` pointers, doubling from `initial` up. Returns false and leaves
// the array untouched when the size is impossible or memory runs out.
static inline bool GrowPointerArray(void*** items, size_t* capacity, size_t required, size_t initial)
{
    if (*capacity >= required)
    {
        return true;
    }

    const size_t max_capacity = SIZE_MAX / sizeof(void*);

    if (required > max_capacity)
    {
        return false;
    }

    size_t new_capacity = *capacity ? *capacity : initial;

    while (new_capacity < required)
    {
        new_capacity = new_capacity > max_capacity / 2 ? required : new_capacity * 2;
    }

    void** new_items = realloc(*items, new_capacity * sizeof(void*));

    if (!new_items)
    {
        return false;
    }

    *items = new_items;
    *capacity = new_capacity;

    return true;
}
