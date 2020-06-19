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
size_t hl_hash_int(const void* int_key)
{
    const int* pint = int_key;
    if(pint == NULL)
    {
        return 0;
    }
    return *pint;
}
#define HL_HASH_INT(func, bit)                                                                                         \
    size_t func(const void* key)                                                                                       \
    {                                                                                                                  \
        const int##bit##_t* pint = key;                                                                                \
        if(pint == NULL)                                                                                               \
        {                                                                                                              \
            return 0;                                                                                                  \
        }                                                                                                              \
        return *pint;                                                                                                  \
    }
HL_HASH_INT(hl_hash_int8, 8)
HL_HASH_INT(hl_hash_int16, 16)
HL_HASH_INT(hl_hash_int32, 32)
HL_HASH_INT(hl_hash_int64, 64)

/// equals functions
BOOL hl_equals_cstr(const void* cstr_key1, const void* cstr_key2)
{
    if(cstr_key1 == NULL || cstr_key2 == NULL)
    {
        return cstr_key1 == cstr_key2;
    }
    return strcmp(cstr_key1, cstr_key2) == 0;
}
BOOL hl_equals_int(const void* int_key1, const void* int_key2)
{
    if(int_key1 == NULL || int_key2 == NULL)
    {
        return int_key1 == int_key2;
    }
    return *(int*)int_key1 == *(int*)int_key2;
}
#define HL_EQUALS_INT(func, bit)                                                                                       \
    BOOL func(const void* key1, const void* key2)                                                                      \
    {                                                                                                                  \
        if(key1 == NULL || key2 == NULL)                                                                               \
        {                                                                                                              \
            return key1 == key2;                                                                                       \
        }                                                                                                              \
        return *(int##bit##_t*)key1 == *(int##bit##_t*)key2;                                                           \
    }
HL_EQUALS_INT(hl_equals_int8, 8)
HL_EQUALS_INT(hl_equals_int16, 16)
HL_EQUALS_INT(hl_equals_int32, 32)
HL_EQUALS_INT(hl_equals_int64, 64)
