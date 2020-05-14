#include "hl_vector.h"
#include "hl_defs.h"

static inline size_t hl_better_size(size_t size)
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
        vector->cap = hl_better_size(cap);
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

void hl_vector_set(hl_vector* vector, const hl_vector* data)
{
    hl_assert(vector != NULL);
    if(data == NULL)
    {
        hl_vector_clear(vector);
        return;
    }
    hl_assert(hl_vector_item_size(vector) == hl_vector_item_size(data));

    hl_vector_reserve(vector, hl_vector_len(vector));
    memcpy(vector->items, data->items, hl_vector_len(vector) * hl_vector_item_size(vector));
    vector->len = hl_vector_len(data);
}

void hl_vector_set_array(hl_vector* vector, const void* data, size_t len)
{
    hl_assert(vector != NULL);
    if(data == NULL || len == 0)
    {
        hl_vector_clear(vector);
        return;
    }
    hl_vector_reserve(vector, len);
    memcpy(vector->items, data, len * hl_vector_item_size(vector));
    vector->len = len;
}

void* hl_vector_at(hl_vector* vector, size_t index)
{
    hl_assert(vector != NULL);
    hl_return_v_check(index < hl_vector_len(vector), NULL);
    return (char*)vector->items + index * hl_vector_item_size(vector);
}

int hl_vector_index_of(hl_vector* vector, const void* item)
{
    hl_assert(vector != NULL);
    char* p = vector->items;
    for(size_t i = 0; i < hl_vector_len(vector); ++i)
    {
        if(0 == memcmp(p, item, hl_vector_item_size(vector)))
        {
            return i;
        }
        p += hl_vector_item_size(vector);
    }
    return -1;
}

void hl_vector_remove_at(hl_vector* vector, size_t index)
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

void hl_vector_remove(hl_vector* vector, const void* item)
{
    hl_assert(vector != NULL);
    int index = hl_vector_index_of(vector, item);
    if(index != -1)
    {
        hl_vector_remove_at(vector, index);
    }
}

void hl_vector_remove_all(hl_vector* vector, const void* item)
{
    hl_assert(vector != NULL);
    char* p = vector->items;
    for(size_t i = 0; i < hl_vector_len(vector); ++i)
    {
        if(0 == memcmp(p, item, hl_vector_item_size(vector)))
        {
            hl_vector_remove_at(vector, i);
            continue;
        }
        p += hl_vector_item_size(vector);
    }
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

    size_t cap = hl_better_size(hl_vector_len(vector));
    if(cap != vector->cap)
    {
        void* new = hl_malloc(cap * hl_vector_item_size(vector));
        memcpy(new, vector->items, hl_vector_len(vector));
        hl_free(vector->items);
        vector->items = new;
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

