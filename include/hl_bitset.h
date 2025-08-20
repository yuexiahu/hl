#ifndef HL_BITSET_H
#define HL_BITSET_H

#include "hl_defs.h"

typedef struct {
    size_t bit_count; // 位数
    uint8_t* bits;    // 位数组指针
} hl_bitset_t;

void hl_bitset_new(hl_bitset_t* bitset, size_t bit_count);
void hl_bitset_free(hl_bitset_t* bitset);
void hl_bitset_init_adaptor(hl_bitset_t* bitset, uint8_t* buffer, size_t buffer_size);

void hl_bitset_clone(hl_bitset_t* dest, const hl_bitset_t* from);
void hl_bitset_set(hl_bitset_t* bitset, size_t index);
void hl_bitset_clear(hl_bitset_t* bitset, size_t index);
BOOL hl_bitset_test(const hl_bitset_t* bitset, size_t index);

void hl_bitset_swap(hl_bitset_t* bitset1, hl_bitset_t* bitset2);

HL_INLINE size_t hl_bitset_count(const hl_bitset_t* bitset)
{
    hl_assert(bitset != NULL);
    return bitset->bit_count;
}

HL_INLINE BOOL hl_bitset_empty(const hl_bitset_t* bitset)
{
    return hl_bitset_count(bitset) == 0;
}

HL_INLINE uint8_t* hl_bitset_array(const hl_bitset_t* bitset)
{
    hl_assert(bitset != NULL);
    return bitset->bits;
}

// 额外实用功能
void hl_bitset_set_all(hl_bitset_t* bitset);
void hl_bitset_clear_all(hl_bitset_t* bitset);
void hl_bitset_flip(hl_bitset_t* bitset, size_t index);
void hl_bitset_flip_all(hl_bitset_t* bitset);

// 位操作
void hl_bitset_and(hl_bitset_t* dest, const hl_bitset_t* src);
void hl_bitset_or(hl_bitset_t* dest, const hl_bitset_t* src);
void hl_bitset_xor(hl_bitset_t* dest, const hl_bitset_t* src);
void hl_bitset_not(hl_bitset_t* bitset);

// 查找功能
int hl_bitset_find_first_set(const hl_bitset_t* bitset);
int hl_bitset_find_first_clear(const hl_bitset_t* bitset);
int hl_bitset_find_next_set(const hl_bitset_t* bitset, size_t start);
int hl_bitset_find_next_clear(const hl_bitset_t* bitset, size_t start);

// 统计功能
size_t hl_bitset_count_set(const hl_bitset_t* bitset);
size_t hl_bitset_count_clear(const hl_bitset_t* bitset);

// 比较功能
BOOL hl_bitset_equals(const hl_bitset_t* bitset1, const hl_bitset_t* bitset2);
BOOL hl_bitset_is_subset(const hl_bitset_t* subset, const hl_bitset_t* superset);

#endif // HL_BITSET_H