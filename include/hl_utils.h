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
/// - FALSE: not equal
/// - TRUE: equal
BOOL hl_equals_cstr(const void* cstr_key1, const void* cstr_key2);
BOOL hl_equals_int(const void* int_key1, const void* int_key2);
BOOL hl_equals_int8(const void* int8_key1, const void* int8_key2);
BOOL hl_equals_int16(const void* int16_key1, const void* int16_key2);
BOOL hl_equals_int32(const void* int32_key1, const void* int32_key2);
BOOL hl_equals_int64(const void* int64_key1, const void* int64_key2);

/// compare functions
/// - FALSE: key1 great or equal then key2
/// - TRUE: key1 less then key2
BOOL hl_less_cstr(const void* cstr_key1, const void* cstr_key2);
BOOL hl_less_int(const void* int_key1, const void* int_key2);
BOOL hl_less_int8(const void* int8_key1, const void* int8_key2);
BOOL hl_less_int16(const void* int16_key1, const void* int16_key2);
BOOL hl_less_int32(const void* int32_key1, const void* int32_key2);
BOOL hl_less_int64(const void* int64_key1, const void* int64_key2);
BOOL hl_less_unsigned(const void* unsigned_key1, const void* unsigned_key2);
BOOL hl_less_uint8(const void* uint8_key1, const void* uint8_key2);
BOOL hl_less_uint16(const void* uint16_key1, const void* uint16_key2);
BOOL hl_less_uint32(const void* uint32_key1, const void* uint32_key2);
BOOL hl_less_uint64(const void* uint64_key1, const void* uint64_key2);

/// memory functions
void* hl_cleancopy(void* dst, const void* src, size_t size);

#endif // HL_UTILS_H
