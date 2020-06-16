#include "hl_vector.h"

HL_INLINE size_t hl_better_size(size_t size)
{
    size_t res = 8;
    while(res < size)
        res <<= 1;
    return res;
}

void hl_vector_new(hl_vector* vector, size_t cap, size_t item_size)
{
    hl_assert(vector != NULL);
    hl_assert(item_size != 0);
    vector->len = 0;
    vector->item_size = item_size;
    if(cap == 0)
    {
        vector->cap = 0;
        vector->items = NULL;
    }
    else
    {
        vector->cap = cap;
        vector->items = hl_malloc(vector->cap * item_size);
    }
}

void hl_vector_free(hl_vector* vector)
{
    hl_assert(vector != NULL);
    if(vector->items)
    {
        hl_free(vector->items);
    }
    vector->items = NULL;
    vector->len = 0;
    vector->cap = 0;
}

void hl_vector_clear(hl_vector* vector)
{
    hl_assert(vector != NULL);
    vector->len = 0;
}

void hl_vector_clone(hl_vector* vector, const hl_vector* from)
{
    hl_assert(vector != NULL);
    if(from == NULL)
    {
        hl_vector_clear(vector);
        return;
    }
    hl_assert(hl_vector_item_size(vector) == hl_vector_item_size(from));

    hl_vector_reserve(vector, hl_vector_len(vector));
    memcpy(vector->items, from->items, hl_vector_len(vector) * hl_vector_item_size(vector));
    vector->len = hl_vector_len(from);
}

void hl_vector_clone_array(hl_vector* vector, const void* from, size_t len)
{
    hl_assert(vector != NULL);
    if(from == NULL || len == 0)
    {
        hl_vector_clear(vector);
        return;
    }
    hl_vector_reserve(vector, len);
    memcpy(vector->items, from, len * hl_vector_item_size(vector));
    vector->len = len;
}

int hl_vector_find(const hl_vector* vector, const void* item, size_t start, BOOL(*equals)(const void* item1, const void* item2))
{
    hl_assert(vector != NULL);
    char* p = vector->items + start*hl_vector_item_size(vector);
    for(size_t i = start; i < hl_vector_len(vector); ++i)
    {
        if(equals == NULL)
        {
            if(0 == memcmp(p, item, hl_vector_item_size(vector)))
            {
                return i;
            }
        }
        else
        {
            if(equals(p, item))
            {
                return i;
            }
        }
        p += hl_vector_item_size(vector);
    }
    return -1;
}

int hl_vector_find_if(const hl_vector* vector, size_t start, BOOL(*find_if)(const void* item))
{
    hl_assert(vector != NULL && find_if != NULL);

    char* p = vector->items + start*hl_vector_item_size(vector);
    for(size_t i = start; i < hl_vector_len(vector); ++i)
    {
        if(find_if(p))
        {
            return i;
        }
        p += hl_vector_item_size(vector);
    }
    return -1;
}

void hl_vector_append(hl_vector* vector, const void* item)
{
    hl_vector_insert(vector, hl_vector_len(vector), item);
}

void hl_vector_prepend(hl_vector* vector, const void* item)
{
    hl_vector_insert(vector, 0, item);
}

void hl_vector_insert(hl_vector* vector, size_t index, const void* item)
{
    hl_return_check(index <= hl_vector_len(vector));
    hl_vector_reserve(vector, hl_vector_len(vector) + 1);

    size_t move_cnt = hl_vector_len(vector) - index;
    if(move_cnt > 0)
    {
        void* start = vector->items + hl_vector_item_size(vector) * index;
        memmove(start + hl_vector_item_size(vector), start, move_cnt * hl_vector_item_size(vector));
    }
    vector->len += 1;
    memcpy(hl_vector_at(vector, index), item, hl_vector_item_size(vector));
}

void hl_vector_reserve(hl_vector* vector, size_t cap)
{
    hl_assert(vector != NULL);

    if(cap <= hl_vector_cap(vector))
    {
        return;
    }

    cap = hl_better_size(cap);
    vector->cap = cap;
    vector->items = hl_realloc(vector->items, cap * hl_vector_item_size(vector));
}

void hl_vector_shrink_to_fit(hl_vector* vector)
{
    hl_assert(vector != NULL);

    size_t cap = hl_vector_len(vector);
    if(cap != vector->cap)
    {
        void* new = NULL;
        if(cap > 0)
        {
            new = hl_malloc(cap * hl_vector_item_size(vector));
            memcpy(new, vector->items, hl_vector_len(vector));
        }
        hl_free(vector->items);
        vector->items = new;
        vector->cap = cap;
    }
}

void hl_vector_swap(hl_vector* vector1, hl_vector* vector2)
{
    hl_assert(vector1 != NULL && vector2 != NULL);
    hl_vector tmp;
    memcpy(&tmp, vector1, sizeof(hl_vector));
    memcpy(vector1, vector2, sizeof(hl_vector));
    memcpy(vector2, &tmp, sizeof(hl_vector));
}

void hl_vector_erase(hl_vector* vector, size_t index)
{
    hl_assert(vector != NULL);
    hl_return_check(index < hl_vector_len(vector));
    void* pos = hl_vector_at(vector, index);
    size_t move_cnt = hl_vector_len(vector) - index - 1;

    if(move_cnt > 0)
    {
        memmove(pos, pos + hl_vector_item_size(vector), move_cnt * hl_vector_item_size(vector));
    }
    vector->len -= 1;
}

