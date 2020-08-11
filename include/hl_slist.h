#ifndef HL_SLIST_H_
#define HL_SLIST_H_

#include "hl_defs.h"

typedef struct hl_slist_node
{
    struct hl_slist_node* next;
    char data[0];
} hl_slist_node;

typedef hl_slist_node hl_slist;

void hl_slist_new(hl_slist* slist);
void hl_slist_free(hl_slist* slist);

void hl_slist_clear(hl_slist* slist);
void hl_slist_clone(hl_slist* slist, const hl_slist* from, size_t item_size);

size_t hl_slist_len(const hl_slist* slist);
HL_INLINE BOOL hl_slist_empty(const hl_slist* slist)
{
    hl_assert(slist != NULL);
    return slist->next == NULL;
}

hl_slist_node* hl_slist_find(const hl_slist* slist, const void* item, hl_slist_node* start,
                           BOOL (*equals)(const void* item1, const void* item2));
hl_slist_node* hl_slist_find_if(const hl_slist* slist, hl_slist_node* start, BOOL (*find_if)(const void* item));

void hl_slist_append(hl_slist* slist, const void* item, size_t item_size);
void hl_slist_prepend(hl_slist* slist, const void* item, size_t item_size);
void hl_slist_insert(hl_slist* slist, hl_slist_node* iter, const void* item, size_t item_size);
void hl_slist_insert_after(hl_slist* slist, hl_slist_node* iter, const void* item, size_t item_size);
void hl_slist_swap(hl_slist* slist1, hl_slist* slist2);
hl_slist_node* hl_slist_erase(hl_slist* slist, hl_slist_node* iter);
hl_slist_node* hl_slist_erase_after(hl_slist* slist, hl_slist_node* iter);

#define hl_slist_ref(type, iter) (*(type*)hl_slist_at(iter))

HL_INLINE void* hl_slist_at(hl_slist_node* iter)
{
    hl_return_v_check(iter != NULL, NULL);
    return iter->data;
}

HL_INLINE void hl_slist_get(hl_slist_node* iter, void* item, size_t item_size)
{
    hl_return_check(item != NULL);
    memcpy(item, hl_slist_at(iter), item_size);
}

HL_INLINE void hl_slist_set(hl_slist_node* iter, const void* item, size_t item_size)
{
    hl_return_check(item != NULL);
    memcpy(hl_slist_at(iter), item, item_size);
}

HL_INLINE hl_slist_node* hl_slist_begin(const hl_slist* slist)
{
    hl_assert(slist != NULL);
    return slist->next;
}

HL_INLINE hl_slist_node* hl_slist_end(const hl_slist* slist)
{
    return NULL;
}

HL_INLINE void hl_slist_next(hl_slist_node** iter)
{
    hl_assert(iter != NULL);
    hl_return_check(*iter != NULL);
    *iter = (*iter)->next;
}

HL_INLINE void* hl_slist_first(const hl_slist* slist)
{
    return hl_slist_at(hl_slist_begin(slist));
}

#endif // HL_LIST_H_
