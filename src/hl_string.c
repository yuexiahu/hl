#include "hl_string.h"
#include <stdarg.h>

HL_INLINE size_t hl_better_size(size_t size)
{
    size_t res = (__HL_STRING_SSO_LEN + 1) << 1;
    while(res < size)
        res <<= 1;
    return res;
}

void hl_string_new(hl_string* string)
{
    hl_assert(string != NULL);
    string->start = NULL;
    string->len = 0;
    string->cap = 0;
}

void hl_string_free(hl_string* string)
{
    hl_assert(string != NULL);
    if(string->start)
    {
        hl_free(string->start);
    }
    hl_string_new(string);
}

void hl_string_clear(hl_string* string)
{
    hl_assert(string != NULL);
    hl_string_cstr(string)[0] = '\0';
    string->len = 0;
}

void hl_string_clone(hl_string* string, const hl_string* from)
{
    hl_assert(string != NULL);
    if(from == NULL)
    {
        hl_string_clear(string);
        return;
    }
    size_t len = hl_string_len(from);
    hl_string_reserve(string, len);
    memcpy(hl_string_cstr(string), hl_string_cstr((hl_string*)from), len + 1);
    string->len = len;
}

void hl_string_clone_cstr(hl_string* string, const char* from)
{
    hl_assert(string != NULL);
    if(from == NULL)
    {
        hl_string_clear(string);
        return;
    }
    size_t len = strlen(from);
    hl_string_reserve(string, len);
    memcpy(hl_string_cstr(string), from, len + 1);
    string->len = len;
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
    memcpy(hl_string_cstr(string) + hl_string_len(string), hl_string_cstr((hl_string*)data), len + 1);
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
        memcpy(hl_string_cstr(string), hl_string_cstr((hl_string*)data), len);
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

int hl_string_sprintf(hl_string* string, const char* format, ...)
{
    hl_assert(string != NULL);
    va_list ap;
    int ret;
    char* start = hl_string_cstr(string);
    size_t max_size = hl_string_cap(string)+1;

    va_start(ap, format);
    ret = vsnprintf(start, max_size, format, ap);
    va_end(ap);

    if(ret < 0)
    {
        hl_string_clear(string);
    }
    else
    {
        string->len = ret;
    }

    return ret;
}

void hl_string_reserve(hl_string* string, size_t len_hint)
{
    hl_assert(string != NULL);
    if(len_hint <= hl_string_cap(string))
    {
        return;
    }

    size_t cap = hl_better_size(len_hint + 1);
    if(!string->start)
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
    if(!string->start)
    {
        return;
    }

    size_t len = hl_string_len(string);
    if(len <= __HL_STRING_SSO_LEN)
    {
        memcpy(string->sso, string->start, len + 1);
        hl_free(string->start);
        string->start = NULL;
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

void hl_string_swap(hl_string* string1, hl_string* string2)
{
    hl_assert(string1 != NULL && string2 != NULL);
    hl_string tmp;
    memcpy(&tmp, string1, sizeof(hl_string));
    memcpy(string1, string2, sizeof(hl_string));
    memcpy(string2, &tmp, sizeof(hl_string));
}
