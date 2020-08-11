#include "hl_slist.h"
#include "hl_defs.h"
#include <sys/cdefs.h>

void hl_slist_new(hl_slist* slist)
{
    hl_assert(slist != NULL);
    slist->next = NULL;
}

void hl_slist_free(hl_slist* slist)
{
    hl_slist_clear(slist);
}

void hl_slist_clear(hl_slist* slist)
{
    hl_assert(slist != NULL);
    hl_slist_node* node = slist->next;
    while(node != NULL)
    {
        hl_slist_node* next = node->next;
        hl_free(node);
        node = next;
    }
    slist->next = NULL;
}

void hl_slist_clone(hl_slist* slist, const hl_slist* from, size_t item_size)
{
    hl_assert(slist != NULL);
    hl_slist_clear(slist);
    if(from == NULL)
    {
        return;
    }

    hl_slist_node* iter = slist;
    hl_slist_node* iter_data = hl_slist_begin(from);
    while(iter_data != hl_slist_end(from))
    {
        hl_slist_insert_after(slist, iter, hl_slist_at(iter_data), item_size);
        hl_slist_next(&iter);
        hl_slist_next(&iter_data);
    }
}

size_t hl_slist_len(const hl_slist* slist)
{
    hl_assert(slist != NULL);

    size_t len = 0;
    hl_slist_node* iter = hl_slist_begin(slist);
    while(iter != hl_slist_end(slist))
    {
        ++len;
        hl_slist_next(&iter);
    }
    return len;
}

hl_slist_node* hl_slist_find(hl_slist_node* begin, hl_slist_node* end, const void* item,
                             BOOL (*equals)(const void* item1, const void* item2))
{
    hl_assert(equals != NULL);

    hl_slist_node* iter;
    for(iter = begin; iter != end; hl_slist_next(&iter))
    {
        if(equals(item, hl_slist_at(iter)))
        {
            return iter;
        }
    }
    return end;
}

hl_slist_node* hl_slist_find_if(hl_slist_node* begin, hl_slist_node* end, BOOL (*find_if)(const void* item))
{
    hl_assert(find_if != NULL);

    hl_slist_node* iter;
    for(iter = begin; iter != end; hl_slist_next(&iter))
    {
        if(find_if(hl_slist_at(iter)))
        {
            return iter;
        }
    }
    return end;
}

void hl_slist_append(hl_slist* slist, const void* item, size_t item_size)
{
    hl_assert(slist != NULL);

    hl_slist_node* iter = hl_slist_end(slist);
    hl_slist_insert(slist, iter, item, item_size);
}

void hl_slist_prepend(hl_slist* slist, const void* item, size_t item_size)
{
    hl_assert(slist != NULL);

    hl_slist_insert_after(slist, slist, item, item_size);
}

void hl_slist_insert(hl_slist* slist, hl_slist_node* iter, const void* item, size_t item_size)
{
    hl_assert(slist != NULL);

    hl_slist_node* prev_iter = slist;
    while(prev_iter != hl_slist_end(slist))
    {
        if(prev_iter->next == iter)
        {
            break;
        }
        hl_slist_next(&prev_iter);
    }
    hl_slist_insert_after(slist, prev_iter, item, item_size);
}

void hl_slist_insert_after(hl_slist* slist, hl_slist_node* iter, const void* item, size_t item_size)
{
    hl_assert(slist != NULL);
    hl_return_check(iter != NULL);

    hl_slist_node* node = hl_malloc(sizeof(hl_slist_node) + item_size);
    memcpy(node->data, item, item_size);

    hl_slist_node* next = iter->next;
    iter->next = node;
    node->next = next;
}

void hl_slist_swap(hl_slist* slist1, hl_slist* slist2)
{
    hl_assert(slist1 != NULL && slist2 != NULL);
    hl_slist_node* tmp = slist1->next;
    slist1->next = slist2->next;
    slist2->next = tmp;
}

hl_slist_node* hl_slist_erase(hl_slist* slist, hl_slist_node* iter)
{
    hl_assert(slist != NULL);

    hl_slist_node* prev_iter = slist;
    while(prev_iter != hl_slist_end(slist))
    {
        if(prev_iter->next == iter)
        {
            break;
        }
        hl_slist_next(&prev_iter);
    }
    return hl_slist_erase_after(slist, prev_iter);
}

hl_slist_node* hl_slist_erase_after(hl_slist* slist, hl_slist_node* iter)
{
    hl_assert(slist != NULL);

    if(iter == hl_slist_end(slist))
    {
        return iter;
    }

    hl_slist_node* next = iter->next;
    iter->next = next ? next->next : NULL;
    hl_free(next);
    return next;
}

