#ifndef HL_MAP_H_
#define HL_MAP_H_

#include "hl_defs.h"

#define HL_MAP_BLACK 0
#define HL_MAP_RED   1

typedef struct hl_map_node
{
    struct hl_map_node* parent;
    struct hl_map_node* left;
    struct hl_map_node* right;
    int color;
    char data[0];
} hl_map_node;

typedef struct hl_map
{
    size_t len;
    hl_map_node* root;
    BOOL (*less)(const void* item1, const void* item2);
} hl_map;

void hl_map_new(hl_map* map, BOOL (*less)(const void* item1, const void* item2));
void hl_map_free(hl_map* map);

void hl_map_clear(hl_map* map);
void hl_map_clone(hl_map* map, const hl_map* from, size_t item_size);

HL_INLINE size_t hl_map_len(const hl_map* map)
{
    hl_assert(map != NULL);
    return map->len;
}
HL_INLINE BOOL hl_map_empty(const hl_map* map)
{
    return hl_map_len(map) == 0;
}

hl_map_node* hl_map_insert(hl_map* map, const void* item, size_t item_size);
hl_map_node* hl_map_insert_or_replace(hl_map* map, const void* item, size_t item_size);
void hl_map_swap(hl_map* map1, hl_map* map2);
hl_map_node* hl_map_erase(hl_map* map, hl_map_node* iter);
hl_map_node* hl_map_find(const hl_map* map, const void* item);

#define hl_map_ref(type, iter) (*(type*)hl_map_at(iter))

HL_INLINE void* hl_map_at(hl_map_node* iter)
{
    hl_return_v_check(iter != NULL, NULL);
    return iter->data;
}

HL_INLINE void hl_map_get(hl_map_node* iter, void* item, size_t item_size)
{
    hl_return_check(item != NULL);
    memcpy(item, hl_map_at(iter), item_size);
}

HL_INLINE void hl_map_set(hl_map_node* iter, const void* item, size_t item_size)
{
    hl_return_check(item != NULL);
    memcpy(hl_map_at(iter), item, item_size);
}

hl_map_node* hl_map_min(const hl_map* map);
hl_map_node* hl_map_max(const hl_map* map);

HL_INLINE hl_map_node* hl_map_begin(const hl_map* map)
{
    return hl_map_min(map);
}

HL_INLINE hl_map_node* hl_map_end(const hl_map* map)
{
    return NULL;
}

void hl_map_prev(const hl_map* map, hl_map_node** iter);
void hl_map_next(const hl_map* map, hl_map_node** iter);

#endif //HL_MAP_H_
