#include "hl_slist.h"
#include "simpletest.h"
#include "hl_utils.h"

CASE(test_slist_get_and_append)
{
    hl_slist slist;
    hl_slist_node* iter;
    int i;
    hl_slist_new(&slist);
    EXPECT_EQ_INT(0, hl_slist_len(&slist));

    for(i = 0; i < 10; ++i)
    {
        hl_slist_append(&slist, &i, sizeof(int));
        EXPECT_EQ_INT(i + 1, hl_slist_len(&slist));
    }
    iter = hl_slist_begin(&slist);
    i = 0;
    while(iter != hl_slist_end(&slist))
    {
        EXPECT_EQ_INT(i, hl_slist_ref(int, iter));
        hl_slist_next(&iter);
        ++i;
    }
    EXPECT_EQ_INT(10, i);
    EXPECT_EQ_INT(0, *(int *)hl_slist_first(&slist));

    hl_slist_free(&slist);

    hl_slist_new(&slist);
    EXPECT_EQ_INT(0, hl_slist_len(&slist));

    char ch = 0;
    for(i = 0; i < 10; ++i)
    {
        hl_slist_append(&slist, &ch, sizeof(char));
        EXPECT_EQ_INT(i + 1, hl_slist_len(&slist));
        ++ch;
    }
    iter = hl_slist_begin(&slist);
    i = 0;
    while(iter != hl_slist_end(&slist))
    {
        EXPECT_EQ_INT(i, hl_slist_ref(char, iter));
        hl_slist_next(&iter);
        ++i;
    }
    EXPECT_EQ_INT(10, i);
    EXPECT_EQ_INT(0, *(char *)hl_slist_first(&slist));

    hl_slist_free(&slist);

    double double_num = 0;
    hl_slist_new(&slist);
    EXPECT_EQ_INT(0, hl_slist_len(&slist));

    for(i = 0; i < 10; ++i)
    {
        hl_slist_append(&slist, &double_num, sizeof(double));
        EXPECT_EQ_INT(i + 1, hl_slist_len(&slist));
        ++double_num;
    }
    iter = hl_slist_begin(&slist);
    i = 0;
    while(iter != hl_slist_end(&slist))
    {
        EXPECT_EQ_DOUBLE(i, hl_slist_ref(double, iter));
        hl_slist_next(&iter);
        ++i;
    }
    EXPECT_EQ_INT(10, i);
    EXPECT_EQ_DOUBLE(0, *(double *)hl_slist_first(&slist));

    hl_slist_free(&slist);
}

CASE(test_slist_prepend)
{
    hl_slist slist;
    hl_slist_node* iter;
    int i;
    hl_slist_new(&slist);
    EXPECT_EQ_INT(0, hl_slist_len(&slist));

    for(i = 0; i < 10; ++i)
    {
        hl_slist_prepend(&slist, &i, sizeof(int));
        EXPECT_EQ_INT(i + 1, hl_slist_len(&slist));
    }

    iter = hl_slist_begin(&slist);
    i = 0;
    while(iter != hl_slist_end(&slist))
    {
        EXPECT_EQ_INT(10 - 1 - i, hl_slist_ref(int, iter));
        hl_slist_next(&iter);
        ++i;
    }
    EXPECT_EQ_INT(10, i);

    hl_slist_free(&slist);

    hl_slist_new(&slist);
    EXPECT_EQ_INT(0, hl_slist_len(&slist));

    char ch = 0;
    for(i = 0; i < 10; ++i)
    {
        hl_slist_prepend(&slist, &ch, sizeof(char));
        EXPECT_EQ_INT(i + 1, hl_slist_len(&slist));
        ++ch;
    }

    iter = hl_slist_begin(&slist);
    i = 0;
    while(iter != hl_slist_end(&slist))
    {
        EXPECT_EQ_INT(10 - 1 - i, hl_slist_ref(char, iter));
        hl_slist_next(&iter);
        ++i;
    }
    EXPECT_EQ_INT(10, i);

    hl_slist_free(&slist);

    double double_num = 0;
    hl_slist_new(&slist);
    EXPECT_EQ_INT(0, hl_slist_len(&slist));

    for(i = 0; i < 10; ++i)
    {
        hl_slist_prepend(&slist, &double_num, sizeof(double));
        EXPECT_EQ_INT(i + 1, hl_slist_len(&slist));
        ++double_num;
    }

    iter = hl_slist_begin(&slist);
    i = 0;
    while(iter != hl_slist_end(&slist))
    {
        EXPECT_EQ_DOUBLE(10 - 1 - i, hl_slist_ref(double, iter));
        hl_slist_next(&iter);
        ++i;
    }
    EXPECT_EQ_INT(10, i);

    hl_slist_free(&slist);
}

CASE(test_slist_insert)
{
    hl_slist slist;
    int i;

    hl_slist_new(&slist);
    for(i = 0; i < 10; ++i)
    {
        hl_slist_append(&slist, &i, sizeof(int));
    }

    hl_slist_node* iter = hl_slist_begin(&slist);
    for(i = 0; i < 5; ++i)
    {
        hl_slist_next(&iter);
    }

    for(i = 0; i < 10; ++i)
    {
        hl_slist_insert(&slist, iter, &i, sizeof(int));
    }
    int data2[] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 5, 6, 7, 8, 9};

    iter = hl_slist_begin(&slist);
    for(i = 0; i < sizeof(data2) / sizeof(int); ++i)
    {
        EXPECT_EQ_INT(data2[i], hl_slist_ref(int, iter));
        hl_slist_next(&iter);
    }

    hl_slist_free(&slist);
}

CASE(test_slist_insert_after)
{
    hl_slist slist;
    int i;

    hl_slist_new(&slist);
    for(i = 0; i < 10; ++i)
    {
        hl_slist_append(&slist, &i, sizeof(int));
    }

    hl_slist_node* iter = hl_slist_begin(&slist);
    for(i = 0; i < 5; ++i)
    {
        hl_slist_next(&iter);
    }

    for(int i = 0; i < 10; ++i)
    {
        hl_slist_insert_after(&slist, iter, &i, sizeof(int));
    }
    int data2[] = {0, 1, 2, 3, 4, 5, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 6, 7, 8, 9};

    iter = hl_slist_begin(&slist);
    for(i = 0; i < sizeof(data2) / sizeof(int); ++i)
    {
        EXPECT_EQ_INT(data2[i], hl_slist_ref(int, iter));
        hl_slist_next(&iter);
    }

    hl_slist_free(&slist);
}

CASE(test_slist_swap)
{
    hl_slist slist1;
    hl_slist slist2;
    hl_slist_node* iter;
    int i;

    hl_slist_new(&slist1);
    hl_slist_new(&slist2);

    for(i = 0; i < 10; ++i)
    {
        hl_slist_append(&slist1, &i, sizeof(int));
    }
    EXPECT_EQ_INT(10, hl_slist_len(&slist1));
    EXPECT_EQ_INT(0, hl_slist_len(&slist2));

    hl_slist_swap(&slist1, &slist2);
    EXPECT_EQ_INT(0, hl_slist_len(&slist1));
    EXPECT_EQ_INT(10, hl_slist_len(&slist2));

    iter = hl_slist_begin(&slist2);
    i = 0;
    while(iter != hl_slist_end(&slist2))
    {
        REQUIRE_EQ_INT(i, hl_slist_ref(int, iter));
        hl_slist_next(&iter);
        ++i;
    }

    hl_slist_free(&slist1);
    hl_slist_free(&slist2);
}

CASE(test_slist_clear_and_clone)
{
    hl_slist slist;
    hl_slist slist2;
    int i;

    hl_slist_new(&slist);
    hl_slist_new(&slist2);
    for(i = 0; i < 10; ++i)
    {
        hl_slist_append(&slist, &i, sizeof(int));
    }

    EXPECT_EQ_INT(10, hl_slist_len(&slist));
    hl_slist_clear(&slist);

    EXPECT_EQ_INT(0, hl_slist_len(&slist));
    for(i = 0; i < 10; ++i)
    {
        hl_slist_append(&slist, &i, sizeof(int));
    }
    EXPECT_EQ_INT(10, hl_slist_len(&slist));

    hl_slist_clone(&slist2, &slist, sizeof(int));
    EXPECT_EQ_INT(10, hl_slist_len(&slist2));
    hl_slist_node* iter = hl_slist_begin(&slist2);
    i = 0;
    while(iter != hl_slist_end(&slist2))
    {
        EXPECT_EQ_INT(i, hl_slist_ref(int, iter));
        hl_slist_next(&iter);
        ++i;
    }

    hl_slist_free(&slist);
    hl_slist_free(&slist2);
}

static int s_find_int;
static BOOL find_if_int(const void* item)
{
    int i = *(const int*)item;
    return i == s_find_int;
}

CASE(test_slist_find)
{
    hl_slist slist;
    int i;
    hl_slist_node* iter;
    hl_slist_new(&slist);

    for(i = 0; i < 10; ++i)
    {
        hl_slist_append(&slist, &i, sizeof(int));
    }

    for(i = 0; i < 10; ++i)
    {
        iter = hl_slist_find(hl_slist_begin(&slist), hl_slist_end(&slist), &i, hl_equals_int);
        EXPECT_EQ_INT(i, hl_slist_ref(int, iter));
        s_find_int = i;
        iter = hl_slist_find_if(hl_slist_begin(&slist), hl_slist_end(&slist), find_if_int);
        EXPECT_EQ_INT(i, hl_slist_ref(int, iter));
    }

    hl_slist_free(&slist);
}

CASE(test_slist_erase)
{
    hl_slist slist;
    int i;
    const int count = 100;
    hl_slist_node* iter;

    hl_slist_new(&slist);
    for(i = 0; i < count; ++i)
    {
        hl_slist_append(&slist, &i, sizeof(int));
    }
    EXPECT_EQ_INT(count, hl_slist_len(&slist));


    for(i = 0; i < count; ++i)
    {
        iter = hl_slist_find(hl_slist_begin(&slist), hl_slist_end(&slist), &i, hl_equals_int);
        if(iter != hl_slist_end(&slist))
        {
            EXPECT_EQ_INT(i, hl_slist_ref(int, iter));
            hl_slist_erase(&slist, iter);
            EXPECT_EQ_INT(count-i-1, hl_slist_len(&slist));
            EXPECT(hl_slist_end(&slist) == hl_slist_find(hl_slist_begin(&slist), hl_slist_end(&slist), &i, hl_equals_int));
        }
    }
    hl_slist_free(&slist);
}

CASE(test_slist_erase_after)
{
    hl_slist slist;
    int i;
    const int count = 100;
    hl_slist_node* iter;

    hl_slist_new(&slist);
    for(i = 0; i < count; ++i)
    {
        hl_slist_append(&slist, &i, sizeof(int));
    }
    EXPECT_EQ_INT(count, hl_slist_len(&slist));


    for(i = 0; i < count; ++i)
    {
        iter = hl_slist_find(hl_slist_begin(&slist), hl_slist_end(&slist), &i, hl_equals_int);
        if(iter != hl_slist_end(&slist))
        {
            EXPECT_EQ_INT(i, hl_slist_ref(int, iter));
            hl_slist_erase_after(&slist, iter);
            EXPECT_EQ_INT(count-i/2-1, hl_slist_len(&slist));
            i+=1;
            EXPECT(hl_slist_end(&slist) == hl_slist_find(hl_slist_begin(&slist), hl_slist_end(&slist), &i, hl_equals_int));
        }
    }
    hl_slist_free(&slist);
}

UNIT(test_slist, test_slist_get_and_append, test_slist_prepend, test_slist_insert, test_slist_insert_after, test_slist_swap,
     test_slist_clear_and_clone, test_slist_find, test_slist_erase, test_slist_erase_after)
