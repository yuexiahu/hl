#include "simpletest.h"
#include "hl_string.h"

CASE(test_string_clone)
{
    hl_string str;
    hl_string str2;

    hl_string_new(&str);
    EXPECT_EQ_STR("", hl_string_cstr(&str));

    hl_string_new(&str2);
    EXPECT_EQ_STR("", hl_string_cstr(&str2));

    hl_string_clone_cstr(&str, NULL);
    EXPECT_EQ_STR("", hl_string_cstr(&str));
    EXPECT_EQ_INT(0, hl_string_len(&str));

    hl_string_clone(&str, NULL);
    EXPECT_EQ_STR("", hl_string_cstr(&str));
    EXPECT_EQ_INT(0, hl_string_len(&str));

    const char* cstrs[] = {
        "",
        "\0",
        "123",
        "123456789012345678901234567890",
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890",
        "123456789012345678901234567890",
        "123",
    };

    for(int i = 0; i < sizeof(cstrs) / sizeof(const char*); ++i)
    {
        hl_string_clone_cstr(&str, cstrs[i]);
        EXPECT_EQ_STR(cstrs[i], hl_string_cstr(&str));
        EXPECT_EQ_INT(strlen(cstrs[i]), hl_string_len(&str));

        hl_string_clone(&str2, &str);
        EXPECT_EQ_STR(cstrs[i], hl_string_cstr(&str2));
        EXPECT_EQ_INT(strlen(cstrs[i]), hl_string_len(&str2));
    }

    hl_string_free(&str2);
    hl_string_free(&str);
}

CASE(test_string_append)
{
    hl_string str;
    hl_string str2;

    hl_string_new(&str);
    hl_string_new(&str2);

    char cstr[1024] = "";
    const char* cstrs[] = {
        "",
        "\0",
        "[123]",
        "[123456789012345678901234567890]",
        "[123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890]",
        "[123456789012345678901234567890]",
        "[123]",
    };

    for(int i = 0; i < sizeof(cstrs) / sizeof(const char*); ++i)
    {
        hl_string_append_cstr(&str, cstrs[i]);
        strcat(cstr, cstrs[i]);
        EXPECT_EQ_STR(cstr, hl_string_cstr(&str));

        hl_string tmp;
        hl_string_new(&tmp);
        hl_string_clone_cstr(&tmp, cstrs[i]);
        hl_string_append(&str2, &tmp);
        EXPECT_EQ_STR(cstr, hl_string_cstr(&str2));
        hl_string_free(&tmp);
    }

    hl_string_append_cstr(&str, NULL);
    EXPECT_EQ_STR(hl_string_cstr(&str), hl_string_cstr(&str2));

    hl_string_append(&str, NULL);
    EXPECT_EQ_STR(hl_string_cstr(&str), hl_string_cstr(&str2));

    hl_string_free(&str);
    hl_string_free(&str2);
}

CASE(test_string_prepend)
{
    hl_string str;
    hl_string str2;

    hl_string_new(&str);
    hl_string_new(&str2);

    char cstr[1024] = "";
    char cstr2[1024] = "";
    const char* cstrs[] = {
        "",
        "\0",
        "[123]",
        "[123456789012345678901234567890]",
        "[123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890]",
        "[123456789012345678901234567890]",
        "[123]",
    };

    for(int i = 0; i < sizeof(cstrs) / sizeof(const char*); ++i)
    {
        hl_string_prepend_cstr(&str, cstrs[i]);
        strcpy(cstr2, cstr);
        strcpy(cstr, cstrs[i]);
        strcat(cstr, cstr2);
        EXPECT_EQ_STR(cstr, hl_string_cstr(&str));

        hl_string tmp;
        hl_string_new(&tmp);
        hl_string_clone_cstr(&tmp, cstrs[i]);
        hl_string_prepend(&str2, &tmp);
        EXPECT_EQ_STR(cstr, hl_string_cstr(&str2));
        hl_string_free(&tmp);
    }

    hl_string_prepend_cstr(&str, NULL);
    EXPECT_EQ_STR(hl_string_cstr(&str), hl_string_cstr(&str2));

    hl_string_prepend(&str, NULL);
    EXPECT_EQ_STR(hl_string_cstr(&str), hl_string_cstr(&str2));

    hl_string_free(&str);
    hl_string_free(&str2);
}

CASE(test_string_swap)
{
    hl_string str;
    hl_string str2;

    hl_string_new(&str);
    hl_string_new(&str2);

    hl_string_swap(&str, &str2);
    EXPECT_EQ_STR("", hl_string_cstr(&str));
    EXPECT_EQ_STR("", hl_string_cstr(&str2));

    hl_string_clone_cstr(&str, "1234567890");
    hl_string_swap(&str, &str2);
    EXPECT_EQ_STR("", hl_string_cstr(&str));
    EXPECT_EQ_STR("1234567890", hl_string_cstr(&str2));

    hl_string_clone_cstr(&str, "123456789012345678901234567890");
    hl_string_swap(&str, &str2);
    EXPECT_EQ_STR("1234567890", hl_string_cstr(&str));
    EXPECT_EQ_STR("123456789012345678901234567890", hl_string_cstr(&str2));

    hl_string_free(&str);
    hl_string_free(&str2);
}

CASE(test_string_reserve_and_fit)
{
    hl_string str;
    hl_string_new(&str);
    EXPECT_EQ_INT(__HL_STRING_SSO_LEN, hl_string_cap(&str));

    hl_string_reserve(&str, 1000);
    EXPECT_EQ_INT(1024 - 1, hl_string_cap(&str));

    hl_string_clone_cstr(&str, "123");
    hl_string_shrink_to_fit(&str);
    EXPECT_EQ_INT(__HL_STRING_SSO_LEN, hl_string_cap(&str));
    EXPECT_EQ_STR("123", hl_string_cstr(&str));

    hl_string_clone_cstr(&str, "12345678901234567890");
    EXPECT_EQ_INT(32 - 1, hl_string_cap(&str));
    hl_string_reserve(&str, 1000);
    EXPECT_EQ_INT(1024 - 1, hl_string_cap(&str));
    EXPECT_EQ_STR("12345678901234567890", hl_string_cstr(&str));

    hl_string_shrink_to_fit(&str);
    EXPECT_EQ_INT(32 - 1, hl_string_cap(&str));
    EXPECT_EQ_STR("12345678901234567890", hl_string_cstr(&str));

    hl_string_free(&str);
}

UNIT(test_string, test_string_clone, test_string_append, test_string_prepend, test_string_swap,
     test_string_reserve_and_fit)
