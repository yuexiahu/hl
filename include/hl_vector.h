#ifndef HL_VECTOR_H_
#define HL_VECTOR_H_

#include "hl_defs.h"

typedef struct hl_vector
{
    size_t len;
    size_t cap;
    size_t item_size;
    void* items;
} hl_vector;

void hl_vector_new(hl_vector* vector, size_t cap, size_t item_size);
void hl_vector_free(hl_vector* vector);

void hl_vector_clear(hl_vector* vector);
void hl_vector_clone(hl_vector* vector, const hl_vector* from);
void hl_vector_clone_array(hl_vector* vector, const void* from, size_t len);

HL_INLINE size_t hl_vector_len(const hl_vector* vector)
{
    hl_assert(vector != NULL);
    return vector->len;
}
HL_INLINE BOOL hl_vector_empty(const hl_vector* vector)
{
    return hl_vector_len(vector) == 0;
}

HL_INLINE size_t hl_vector_cap(const hl_vector* vector)
{
    hl_assert(vector != NULL);
    return vector->cap;
}

HL_INLINE void* hl_vector_array(const hl_vector* vector)
{
    hl_assert(vector != NULL);
    return vector->items;
}

HL_INLINE size_t hl_vector_item_size(const hl_vector* vector)
{
    hl_assert(vector != NULL);
    return vector->item_size;
}

#define hl_vector_ref(type, vector, index) (*(type*)hl_vector_at((vector), index))

HL_INLINE void* hl_vector_at(const hl_vector* vector, size_t index)
{
    hl_assert(vector != NULL);
    hl_return_v_check(index < hl_vector_len(vector), NULL);
    return (char*)vector->items + index * hl_vector_item_size(vector);
}

HL_INLINE void hl_vector_get(const hl_vector* vector, size_t index, void* data)
{
    hl_return_check(data != NULL);
    memcpy(data, hl_vector_at(vector, index), hl_vector_item_size(vector));
}

HL_INLINE void hl_vector_set(const hl_vector* vector, size_t index, const void* data)
{
    hl_return_check(data != NULL);
    memcpy(hl_vector_at(vector, index), data, hl_vector_item_size(vector));
}

size_t hl_vector_find(const hl_vector* vector, size_t start, const void* item,
                   BOOL (*equals)(const void* item1, const void* item2));
size_t hl_vector_find_if(const hl_vector* vector, size_t start, BOOL (*find_if)(const void* item));

void hl_vector_append(hl_vector* vector, const void* item);
void hl_vector_prepend(hl_vector* vector, const void* item);
void hl_vector_insert(hl_vector* vector, size_t index, const void* item);

void hl_vector_reserve(hl_vector* vector, size_t cap);
void hl_vector_shrink_to_fit(hl_vector* vector);
void hl_vector_swap(hl_vector* vector1, hl_vector* vector2);
void hl_vector_erase(hl_vector* vector, size_t index);

void hl_vector_sort(hl_vector* vector, BOOL (*less)(const void* item1, const void* item2));
size_t hl_vector_bsearch(const hl_vector* vector, const void* item,
                   BOOL (*less)(const void* item1, const void* item2));

HL_INLINE size_t hl_vector_begin(const hl_vector* vector)
{
    hl_assert(vector != NULL);
    return 0;
}

HL_INLINE size_t hl_vector_end(const hl_vector* vector)
{
    return hl_vector_len(vector);
}

HL_INLINE void* hl_vector_first(const hl_vector* vector)
{
    hl_assert(!hl_vector_empty(vector));
    return hl_vector_at(vector, 0);
}
HL_INLINE void* hl_vector_last(const hl_vector* vector)
{
    hl_assert(!hl_vector_empty(vector));
    return hl_vector_at(vector, hl_vector_len(vector) - 1);
}

#endif // HL_VECTOR_H_
