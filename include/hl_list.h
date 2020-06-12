#ifndef HL_LIST_H_
#define HL_LIST_H_

#include "hl_defs.h"

typedef struct hl_list_node
{
    struct hl_list_node* prev;
    struct hl_list_node* next;
    char data[0];
} hl_list_node;

typedef struct hl_list
{
    hl_list_node* node;
} hl_list;

void hl_list_new(hl_list* list);
void hl_list_free(hl_list* list);

void hl_list_clear(hl_list* list);
void hl_list_clone(hl_list* list, const hl_list* from, size_t item_size);

HL_INLINE size_t hl_list_len(const hl_list* list)
{
    hl_assert(list != NULL);
    return *(size_t*)list->node->data;
}

void hl_list_append(hl_list* list, const void* item, size_t item_size);
void hl_list_prepend(hl_list* list, const void* item, size_t item_size);
void hl_list_insert(hl_list* list, hl_list_node* iter, const void* item, size_t item_size);
void hl_list_swap(hl_list* list1, hl_list* list2);
hl_list_node* hl_list_erase(hl_list* list, hl_list_node* iter);

#define hl_list_ref(type, iter) (*(type*)hl_list_at(iter))

HL_INLINE void* hl_list_at(hl_list_node* iter)
{
    hl_return_v_check(iter != NULL, NULL);
    return iter->data;
}

HL_INLINE void hl_list_get(hl_list_node* iter, void* item, size_t item_size)
{
    hl_return_check(item != NULL);
    memcpy(item, hl_list_at(iter), item_size);
}

HL_INLINE void hl_list_set(hl_list_node* iter, const void* item, size_t item_size)
{
    hl_return_check(item != NULL);
    memcpy(hl_list_at(iter), item, item_size);
}

HL_INLINE hl_list_node* hl_list_begin(const hl_list* list)
{
    hl_assert(list != NULL);
    return list->node->next;
}

HL_INLINE hl_list_node* hl_list_end(const hl_list* list)
{
    hl_assert(list != NULL);
    return list->node;
}

HL_INLINE void hl_list_next(hl_list_node** iter)
{
    hl_assert(iter != NULL && *iter != NULL);
    *iter = (*iter)->next;
}

HL_INLINE void hl_list_prev(hl_list_node** iter)
{
    hl_assert(iter != NULL && *iter != NULL);
    *iter = (*iter)->prev;
}

#endif // HL_LIST_H_
