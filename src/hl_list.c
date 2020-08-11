#include "hl_list.h"
#include "hl_defs.h"

void hl_list_new(hl_list* list)
{
    hl_assert(list != NULL);
    list->node = hl_malloc(sizeof(hl_list_node)+sizeof(size_t));
    list->node->next = list->node;
    list->node->prev = list->node;
    *(size_t*)list->node->data = 0;
}

void hl_list_free(hl_list* list)
{
    hl_list_clear(list);
    hl_free(list->node);
    list->node = NULL;
}

void hl_list_clear(hl_list* list)
{
    hl_assert(list != NULL);
    hl_list_node* node = list->node->next;
    while(node != list->node)
    {
        hl_list_node* next = node->next;
        hl_free(node);
        node = next;
    }
    list->node->next = list->node;
    list->node->prev = list->node;
    *(size_t*)list->node->data = 0;
}

void hl_list_clone(hl_list* list, const hl_list* from, size_t item_size)
{
    hl_assert(list != NULL);
    hl_list_clear(list);
    if(from == NULL)
    {
        return;
    }

    hl_list_node* iter = hl_list_begin(list);
    hl_list_node* iter_data = hl_list_begin(from);
    while(iter_data != hl_list_end(from))
    {
        hl_list_insert(list, iter, hl_list_at(iter_data), item_size);
        hl_list_next(&iter_data);
    }
}

hl_list_node* hl_list_find(hl_list_node* begin, hl_list_node* end, const void* item,
                             BOOL (*equals)(const void* item1, const void* item2))
{
    hl_assert(equals != NULL);

    hl_list_node* iter;
    for(iter = begin; iter != end; hl_list_next(&iter))
    {
        if(equals(item, hl_list_at(iter)))
        {
            return iter;
        }
    }
    return end;
}

hl_list_node* hl_list_find_if(hl_list_node* begin, hl_list_node* end, BOOL (*find_if)(const void* item))
{
    hl_assert(find_if != NULL);

    hl_list_node* iter;
    for(iter = begin; iter != end; hl_list_next(&iter))
    {
        if(find_if(hl_list_at(iter)))
        {
            return iter;
        }
    }
    return end;
}

void hl_list_append(hl_list* list, const void* item, size_t item_size)
{
    hl_assert(list != NULL);

    hl_list_node* iter = hl_list_end(list);
    hl_list_insert(list, iter, item, item_size);
}

void hl_list_prepend(hl_list* list, const void* item, size_t item_size)
{
    hl_assert(list != NULL);

    hl_list_node* iter = hl_list_begin(list);
    hl_list_insert(list, iter, item, item_size);
}

void hl_list_insert(hl_list* list, hl_list_node* iter, const void* item, size_t item_size)
{
    hl_assert(list != NULL && iter != NULL);

    hl_list_node* node = hl_malloc(sizeof(hl_list_node) + item_size);
    memcpy(node->data, item, item_size);

    hl_list_node* prev = iter->prev;
    prev->next = node;
    node->prev = prev;
    node->next = iter;
    iter->prev = node;

    *(size_t*)list->node->data += 1;
}

void hl_list_swap(hl_list* list1, hl_list* list2)
{
    hl_assert(list1 != NULL && list2 != NULL);
    hl_list tmp;
    memcpy(&tmp, list1, sizeof(hl_list));
    memcpy(list1, list2, sizeof(hl_list));
    memcpy(list2, &tmp, sizeof(hl_list));
}

hl_list_node* hl_list_erase(hl_list* list, hl_list_node* iter)
{
    hl_assert(iter != NULL);
    hl_assert(list != NULL);

    if(iter == hl_list_end(list))
    {
        return iter;
    }

    hl_list_node* next = iter->next;
    next->prev = iter->prev;
    iter->prev->next = next;
    hl_free(iter);

    *(size_t*)list->node->data -= 1;
    return next;
}

