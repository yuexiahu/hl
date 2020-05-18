#ifndef HL_STRING_H_
#define HL_STRING_H_

#include <stdlib.h>

#define HL_STRING_SSO_LEN 15

typedef struct hl_string
{
    char* start;
    size_t len;
    union {
        char sso[HL_STRING_SSO_LEN + 1];
        size_t cap;
    };
} hl_string;

void hl_string_new(hl_string* string);
void hl_string_free(hl_string* string);

void hl_string_clear(hl_string* string);
void hl_string_set(hl_string* string, const hl_string* data);
void hl_string_set_cstr(hl_string* string, const char* data);

#define hl_string_len(string) ((string)->len)
#define hl_string_cstr(string) ((string)->start)
size_t hl_string_cap(const hl_string* string);

void hl_string_append(hl_string* string, const hl_string* data);
void hl_string_append_cstr(hl_string* string, const char* data);
void hl_string_prepend(hl_string* string, const hl_string* data);
void hl_string_prepend_cstr(hl_string* string, const char* data);

void hl_string_reserve(hl_string* string, size_t len);
void hl_string_shrink_to_fit(hl_string* string);
void hl_string_swap(hl_string* string1, hl_string* string2);

#endif // HL_STRING_H_
