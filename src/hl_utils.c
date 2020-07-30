#include "hl_utils.h"

/// hash functions
size_t hl_hash_cstr(const void* cstr_key)
{
    size_t hash = 0;
    const char* cstr = cstr_key;
    if(cstr == NULL)
    {
        return 0;
    }

    while(*cstr)
    {
        hash = hash * 131 + *(cstr++);
    }
    return hash;
}

#define HL_HASH_INT(func, type)                                                                                        \
    size_t func(const void* key)                                                                                       \
    {                                                                                                                  \
        const type* pint = key;                                                                                        \
        if(pint == NULL)                                                                                               \
        {                                                                                                              \
            return 0;                                                                                                  \
        }                                                                                                              \
        return *pint;                                                                                                  \
    }

HL_HASH_INT(hl_hash_int, int)
HL_HASH_INT(hl_hash_int8, int8_t)
HL_HASH_INT(hl_hash_int16, int16_t)
HL_HASH_INT(hl_hash_int32, int32_t)
HL_HASH_INT(hl_hash_int64, int64_t)

/// equals functions
BOOL hl_equals_cstr(const void* cstr_key1, const void* cstr_key2)
{
    if(cstr_key1 == NULL || cstr_key2 == NULL)
    {
        return cstr_key1 == cstr_key2;
    }
    return strcmp(cstr_key1, cstr_key2) == 0;
}

#define HL_EQUALS_INT(func, type)                                                                                      \
    BOOL func(const void* key1, const void* key2)                                                                      \
    {                                                                                                                  \
        if(key1 == NULL || key2 == NULL)                                                                               \
        {                                                                                                              \
            return key1 == key2;                                                                                       \
        }                                                                                                              \
        return *(type*)key1 == *(type*)key2;                                                                           \
    }

HL_EQUALS_INT(hl_equals_int, int)
HL_EQUALS_INT(hl_equals_int8, int8_t)
HL_EQUALS_INT(hl_equals_int16, int16_t)
HL_EQUALS_INT(hl_equals_int32, int32_t)
HL_EQUALS_INT(hl_equals_int64, int64_t)

/// compare functions
BOOL hl_less_cstr(const void* cstr_key1, const void* cstr_key2)
{
    if(cstr_key1 == NULL || cstr_key2 == NULL)
    {
        return cstr_key1 < cstr_key2;
    }
    return strcmp(cstr_key1, cstr_key2) < 0;
}

#define HL_LESS_INT(func, type)                                                                                        \
    BOOL func(const void* key1, const void* key2)                                                                      \
    {                                                                                                                  \
        if(key1 == NULL || key2 == NULL)                                                                               \
        {                                                                                                              \
            return key1 < key2;                                                                                        \
        }                                                                                                              \
        return *(type*)key1 < *(type*)key2;                                                                            \
    }

HL_LESS_INT(hl_less_int, int)
HL_LESS_INT(hl_less_int8, int8_t)
HL_LESS_INT(hl_less_int16, int16_t)
HL_LESS_INT(hl_less_int32, int32_t)
HL_LESS_INT(hl_less_int64, int64_t)

HL_LESS_INT(hl_less_unsigned, unsigned)
HL_LESS_INT(hl_less_uint8, uint8_t)
HL_LESS_INT(hl_less_uint16, uint16_t)
HL_LESS_INT(hl_less_uint32, uint32_t)
HL_LESS_INT(hl_less_uint64, uint64_t)
