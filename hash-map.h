#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct HashMapEntry
{
    const char* key;
    void* value;
    size_t hash;
    struct HashMapEntry* next;
} HashMapEntry;

// A string-keyed hash map with separate chaining. Entries are owned; keys
// and values are not: the map stores the key pointer as is, so the string
// must stay alive and unchanged while its entry is in the map.
typedef struct HashMap
{
    HashMapEntry** buckets;
    size_t bucket_count;
    size_t count;
} HashMap;

typedef void (*HashMapCallback)(const char* key, void* value, void* context);

[[nodiscard]] HashMap* HashMap_Create(void);
[[nodiscard]] HashMap* HashMap_CreateWithBucketCount(size_t bucket_count);
void HashMap_Clear(HashMap* map);
void HashMap_Delete(HashMap* map);

// Adds the key or replaces the value of an existing one; false if memory ran out.
bool HashMap_Put(HashMap* map, const char* key, void* value);
// nullptr when the key is absent.
void* HashMap_Get(const HashMap* map, const char* key);
bool HashMap_ContainsKey(const HashMap* map, const char* key);
// Removes the key and returns its value (nullptr when absent).
void* HashMap_Remove(HashMap* map, const char* key);

// Visits every entry in no particular order.
void HashMap_Foreach(const HashMap* map, HashMapCallback callback, void* context);

size_t HashMap_Count(const HashMap* map);
