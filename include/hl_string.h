#ifndef HL_STRING_H_
#define HL_STRING_H_

#include "hl_defs.h"

typedef struct hl_string
{
    char* start;
    size_t len;
    union {
        char sso[__HL_STRING_SSO_LEN + 1];
        size_t cap;
    };
} hl_string;

void hl_string_new(hl_string* string);
void hl_string_free(hl_string* string);

void hl_string_clear(hl_string* string);
void hl_string_clone(hl_string* string, const hl_string* from);
void hl_string_clone_cstr(hl_string* string, const char* from);

HL_INLINE size_t hl_string_len(const hl_string* string)
{
    hl_assert(string != NULL);
    return string->len;
}

HL_INLINE char* hl_string_cstr(hl_string* string)
{
    hl_assert(string != NULL);
    return string->start ? string->start : string->sso;
}

HL_INLINE size_t hl_string_cap(const hl_string* string)
{
    hl_assert(string != NULL);
    return string->start ? string->cap - 1 : __HL_STRING_SSO_LEN;
}

void hl_string_append(hl_string* string, const hl_string* data);
void hl_string_append_cstr(hl_string* string, const char* data);
void hl_string_prepend(hl_string* string, const hl_string* data);
void hl_string_prepend_cstr(hl_string* string, const char* data);
int hl_string_sprintf(hl_string* string, const char* format, ...);

void hl_string_reserve(hl_string* string, size_t len_hint);
void hl_string_shrink_to_fit(hl_string* string);
void hl_string_swap(hl_string* string1, hl_string* string2);

#endif // HL_STRING_H_
