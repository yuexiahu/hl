#ifndef HL_UTILS_H
#define HL_UTILS_H

#include "hl_defs.h"

/// hash functions
size_t hl_hash_cstr(const void* cstr_key);
size_t hl_hash_int(const void* int_key);
size_t hl_hash_int8(const void* int8_key);
size_t hl_hash_int16(const void* int16_key);
size_t hl_hash_int32(const void* int32_key);
size_t hl_hash_int64(const void* int64_key);

/// equals functions
BOOL hl_equals_cstr(const void* cstr_key1, const void* cstr_key2);
BOOL hl_equals_int(const void* int_key1, const void* int_key2);
BOOL hl_equals_int8(const void* int8_key1, const void* int8_key2);
BOOL hl_equals_int16(const void* int16_key1, const void* int16_key2);
BOOL hl_equals_int32(const void* int32_key1, const void* int32_key2);
BOOL hl_equals_int64(const void* int64_key1, const void* int64_key2);

#endif // HL_UTILS_H
