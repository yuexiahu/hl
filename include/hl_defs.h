#ifndef HL_DEFS_
#define HL_DEFS_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#define HL_INLINE static inline

#define hl_assert assert
#define hl_log(fmt, ...)                                                                                               \
    fprintf(stdout,                                                                                                    \
            "hl_log: "__FILE__                                                                                         \
            ":%d:\n    " fmt "\n",                                                                                     \
            __LINE__, ##__VA_ARGS__)
#define hl_err(fmt, ...)                                                                                               \
    fprintf(stderr,                                                                                                    \
            "hl_err: "__FILE__                                                                                         \
            ":%d:\n    " fmt "\n",                                                                                     \
            __LINE__, ##__VA_ARGS__)

#define hl_break_check(exp)                                                                                            \
    if(!(exp))                                                                                                         \
    {                                                                                                                  \
        hl_err(#exp " check failed!");                                                                                 \
        break;                                                                                                         \
    }

#define hl_goto_check(exp, label)                                                                                      \
    if(!(exp))                                                                                                         \
    {                                                                                                                  \
        hl_err(#exp " check failed!");                                                                                 \
        goto label;                                                                                                    \
    }

#define hl_return_check(exp)                                                                                           \
    if(!(exp))                                                                                                         \
    {                                                                                                                  \
        hl_err(#exp " check failed!");                                                                                 \
        return;                                                                                                        \
    }

#define hl_return_v_check(exp, value)                                                                                  \
    if(!(exp))                                                                                                         \
    {                                                                                                                  \
        hl_err(#exp " check failed!");                                                                                 \
        return (value);                                                                                                \
    }


/// config allocator
#define hl_free free
#define hl_malloc malloc
#define hl_realloc realloc

HL_INLINE void* hl_calloc(size_t num, size_t size)
{
    size_t len = num * size;
    void* ret = malloc(len);
    memset(ret, 0, len);
    return ret;
}

#endif // HL_DEFS_
