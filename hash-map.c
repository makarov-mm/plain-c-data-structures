#include "hash-map.h"

#include <stdlib.h>
#include <string.h>

#define HASH_MAP_DEFAULT_BUCKET_COUNT 16
#define HASH_MAP_MAX_LOAD_NUMERATOR 3
#define HASH_MAP_MAX_LOAD_DENOMINATOR 4

static size_t HashMap_Hash(const char* key)
{
    size_t hash = 5381;
    const unsigned char* bytes = (const unsigned char*)key;
    unsigned char c;

    while ((c = *bytes++) != 0)
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

static HashMapEntry* HashMap_CreateEntry(const char* key, void* value)
{
    HashMapEntry* entry = malloc(sizeof(*entry));

    if (!entry)
    {
        return NULL;
    }

    entry->key = key;
    entry->value = value;
    entry->next = NULL;

    return entry;
}

static int HashMap_Rehash(HashMap* map, size_t new_bucket_count)
{
    HashMapEntry** new_buckets = calloc(new_bucket_count, sizeof(*new_buckets));

    if (!new_buckets)
    {
        return 0;
    }

    for (size_t i = 0; i < map->bucket_count; ++i)
    {
        HashMapEntry* entry = map->buckets[i];

        while (entry)
        {
            HashMapEntry* next = entry->next;
            size_t new_index = HashMap_Hash(entry->key) % new_bucket_count;
            entry->next = new_buckets[new_index];
            new_buckets[new_index] = entry;
            entry = next;
        }
    }

    free(map->buckets);
    map->buckets = new_buckets;
    map->bucket_count = new_bucket_count;

    return 1;
}

static int HashMap_EnsureCapacity(HashMap* map)
{
    if (!map)
    {
        return 0;
    }

    if ((map->count + 1) * HASH_MAP_MAX_LOAD_DENOMINATOR <=
        map->bucket_count * HASH_MAP_MAX_LOAD_NUMERATOR)
    {
        return 1;
    }

    return HashMap_Rehash(map, map->bucket_count * 2);
}

HashMap* HashMap_Create(void)
{
    return HashMap_CreateWithBucketCount(HASH_MAP_DEFAULT_BUCKET_COUNT);
}

HashMap* HashMap_CreateWithBucketCount(size_t bucket_count)
{
    if (bucket_count == 0)
    {
        bucket_count = HASH_MAP_DEFAULT_BUCKET_COUNT;
    }

    HashMap* map = malloc(sizeof(*map));

    if (!map)
    {
        return NULL;
    }

    map->buckets = calloc(bucket_count, sizeof(*map->buckets));

    if (!map->buckets)
    {
        free(map);
        return NULL;
    }

    map->bucket_count = bucket_count;
    map->count = 0;

    return map;
}

void HashMap_Clear(HashMap* map)
{
    if (!map)
    {
        return;
    }

    for (size_t i = 0; i < map->bucket_count; ++i)
    {
        HashMapEntry* entry = map->buckets[i];

        while (entry)
        {
            HashMapEntry* next = entry->next;
            free(entry);
            entry = next;
        }

        map->buckets[i] = NULL;
    }

    map->count = 0;
}

void HashMap_Delete(HashMap* map)
{
    if (!map)
    {
        return;
    }

    HashMap_Clear(map);
    free(map->buckets);
    free(map);
}

int HashMap_Put(HashMap* map, const char* key, void* value)
{
    if (!map || !key)
    {
        return 0;
    }

    size_t index = HashMap_Hash(key) % map->bucket_count;
    HashMapEntry* entry = map->buckets[index];

    while (entry)
    {
        if (strcmp(entry->key, key) == 0)
        {
            entry->value = value;
            return 1;
        }

        entry = entry->next;
    }

    if (!HashMap_EnsureCapacity(map))
    {
        return 0;
    }

    index = HashMap_Hash(key) % map->bucket_count;

    HashMapEntry* new_entry = HashMap_CreateEntry(key, value);

    if (!new_entry)
    {
        return 0;
    }

    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
    ++map->count;

    return 1;
}

void* HashMap_Get(const HashMap* map, const char* key)
{
    if (!map || !key)
    {
        return NULL;
    }

    size_t index = HashMap_Hash(key) % map->bucket_count;
    HashMapEntry* entry = map->buckets[index];

    while (entry)
    {
        if (strcmp(entry->key, key) == 0)
        {
            return entry->value;
        }

        entry = entry->next;
    }

    return NULL;
}

int HashMap_ContainsKey(const HashMap* map, const char* key)
{
    if (!map || !key)
    {
        return 0;
    }

    size_t index = HashMap_Hash(key) % map->bucket_count;
    HashMapEntry* entry = map->buckets[index];

    while (entry)
    {
        if (strcmp(entry->key, key) == 0)
        {
            return 1;
        }

        entry = entry->next;
    }

    return 0;
}

void* HashMap_Remove(HashMap* map, const char* key)
{
    if (!map || !key)
    {
        return NULL;
    }

    size_t index = HashMap_Hash(key) % map->bucket_count;
    HashMapEntry* entry = map->buckets[index];
    HashMapEntry* previous = NULL;

    while (entry)
    {
        if (strcmp(entry->key, key) == 0)
        {
            void* value = entry->value;

            if (previous)
            {
                previous->next = entry->next;
            }
            else
            {
                map->buckets[index] = entry->next;
            }

            free(entry);
            --map->count;
            return value;
        }

        previous = entry;
        entry = entry->next;
    }

    return NULL;
}

size_t HashMap_Count(const HashMap* map)
{
    if (!map)
    {
        return 0;
    }

    return map->count;
}
