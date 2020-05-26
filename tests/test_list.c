#include "hl_list.h"
#include "simpletest.h"

CASE(test_list_get_and_append)
{
    hl_list list;
    hl_list_node* iter;
    int i;
    hl_list_new(&list, sizeof(int));
    EXPECT_EQ_INT(0, hl_list_len(&list));

    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &i);
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

    hl_list_free(&list);

    hl_list_new(&list, sizeof(char));
    EXPECT_EQ_INT(0, hl_list_len(&list));

    char ch = 0;
    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &ch);
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

    hl_list_free(&list);

    double double_num = 0;
    hl_list_new(&list, sizeof(double));
    EXPECT_EQ_INT(0, hl_list_len(&list));

    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &double_num);
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

    hl_list_free(&list);
}

CASE(test_list_prepend)
{
    hl_list list;
    hl_list_node* iter;
    int i;
    hl_list_new(&list, sizeof(int));
    EXPECT_EQ_INT(0, hl_list_len(&list));

    for(i = 0; i < 10; ++i)
    {
        hl_list_prepend(&list, &i);
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

    hl_list_new(&list, sizeof(char));
    EXPECT_EQ_INT(0, hl_list_len(&list));

    char ch = 0;
    for(i = 0; i < 10; ++i)
    {
        hl_list_prepend(&list, &ch);
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
    hl_list_new(&list, sizeof(double));
    EXPECT_EQ_INT(0, hl_list_len(&list));

    for(i = 0; i < 10; ++i)
    {
        hl_list_prepend(&list, &double_num);
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

CASE(test_verctor_insert)
{
    hl_list list;
    int i;

    hl_list_new(&list, sizeof(int));
    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &i);
    }

    hl_list_node* iter = hl_list_begin(&list);
    for(int i = 0; i < 5; ++i)
    {
        hl_list_next(&iter);
    }

    for(int i = 0; i < 10; ++i)
    {
        hl_list_insert(&list, iter, &i);
    }
    int data2[] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 5, 6, 7, 8, 9};

    iter = hl_list_begin(&list);
    for(int i = 0; i < sizeof(data2) / sizeof(int); ++i)
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

    hl_list_new(&list1, sizeof(int));
    hl_list_new(&list2, sizeof(int));

    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list1, &i);
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

CASE(test_list_clear_and_set)
{
    hl_list list;
    hl_list list2;
    int i;

    hl_list_new(&list, sizeof(int));
    hl_list_new(&list2, sizeof(int));
    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &i);
    }

    EXPECT_EQ_INT(10, hl_list_len(&list));
    hl_list_clear(&list);

    EXPECT_EQ_INT(0, hl_list_len(&list));
    for(i = 0; i < 10; ++i)
    {
        hl_list_append(&list, &i);
    }
    EXPECT_EQ_INT(10, hl_list_len(&list));

    hl_list_set(&list2, &list);
    EXPECT_EQ_INT(10, hl_list_len(&list));
    hl_list_node* iter = hl_list_begin(&list2);
    i = 0;
    while(iter != hl_list_end(&list2))
    {
        EXPECT_EQ_INT(i, hl_list_ref(int, iter));
        hl_list_next(&iter);
        ++i;
    }

    hl_list_free(&list);
}

UNIT(test_list, test_list_get_and_append, test_list_prepend, test_verctor_insert, test_list_swap,
     test_list_clear_and_set)
