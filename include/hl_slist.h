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
void hl_slist_set(hl_slist* slist, const hl_slist* data, size_t item_size);

size_t hl_slist_len(const hl_slist* slist);

void hl_slist_append(hl_slist* slist, const void* item, size_t item_size);
void hl_slist_prepend(hl_slist* slist, const void* item, size_t item_size);
void hl_slist_insert(hl_slist* slist, hl_slist_node* iter, const void* item, size_t item_size);
void hl_slist_insert_after(hl_slist* slist, hl_slist_node* iter, const void* item, size_t item_size);
void hl_slist_swap(hl_slist* slist1, hl_slist* slist2);
hl_slist_node* hl_slist_erase(hl_slist* slist, hl_slist_node* iter);

#define hl_slist_ref(type, iter) (*(type*)hl_slist_at(iter))

__HL_INLINE__ void* hl_slist_at(hl_slist_node* iter)
{
    hl_return_v_check(iter != NULL, NULL);
    return iter->data;
}

__HL_INLINE__ void hl_slist_get(hl_slist_node* iter, void* data, size_t item_size)
{
    hl_return_check(data != NULL);
    memcpy(data, hl_slist_at(iter), item_size);
}

__HL_INLINE__ hl_slist_node* hl_slist_begin(const hl_slist* slist)
{
    hl_assert(slist != NULL);
    return slist->next;
}

__HL_INLINE__ hl_slist_node* hl_slist_end(const hl_slist* slist)
{
    return NULL;
}

__HL_INLINE__ void hl_slist_next(hl_slist_node** iter)
{
    hl_assert(iter != NULL);
    hl_return_check(*iter != NULL);
    *iter = (*iter)->next;
}

#endif // HL_LIST_H_
