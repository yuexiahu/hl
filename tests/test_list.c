#include "hl_list.h"
#include "simpletest.h"
#include "hl_utils.h"

CASE(test_list_get_and_append)
{
    hl_list list;
    hl_list_node* iter;
    int i;
    hl_list_new(&list);
    EXPECT_EQ_INT(0, hl_list_len(&list));

    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &i, sizeof(int));
        EXPECT_EQ_INT(i + 1, hl_list_len(&list));
    }
    iter = hl_list_begin(&list);
    i = 0;
    while(iter != hl_list_end(&list))
    {
        EXPECT_EQ_INT(i, hl_list_ref(int, iter));
        hl_list_next(&iter);
        ++i;
    }
    EXPECT_EQ_INT(10, i);
    EXPECT_EQ_INT(0, *(int *)hl_list_first(&list));
    EXPECT_EQ_INT(9, *(int *)hl_list_last(&list));

    hl_list_free(&list);

    hl_list_new(&list);
    EXPECT_EQ_INT(0, hl_list_len(&list));

    char ch = 0;
    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &ch, sizeof(char));
        EXPECT_EQ_INT(i + 1, hl_list_len(&list));
        ++ch;
    }
    iter = hl_list_begin(&list);
    i = 0;
    while(iter != hl_list_end(&list))
    {
        EXPECT_EQ_INT(i, hl_list_ref(char, iter));
        hl_list_next(&iter);
        ++i;
    }
    EXPECT_EQ_INT(10, i);
    EXPECT_EQ_INT(0, *(char *)hl_list_first(&list));
    EXPECT_EQ_INT(9, *(char *)hl_list_last(&list));

    hl_list_free(&list);

    double double_num = 0;
    hl_list_new(&list);
    EXPECT_EQ_INT(0, hl_list_len(&list));

    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &double_num, sizeof(double));
        EXPECT_EQ_INT(i + 1, hl_list_len(&list));
        ++double_num;
    }
    iter = hl_list_begin(&list);
    i = 0;
    while(iter != hl_list_end(&list))
    {
        EXPECT_EQ_DOUBLE(i, hl_list_ref(double, iter));
        hl_list_next(&iter);
        ++i;
    }
    EXPECT_EQ_INT(10, i);
    EXPECT_EQ_DOUBLE(0, *(double *)hl_list_first(&list));
    EXPECT_EQ_DOUBLE(9, *(double *)hl_list_last(&list));

    hl_list_free(&list);
}

CASE(test_list_prepend)
{
    hl_list list;
    hl_list_node* iter;
    int i;
    hl_list_new(&list);
    EXPECT_EQ_INT(0, hl_list_len(&list));

    for(i = 0; i < 10; ++i)
    {
        hl_list_prepend(&list, &i, sizeof(int));
        EXPECT_EQ_INT(i + 1, hl_list_len(&list));
    }

    iter = hl_list_begin(&list);
    i = 0;
    while(iter != hl_list_end(&list))
    {
        EXPECT_EQ_INT(10 - 1 - i, hl_list_ref(int, iter));
        hl_list_next(&iter);
        ++i;
    }
    EXPECT_EQ_INT(10, i);

    hl_list_free(&list);

    hl_list_new(&list);
    EXPECT_EQ_INT(0, hl_list_len(&list));

    char ch = 0;
    for(i = 0; i < 10; ++i)
    {
        hl_list_prepend(&list, &ch, sizeof(char));
        EXPECT_EQ_INT(i + 1, hl_list_len(&list));
        ++ch;
    }

    iter = hl_list_begin(&list);
    i = 0;
    while(iter != hl_list_end(&list))
    {
        EXPECT_EQ_INT(10 - 1 - i, hl_list_ref(char, iter));
        hl_list_next(&iter);
        ++i;
    }
    EXPECT_EQ_INT(10, i);

    hl_list_free(&list);

    double double_num = 0;
    hl_list_new(&list);
    EXPECT_EQ_INT(0, hl_list_len(&list));

    for(i = 0; i < 10; ++i)
    {
        hl_list_prepend(&list, &double_num, sizeof(double));
        EXPECT_EQ_INT(i + 1, hl_list_len(&list));
        ++double_num;
    }

    iter = hl_list_begin(&list);
    i = 0;
    while(iter != hl_list_end(&list))
    {
        EXPECT_EQ_DOUBLE(10 - 1 - i, hl_list_ref(double, iter));
        hl_list_next(&iter);
        ++i;
    }
    EXPECT_EQ_INT(10, i);

    hl_list_free(&list);
}

CASE(test_list_insert)
{
    hl_list list;
    int i;

    hl_list_new(&list);
    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &i, sizeof(int));
    }

    hl_list_node* iter = hl_list_begin(&list);
    for(i = 0; i < 5; ++i)
    {
        hl_list_next(&iter);
    }

    for(i = 0; i < 10; ++i)
    {
        hl_list_insert(&list, iter, &i, sizeof(int));
    }
    int data2[] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 5, 6, 7, 8, 9};

    iter = hl_list_begin(&list);
    for(i = 0; i < sizeof(data2) / sizeof(int); ++i)
    {
        EXPECT_EQ_INT(data2[i], hl_list_ref(int, iter));
        hl_list_next(&iter);
    }

    hl_list_free(&list);
}

CASE(test_list_swap)
{
    hl_list list1;
    hl_list list2;
    hl_list_node* iter;
    int i;

    hl_list_new(&list1);
    hl_list_new(&list2);

    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list1, &i, sizeof(int));
    }
    EXPECT_EQ_INT(10, hl_list_len(&list1));
    EXPECT_EQ_INT(0, hl_list_len(&list2));

    hl_list_swap(&list1, &list2);
    EXPECT_EQ_INT(0, hl_list_len(&list1));
    EXPECT_EQ_INT(10, hl_list_len(&list2));

    iter = hl_list_begin(&list2);
    i = 0;
    while(iter != hl_list_end(&list2))
    {
        REQUIRE_EQ_INT(i, hl_list_ref(int, iter));
        hl_list_next(&iter);
        ++i;
    }

    hl_list_free(&list1);
    hl_list_free(&list2);
}

CASE(test_list_clear_and_clone)
{
    hl_list list;
    hl_list list2;
    int i;

    hl_list_new(&list);
    hl_list_new(&list2);
    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &i, sizeof(int));
    }

    EXPECT_EQ_INT(10, hl_list_len(&list));
    hl_list_clear(&list);

    EXPECT_EQ_INT(0, hl_list_len(&list));
    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &i, sizeof(int));
    }
    EXPECT_EQ_INT(10, hl_list_len(&list));

    hl_list_clone(&list2, &list, sizeof(int));
    EXPECT_EQ_INT(10, hl_list_len(&list2));
    hl_list_node* iter = hl_list_begin(&list2);
    i = 0;
    while(iter != hl_list_end(&list2))
    {
        EXPECT_EQ_INT(i, hl_list_ref(int, iter));
        hl_list_next(&iter);
        ++i;
    }

    hl_list_free(&list);
    hl_list_free(&list2);
}

static int s_find_int;
static BOOL find_if_int(const void* item)
{
    int i = *(const int*)item;
    return i == s_find_int;
}

CASE(test_list_find)
{
    hl_list list;
    int i;
    hl_list_node* iter;
    hl_list_new(&list);

    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &i, sizeof(int));
    }

    for(i = 0; i < 10; ++i)
    {
        iter = hl_list_find(hl_list_begin(&list), hl_list_end(&list), &i, hl_equals_int);
        EXPECT_EQ_INT(i, hl_list_ref(int, iter));
        s_find_int = i;
        iter = hl_list_find_if(hl_list_begin(&list), hl_list_end(&list), find_if_int);
        EXPECT_EQ_INT(i, hl_list_ref(int, iter));
    }

    hl_list_free(&list);
}

CASE(test_list_erase)
{
    hl_list list;
    int i;
    const int count = 100;
    hl_list_node* iter;

    hl_list_new(&list);
    for(i = 0; i < count; ++i)
    {
        hl_list_append(&list, &i, sizeof(int));
    }
    EXPECT_EQ_INT(count, hl_list_len(&list));


    for(i = 0; i < count; ++i)
    {
        iter = hl_list_find(hl_list_begin(&list), hl_list_end(&list), &i, hl_equals_int);
        if(iter != hl_list_end(&list))
        {
            EXPECT_EQ_INT(i, hl_list_ref(int, iter));
            hl_list_erase(&list, iter);
            EXPECT_EQ_INT(count-i-1, hl_list_len(&list));
            EXPECT(hl_list_end(&list) == hl_list_find(hl_list_begin(&list), hl_list_end(&list), &i, hl_equals_int));
        }
    }
    hl_list_free(&list);
}

UNIT(test_list, test_list_get_and_append, test_list_prepend, test_list_insert, test_list_swap,
     test_list_clear_and_clone, test_list_find, test_list_erase)
