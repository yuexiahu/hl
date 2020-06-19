#ifndef HL_HASHMAP_H_
#define HL_HASHMAP_H_

#include "hl_defs.h"

typedef struct hl_hashmap_node
{
    struct hl_hashmap_node* next;
    char data[0];
} hl_hashmap_node;

typedef struct hl_hashmap
{
    size_t len;
    size_t bucket_size;
    hl_hashmap_node** buckets;
    size_t (*hash_key)(const void* item);
    BOOL (*equals)(const void* item1, const void* item2);
} hl_hashmap;

void hl_hashmap_new(hl_hashmap* hashmap,
                    size_t (*hash_key)(const void* item),
                    BOOL (*equals)(const void* item1, const void* item2));
void hl_hashmap_free(hl_hashmap* hashmap);

void hl_hashmap_clear(hl_hashmap* hashmap);
void hl_hashmap_clone(hl_hashmap* hashmap, const hl_hashmap* from, size_t item_size);

HL_INLINE size_t hl_hashmap_len(const hl_hashmap* hashmap)
{
    hl_assert(hashmap != NULL);
    return hashmap->len;
}

hl_hashmap_node* hl_hashmap_insert(hl_hashmap* hashmap, const void* item, size_t item_size);
hl_hashmap_node* hl_hashmap_insert_noresize(hl_hashmap* hashmap, const void* item, size_t item_size);
void hl_hashmap_swap(hl_hashmap* hashmap1, hl_hashmap* hashmap2);
hl_hashmap_node* hl_hashmap_erase(hl_hashmap* hashmap, hl_hashmap_node* iter);
hl_hashmap_node* hl_hashmap_find(const hl_hashmap* hashmap, const void* item);

#define hl_hashmap_ref(type, iter) (*(type*)hl_hashmap_at(iter))

HL_INLINE void* hl_hashmap_at(hl_hashmap_node* iter)
{
    hl_return_v_check(iter != NULL, NULL);
    return iter->data;
}

HL_INLINE void hl_hashmap_get(hl_hashmap_node* iter, void* item, size_t item_size)
{
    hl_return_check(item != NULL);
    memcpy(item, hl_hashmap_at(iter), item_size);
}

HL_INLINE void hl_hashmap_set(hl_hashmap_node* iter, const void* item, size_t item_size)
{
    hl_return_check(item != NULL);
    memcpy(hl_hashmap_at(iter), item, item_size);
}

hl_hashmap_node* hl_hashmap_begin(const hl_hashmap* hashmap);
hl_hashmap_node* hl_hashmap_end(const hl_hashmap* hashmap);
void hl_hashmap_next(const hl_hashmap* hashmap, hl_hashmap_node** iter);

void hl_hashmap_resize(hl_hashmap* hashmap, size_t bucket_size_hint);
void hl_hashmap_reserve(hl_hashmap* hashmap, size_t len_hint);

#endif //HL_HASHMAP_H_
