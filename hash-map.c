#include "hash-map.h"

#include <stdlib.h>
#include <string.h>

enum
{
    kDefaultBucketCount = 16,
    // Rehash into twice the buckets once there are more than 3 entries per 4 buckets.
    kMaxLoadNumerator = 3,
    kMaxLoadDenominator = 4,
};

// djb2
static size_t Hash(const char* key)
{
    size_t hash = 5381;

    for (const unsigned char* c = (const unsigned char*)key; *c; ++c)
    {
        hash = hash * 33 + *c;
    }

    return hash;
}

// The link (bucket head or an entry's `next`) that points at the key's
// entry, or at the end of its chain when the key is absent.
static HashMapEntry** FindLink(const HashMap* map, const char* key, size_t hash)
{
    HashMapEntry** link = &map->buckets[hash % map->bucket_count];

    while (*link && ((*link)->hash != hash || strcmp((*link)->key, key) != 0))
    {
        link = &(*link)->next;
    }

    return link;
}

static bool Rehash(HashMap* map, size_t bucket_count)
{
    HashMapEntry** buckets = calloc(bucket_count, sizeof(*buckets));

    if (!buckets)
    {
        return false;
    }

    for (size_t i = 0; i < map->bucket_count; ++i)
    {
        HashMapEntry* entry = map->buckets[i];

        while (entry)
        {
            HashMapEntry* next = entry->next;
            HashMapEntry** bucket = &buckets[entry->hash % bucket_count];
            entry->next = *bucket;
            *bucket = entry;
            entry = next;
        }
    }

    free(map->buckets);
    map->buckets = buckets;
    map->bucket_count = bucket_count;

    return true;
}

HashMap* HashMap_Create(void)
{
    return HashMap_CreateWithBucketCount(kDefaultBucketCount);
}

HashMap* HashMap_CreateWithBucketCount(size_t bucket_count)
{
    if (bucket_count == 0)
    {
        bucket_count = kDefaultBucketCount;
    }

    HashMap* map = malloc(sizeof(*map));

    if (!map)
    {
        return nullptr;
    }

    *map = (HashMap){.buckets = calloc(bucket_count, sizeof(*map->buckets)), .bucket_count = bucket_count};

    if (!map->buckets)
    {
        free(map);
        return nullptr;
    }

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

        map->buckets[i] = nullptr;
    }

    map->count = 0;
}

void HashMap_Delete(HashMap* map)
{
    if (map)
    {
        HashMap_Clear(map);
        free(map->buckets);
        free(map);
    }
}

bool HashMap_Put(HashMap* map, const char* key, void* value)
{
    if (!map || !key)
    {
        return false;
    }

    size_t hash = Hash(key);
    HashMapEntry* existing = *FindLink(map, key, hash);

    if (existing)
    {
        existing->value = value;
        return true;
    }

    if ((map->count + 1) * kMaxLoadDenominator > map->bucket_count * kMaxLoadNumerator &&
        !Rehash(map, map->bucket_count * 2))
    {
        return false;
    }

    HashMapEntry* entry = malloc(sizeof(*entry));

    if (!entry)
    {
        return false;
    }

    HashMapEntry** bucket = &map->buckets[hash % map->bucket_count];
    *entry = (HashMapEntry){.key = key, .value = value, .hash = hash, .next = *bucket};
    *bucket = entry;
    ++map->count;

    return true;
}

void* HashMap_Get(const HashMap* map, const char* key)
{
    if (!map || !key)
    {
        return nullptr;
    }

    HashMapEntry* entry = *FindLink(map, key, Hash(key));

    return entry ? entry->value : nullptr;
}

bool HashMap_ContainsKey(const HashMap* map, const char* key)
{
    return map && key && *FindLink(map, key, Hash(key)) != nullptr;
}

void* HashMap_Remove(HashMap* map, const char* key)
{
    if (!map || !key)
    {
        return nullptr;
    }

    HashMapEntry** link = FindLink(map, key, Hash(key));
    HashMapEntry* entry = *link;

    if (!entry)
    {
        return nullptr;
    }

    void* value = entry->value;
    *link = entry->next;
    free(entry);
    --map->count;

    return value;
}

void HashMap_Foreach(const HashMap* map, HashMapCallback callback, void* context)
{
    if (!map || !callback)
    {
        return;
    }

    for (size_t i = 0; i < map->bucket_count; ++i)
    {
        for (HashMapEntry* entry = map->buckets[i]; entry; entry = entry->next)
        {
            callback(entry->key, entry->value, context);
        }
    }
}

size_t HashMap_Count(const HashMap* map)
{
    return map ? map->count : 0;
}
