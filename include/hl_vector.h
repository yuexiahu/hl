#ifndef HL_VECTOR_H_
#define HL_VECTOR_H_

#include <stdlib.h>

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
#define hl_vector_len(vector) ((vector)->len)
#define hl_vector_cap(vector) ((vector)->cap)
#define hl_vector_array(vector) ((vector)->items)
#define hl_vector_item_size(vector) ((vector)->item_size)
#define hl_vector_get(type, vector, index) (*(type*)hl_vector_at((vector), index))

void* hl_vector_at(hl_vector* vector, size_t index);
int hl_vector_index_of(hl_vector* vector, const void* item);

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
