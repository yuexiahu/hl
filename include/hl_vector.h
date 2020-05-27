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
void hl_vector_set(hl_vector* vector, const hl_vector* data);
void hl_vector_set_array(hl_vector* vector, const void* data, size_t len);

__HL_INLINE__ size_t hl_vector_len(const hl_vector* vector) {
    hl_assert(vector != NULL);
    return vector->len;
}

__HL_INLINE__ size_t hl_vector_cap(const hl_vector* vector) {
    hl_assert(vector != NULL);
    return vector->cap;
}

__HL_INLINE__ void* hl_vector_array(const hl_vector* vector) {
    hl_assert(vector != NULL);
    return vector->items;
}

__HL_INLINE__ size_t hl_vector_item_size(const hl_vector* vector) {
    hl_assert(vector != NULL);
    return vector->item_size;
}

#define hl_vector_ref(type, vector, index) (*(type*)hl_vector_at((vector), index))

__HL_INLINE__ void* hl_vector_at(const hl_vector* vector, size_t index)
{
    hl_assert(vector != NULL);
    hl_return_v_check(index < hl_vector_len(vector), NULL);
    return (char*)vector->items + index * hl_vector_item_size(vector);
}

__HL_INLINE__ void hl_vector_get(const hl_vector* vector, size_t index, void* data)
{
    hl_return_check(data != NULL);
    memcpy(data, hl_vector_at(vector, index), hl_vector_item_size(vector));
}

int hl_vector_index_of(const hl_vector* vector, const void* item);

void hl_vector_remove_at(hl_vector* vector, size_t index);
void hl_vector_remove(hl_vector* vector, const void* item);
void hl_vector_remove_all(hl_vector* vector, const void* item);

void hl_vector_append(hl_vector* vector, const void* item);
void hl_vector_prepend(hl_vector* vector, const void* item);
void hl_vector_insert(hl_vector* vector, size_t index, const void* item);

void hl_vector_reserve(hl_vector* vector, size_t cap);
void hl_vector_shrink_to_fit(hl_vector* vector);
void hl_vector_swap(hl_vector* vector1, hl_vector* vector2);

#endif // HL_VECTOR_H_