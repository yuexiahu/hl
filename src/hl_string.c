#include "hl_string.h"

__HL_INLINE__ size_t hl_better_size(size_t size)
{
    size_t res = (__HL_STRING_SSO_LEN + 1) << 1;
    while(res < size)
        res <<= 1;
    return res;
}

void hl_string_new(hl_string* string)
{
    hl_assert(string != NULL);
    string->start = string->sso;
    string->len = 0;
    string->cap = 0;
}

void hl_string_free(hl_string* string)
{
    hl_assert(string != NULL);
    if(string->start != string->sso)
    {
        hl_free(string->start);
    }
    hl_string_new(string);
}

void hl_string_clear(hl_string* string)
{
    hl_assert(string != NULL);
    string->start[0] = 0;
    string->len = 0;
}

void hl_string_set(hl_string* string, const hl_string* data)
{
    hl_assert(string != NULL);
    if(data == NULL)
    {
        hl_string_clear(string);
        return;
    }
    size_t len = hl_string_len(data);
    hl_string_reserve(string, len);
    memcpy(string->start, data->start, len + 1);
    string->len = len;
}

void hl_string_set_cstr(hl_string* string, const char* data)
{
    hl_assert(string != NULL);
    if(data == NULL)
    {
        hl_string_clear(string);
        return;
    }
    size_t len = strlen(data);
    hl_string_reserve(string, len);
    memcpy(string->start, data, len + 1);
    string->len = len;
}

size_t hl_string_cap(const hl_string* string)
{
    hl_assert(string != NULL);
    if(string->start == string->sso)
    {
        return __HL_STRING_SSO_LEN;
    }
    return string->cap - 1;
}

void hl_string_append(hl_string* string, const hl_string* data)
{
    hl_assert(string != NULL);
    if(data == NULL)
    {
        return;
    }
    size_t len = hl_string_len(data);
    hl_string_reserve(string, hl_string_len(string) + len);
    memcpy(hl_string_cstr(string) + hl_string_len(string), hl_string_cstr(data), len + 1);
    string->len += len;
}

void hl_string_append_cstr(hl_string* string, const char* data)
{
    hl_assert(string != NULL);
    if(data == NULL)
    {
        return;
    }
    size_t len = strlen(data);
    hl_string_reserve(string, hl_string_len(string) + len);
    memcpy(hl_string_cstr(string) + hl_string_len(string), data, len + 1);
    string->len += len;
}

void hl_string_prepend(hl_string* string, const hl_string* data)
{
    hl_assert(string != NULL);
    if(data == NULL)
    {
        return;
    }
    size_t len = hl_string_len(data);
    if(len != 0)
    {
        hl_string_reserve(string, hl_string_len(string) + len);
        memmove(hl_string_cstr(string) + hl_string_len(data), hl_string_cstr(string), hl_string_len(string) + 1);
        memcpy(hl_string_cstr(string), hl_string_cstr(data), len);
        string->len += len;
    }
}

void hl_string_prepend_cstr(hl_string* string, const char* data)
{
    hl_assert(string != NULL);
    if(data == NULL)
    {
        return;
    }
    size_t len = strlen(data);
    if(len != 0)
    {
        hl_string_reserve(string, hl_string_len(string) + len);
        memmove(hl_string_cstr(string) + len, hl_string_cstr(string), hl_string_len(string) + 1);
        memcpy(hl_string_cstr(string), data, len);
        string->len += len;
    }
}

void hl_string_reserve(hl_string* string, size_t len)
{
    hl_assert(string != NULL);
    if(len <= hl_string_cap(string))
    {
        return;
    }

    size_t cap = hl_better_size(len + 1);
    if(string->start == string->sso)
    {
        string->start = hl_malloc(cap);
        strcpy(string->start, string->sso);
    }
    else
    {
        string->start = hl_realloc(string->start, cap);
    }
    string->cap = cap;
}

void hl_string_shrink_to_fit(hl_string* string)
{
    hl_assert(string != NULL);
    if(string->start == string->sso)
    {
        return;
    }

    size_t len = hl_string_len(string);
    if(len <= __HL_STRING_SSO_LEN)
    {
        memcpy(string->sso, string->start, len + 1);
        hl_free(string->start);
        string->start = string->sso;
    }
    else
    {
        size_t cap = hl_better_size(len + 1);
        if(cap != string->cap)
        {
            char* new = hl_malloc(cap);
            memcpy(new, string->start, len + 1);
            hl_free(string->start);
            string->start = new;
            string->cap = cap;
        }
    }
}

static inline void hl_string_move(hl_string* dest, hl_string* src)
{
    if(src->start != src->sso)
    {
        dest->start = src->start;
        dest->len = src->len;
        dest->cap = src->cap;
    }
    else
    {
        dest->start = dest->sso;
        dest->len = src->len;
        memcpy(dest->sso, src->sso, src->len + 1);
    }
}

void hl_string_swap(hl_string* string1, hl_string* string2)
{
    hl_assert(string1 != NULL && string2 != NULL);
    hl_string tmp;
    hl_string_move(&tmp, string1);
    hl_string_move(string1, string2);
    hl_string_move(string2, &tmp);
}
