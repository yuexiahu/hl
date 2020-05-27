#include "hl_list.h"
#include "hl_defs.h"

void hl_list_new(hl_list* list, size_t item_size)
{
    hl_assert(list != NULL);
    hl_assert(item_size != 0);
    list->len = 0;
    list->item_size = item_size;
    list->node = hl_malloc(sizeof(hl_list_node));
    list->node->next = list->node;
    list->node->prev = list->node;
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
    list->len = 0;
    list->node->next = list->node;
    list->node->prev = list->node;
}

void hl_list_set(hl_list* list, const hl_list* data)
{
    hl_assert(list != NULL);
    hl_list_clear(list);
    if(data == NULL)
    {
        return;
    }

    list->item_size = data->item_size;
    hl_list_node* iter = hl_list_begin(list);
    while(iter != hl_list_end(list))
    {
        hl_list_append(list, hl_list_at(iter));
        hl_list_next(&iter);
    }
}

void hl_list_append(hl_list* list, const void* item)
{
    hl_list_node* iter = hl_list_end(list);
    hl_list_insert(list, iter, item);
}

void hl_list_prepend(hl_list* list, const void* item)
{
    hl_list_node* iter = hl_list_begin(list);
    hl_list_insert(list, iter, item);
}

void hl_list_insert(hl_list* list, hl_list_node* iter, const void* item)
{
    hl_assert(list != NULL && iter != NULL);

    hl_list_node* node = hl_malloc(sizeof(hl_list_node) + hl_list_item_size(list));
    memcpy(node->data, item, hl_list_item_size(list));

    hl_list_node* prev = iter->prev;
    prev->next = node;
    node->prev = prev;
    node->next = iter;
    iter->prev = node;

    list->len += 1;
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
    list->len -= 1;
    return next;
}

