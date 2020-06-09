#ifndef HL_HASHMAP_H_
#define HL_HASHMAP_H_

#include "hl_defs.h"
#include "hl_slist.h"

typedef struct hl_hashmap
{
    size_t len;
    size_t cap;
    unsigned (*hash_func)(void*);
    hl_slist* buckets;
} hl_hashmap;

#endif //HL_HASHMAP_H_
