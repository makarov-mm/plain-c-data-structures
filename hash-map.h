#ifndef HASH_MAP
#define HASH_MAP

#include <stddef.h>
#include "hash-map-entry.h"

typedef struct HashMap {
    struct HashMapEntry** buckets;
    size_t bucket_count;
    size_t count;
} HashMap;

extern HashMap* HashMap_Create(void);
extern HashMap* HashMap_CreateWithBucketCount(size_t bucket_count);
extern void HashMap_Clear(HashMap* map);
extern void HashMap_Delete(HashMap* map);

extern int HashMap_Put(HashMap* map, const char* key, void* value);
extern void* HashMap_Get(const HashMap* map, const char* key);
extern int HashMap_ContainsKey(const HashMap* map, const char* key);
extern void* HashMap_Remove(HashMap* map, const char* key);

extern size_t HashMap_Count(const HashMap* map);

#endif
