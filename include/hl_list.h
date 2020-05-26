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
    size_t len;
    size_t item_size;
    hl_list_node* node;
} hl_list;

void hl_list_new(hl_list* list, size_t item_size);
void hl_list_free(hl_list* list);

void hl_list_clear(hl_list* list);
void hl_list_set(hl_list* list, const hl_list* data);

__HL_INLINE__ size_t hl_list_len(const hl_list* list)
{
    hl_assert(list != NULL);
    return list->len;
}

__HL_INLINE__ size_t hl_list_item_size(const hl_list* list)
{
    hl_assert(list != NULL);
    return list->item_size;
}

void hl_list_append(hl_list* list, const void* item);
void hl_list_prepend(hl_list* list, const void* item);
void hl_list_insert(hl_list* list, hl_list_node* iter, const void* item);
void hl_list_swap(hl_list* list1, hl_list* list2);
hl_list_node* hl_list_erase(hl_list* list, hl_list_node* iter);

#define hl_list_ref(type, iter) (*(type*)hl_list_at(iter))

__HL_INLINE__ void* hl_list_at(hl_list_node* iter)
{
    hl_return_v_check(iter != NULL, NULL);
    return iter->data;
}

__HL_INLINE__ void hl_list_get(hl_list_node* iter, void* data, size_t item_size)
{
    hl_return_check(data != NULL);
    memcpy(data, hl_list_at(iter), item_size);
}

__HL_INLINE__ hl_list_node* hl_list_begin(hl_list* list)
{
    hl_assert(list != NULL);
    return list->node->next;
}

__HL_INLINE__ hl_list_node* hl_list_end(hl_list* list)
{
    hl_assert(list != NULL);
    return list->node;
}

__HL_INLINE__ void hl_list_next(hl_list_node** iter)
{
    hl_assert(iter != NULL && *iter != NULL);
    *iter = (*iter)->next;
}

__HL_INLINE__ void hl_list_prev(hl_list_node** iter)
{
    hl_assert(iter != NULL && *iter != NULL);
    *iter = (*iter)->prev;
}


#endif // HL_LIST_H_
