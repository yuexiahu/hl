#ifndef HL_DEFS_
#define HL_DEFS_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hl_free free
#define hl_malloc malloc
#define hl_realloc realloc

#ifndef BOOL
#define BOOL int
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#define __HL_INLINE__ static inline

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

#endif // HL_DEFS_
