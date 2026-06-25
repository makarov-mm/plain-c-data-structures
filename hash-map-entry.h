#ifndef HASH_MAP_ENTRY
#define HASH_MAP_ENTRY

typedef struct HashMapEntry {
    const char* key;
    void* value;
    struct HashMapEntry* next;
} HashMapEntry;

#endif
