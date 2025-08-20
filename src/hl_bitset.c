#include "hl_bitset.h"

HL_INLINE size_t hl_bitset_bytes_needed(size_t bit_count)
{
    return (bit_count + 7) / 8;
}

void hl_bitset_new(hl_bitset_t* bitset, size_t bit_count)
{
    hl_assert(bitset != NULL);
    bitset->bit_count = bit_count;
    if (bit_count == 0)
    {
        bitset->bits = NULL;
    }
    else
    {
        size_t bytes = hl_bitset_bytes_needed(bit_count);
        bitset->bits = (uint8_t*)hl_calloc(bytes, sizeof(uint8_t));
    }
}

void hl_bitset_free(hl_bitset_t* bitset)
{
    hl_assert(bitset != NULL);
    if (bitset->bits)
    {
        hl_free(bitset->bits);
    }
    bitset->bits = NULL;
    bitset->bit_count = 0;
}

void hl_bitset_init_adaptor(hl_bitset_t* bitset, uint8_t* buffer, size_t buffer_size)
{
    hl_assert(bitset != NULL);
    hl_assert(buffer != NULL);
    hl_assert(buffer_size > 0);

    bitset->bit_count = buffer_size * 8;
    bitset->bits = buffer;
}

void hl_bitset_clone(hl_bitset_t* dest, const hl_bitset_t* from)
{
    hl_assert(dest != NULL);
    if (from == NULL)
    {
        hl_bitset_free(dest);
        dest->bit_count = 0;
        dest->bits = NULL;
        return;
    }
    
    // 释放目标 bitset 原有内存
    if (dest->bits)
    {
        hl_free(dest->bits);
    }
    
    dest->bit_count = from->bit_count;
    if (from->bit_count == 0)
    {
        dest->bits = NULL;
    }
    else
    {
        size_t bytes = hl_bitset_bytes_needed(from->bit_count);
        dest->bits = (uint8_t*)hl_malloc(bytes);
        memcpy(dest->bits, from->bits, bytes);
    }
}

void hl_bitset_set(hl_bitset_t* bitset, size_t index)
{
    hl_assert(bitset != NULL);
    hl_return_check(index < bitset->bit_count);
    hl_return_check(bitset->bits != NULL);
    
    size_t byte_index = index / 8;
    size_t bit_index = index % 8;
    bitset->bits[byte_index] |= (1 << bit_index);
}

void hl_bitset_clear(hl_bitset_t* bitset, size_t index)
{
    hl_assert(bitset != NULL);
    hl_return_check(index < bitset->bit_count);
    hl_return_check(bitset->bits != NULL);
    
    size_t byte_index = index / 8;
    size_t bit_index = index % 8;
    bitset->bits[byte_index] &= ~(1 << bit_index);
}

BOOL hl_bitset_test(const hl_bitset_t* bitset, size_t index)
{
    hl_assert(bitset != NULL);
    hl_return_v_check(index < bitset->bit_count, FALSE);
    hl_return_v_check(bitset->bits != NULL, FALSE);
    
    size_t byte_index = index / 8;
    size_t bit_index = index % 8;
    return (bitset->bits[byte_index] & (1 << bit_index)) != 0;
}

void hl_bitset_swap(hl_bitset_t* bitset1, hl_bitset_t* bitset2)
{
    hl_assert(bitset1 != NULL && bitset2 != NULL);
    hl_bitset_t tmp;
    memcpy(&tmp, bitset1, sizeof(hl_bitset_t));
    memcpy(bitset1, bitset2, sizeof(hl_bitset_t));
    memcpy(bitset2, &tmp, sizeof(hl_bitset_t));
}

void hl_bitset_set_all(hl_bitset_t* bitset)
{
    hl_assert(bitset != NULL);
    hl_return_check(bitset->bits != NULL);
    
    size_t bytes = hl_bitset_bytes_needed(bitset->bit_count);
    memset(bitset->bits, 0xFF, bytes);
    
    // 清除最后一个字节中超出位数的位
    if (bitset->bit_count % 8 != 0)
    {
        size_t last_byte = bytes - 1;
        size_t valid_bits = bitset->bit_count % 8;
        uint8_t mask = (1 << valid_bits) - 1;
        bitset->bits[last_byte] &= mask;
    }
}

void hl_bitset_clear_all(hl_bitset_t* bitset)
{
    hl_assert(bitset != NULL);
    hl_return_check(bitset->bits != NULL);
    
    size_t bytes = hl_bitset_bytes_needed(bitset->bit_count);
    memset(bitset->bits, 0x00, bytes);
}

void hl_bitset_flip(hl_bitset_t* bitset, size_t index)
{
    hl_assert(bitset != NULL);
    hl_return_check(index < bitset->bit_count);
    hl_return_check(bitset->bits != NULL);
    
    size_t byte_index = index / 8;
    size_t bit_index = index % 8;
    bitset->bits[byte_index] ^= (1 << bit_index);
}

void hl_bitset_flip_all(hl_bitset_t* bitset)
{
    hl_assert(bitset != NULL);
    hl_return_check(bitset->bits != NULL);
    
    size_t bytes = hl_bitset_bytes_needed(bitset->bit_count);
    for (size_t i = 0; i < bytes; i++)
    {
        bitset->bits[i] = ~bitset->bits[i];
    }
    
    // 清除最后一个字节中超出位数的位
    if (bitset->bit_count % 8 != 0)
    {
        size_t last_byte = bytes - 1;
        size_t valid_bits = bitset->bit_count % 8;
        uint8_t mask = (1 << valid_bits) - 1;
        bitset->bits[last_byte] &= mask;
    }
}

void hl_bitset_and(hl_bitset_t* dest, const hl_bitset_t* src)
{
    hl_assert(dest != NULL && src != NULL);
    hl_return_check(dest->bit_count == src->bit_count);
    hl_return_check(dest->bits != NULL && src->bits != NULL);
    
    size_t bytes = hl_bitset_bytes_needed(dest->bit_count);
    for (size_t i = 0; i < bytes; i++)
    {
        dest->bits[i] &= src->bits[i];
    }
}

void hl_bitset_or(hl_bitset_t* dest, const hl_bitset_t* src)
{
    hl_assert(dest != NULL && src != NULL);
    hl_return_check(dest->bit_count == src->bit_count);
    hl_return_check(dest->bits != NULL && src->bits != NULL);
    
    size_t bytes = hl_bitset_bytes_needed(dest->bit_count);
    for (size_t i = 0; i < bytes; i++)
    {
        dest->bits[i] |= src->bits[i];
    }
}

void hl_bitset_xor(hl_bitset_t* dest, const hl_bitset_t* src)
{
    hl_assert(dest != NULL && src != NULL);
    hl_return_check(dest->bit_count == src->bit_count);
    hl_return_check(dest->bits != NULL && src->bits != NULL);
    
    size_t bytes = hl_bitset_bytes_needed(dest->bit_count);
    for (size_t i = 0; i < bytes; i++)
    {
        dest->bits[i] ^= src->bits[i];
    }
}

void hl_bitset_not(hl_bitset_t* bitset)
{
    hl_bitset_flip_all(bitset);
}

int hl_bitset_find_first_set(const hl_bitset_t* bitset)
{
    return hl_bitset_find_next_set(bitset, 0);
}

int hl_bitset_find_first_clear(const hl_bitset_t* bitset)
{
    return hl_bitset_find_next_clear(bitset, 0);
}

int hl_bitset_find_next_set(const hl_bitset_t* bitset, size_t start)
{
    hl_assert(bitset != NULL);
    hl_return_v_check(bitset->bits != NULL, -1);
    
    for (size_t i = start; i < bitset->bit_count; i++)
    {
        if (hl_bitset_test(bitset, i))
        {
            return (int)i;
        }
    }
    return -1;
}

int hl_bitset_find_next_clear(const hl_bitset_t* bitset, size_t start)
{
    hl_assert(bitset != NULL);
    hl_return_v_check(bitset->bits != NULL, -1);
    
    for (size_t i = start; i < bitset->bit_count; i++)
    {
        if (!hl_bitset_test(bitset, i))
        {
            return (int)i;
        }
    }
    return -1;
}

size_t hl_bitset_count_set(const hl_bitset_t* bitset)
{
    hl_assert(bitset != NULL);
    hl_return_v_check(bitset->bits != NULL, 0);
    
    size_t count = 0;
    size_t bytes = hl_bitset_bytes_needed(bitset->bit_count);
    
    for (size_t i = 0; i < bytes; i++)
    {
        uint8_t byte = bitset->bits[i];
        // 使用 Brian Kernighan 的算法计算字节中的设置位数
        while (byte)
        {
            count++;
            byte &= byte - 1; // 清除最低位的 1
        }
    }
    
    return count;
}

size_t hl_bitset_count_clear(const hl_bitset_t* bitset)
{
    hl_assert(bitset != NULL);
    return bitset->bit_count - hl_bitset_count_set(bitset);
}

BOOL hl_bitset_equals(const hl_bitset_t* bitset1, const hl_bitset_t* bitset2)
{
    hl_assert(bitset1 != NULL && bitset2 != NULL);
    
    if (bitset1->bit_count != bitset2->bit_count)
    {
        return FALSE;
    }
    
    if (bitset1->bits == NULL && bitset2->bits == NULL)
    {
        return TRUE;
    }
    
    if (bitset1->bits == NULL || bitset2->bits == NULL)
    {
        return FALSE;
    }
    
    size_t bytes = hl_bitset_bytes_needed(bitset1->bit_count);
    return memcmp(bitset1->bits, bitset2->bits, bytes) == 0;
}

BOOL hl_bitset_is_subset(const hl_bitset_t* subset, const hl_bitset_t* superset)
{
    hl_assert(subset != NULL && superset != NULL);
    hl_return_v_check(subset->bit_count == superset->bit_count, FALSE);
    hl_return_v_check(subset->bits != NULL && superset->bits != NULL, FALSE);
    
    size_t bytes = hl_bitset_bytes_needed(subset->bit_count);
    for (size_t i = 0; i < bytes; i++)
    {
        // 如果 subset 有任何位在 superset 中没有设置，则不是子集
        if ((subset->bits[i] & superset->bits[i]) != subset->bits[i])
        {
            return FALSE;
        }
    }
    return TRUE;
}
