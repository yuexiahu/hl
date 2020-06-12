#ifndef HL_HASHMAP_H_
#define HL_HASHMAP_H_

#include "hl_defs.h"
#include "hl_list.h"

typedef  struct hl_hashmap_node
{
    struct hl_hashmap_node* next;
    char data[0];
} hl_hashmap_node;

typedef struct hl_hashmap
{
    size_t len;
    size_t bucket_size;
    hl_hashmap_node** buckets;
    size_t (*hash_key)(void* item);
    BOOL (*equals)(void* item1, void* item2);
} hl_hashmap;

typedef struct hl_hashmap_iter
{
    hl_hashmap_node* cur;
    hl_hashmap* hashmap;
} hl_hashmap_iter;

void hl_hashmap_new(hl_hashmap* hashmap, size_t (*hash_key)(void* item), BOOL (*equals)(void* item1, void* item2));
void hl_hashmap_free(hl_hashmap* hashmap);

void hl_hashmap_clear(hl_hashmap* hashmap);
void hl_hashmap_clone(hl_hashmap* hashmap, const hl_hashmap* from, size_t item_size);

HL_INLINE size_t hl_hashmap_len(const hl_hashmap* hashmap)
{
    hl_assert(hashmap != NULL);
    return hashmap->len;
}

void hl_hashmap_insert(hl_hashmap* hashmap, const void* item, size_t item_size);
void hl_hashmap_swap(hl_hashmap* hashmap1, hl_hashmap* hashmap2);
void hl_hashmap_erase(hl_hashmap* hashmap, hl_hashmap_iter* iter);

#define hl_hashmap_ref(type, iter) (*(type*)hl_hashmap_at(iter))

HL_INLINE void* hl_hashmap_at(hl_hashmap_iter* iter)
{
    hl_return_v_check(iter != NULL && iter->cur != NULL, NULL);
    return iter->cur->data;
}

HL_INLINE void hl_hashmap_get(hl_hashmap_iter* iter, void* data, size_t item_size)
{
    hl_return_check(data != NULL);
    memcpy(data, hl_hashmap_at(iter), item_size);
}

HL_INLINE void hl_hashmap_set(hl_hashmap_iter* iter, const void* data, size_t item_size)
{
    hl_return_check(data != NULL);
    memcpy(hl_hashmap_at(iter), data, item_size);
}

void hl_hashmap_begin(hl_hashmap* hashmap, hl_hashmap_iter* iter);
void hl_hashmap_end(hl_hashmap* hashmap, hl_hashmap_iter* iter);
void hl_hashmap_next(hl_hashmap_iter* iter);

#endif //HL_HASHMAP_H_
