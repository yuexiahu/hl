#include "hl_vector.h"
#include "simpletest.h"
#include "hl_utils.h"

CASE(test_vector_get_and_append)
{
    hl_vector vector;
    hl_vector_new(&vector, 0, sizeof(int));
    EXPECT_EQ_INT(0, hl_vector_len(&vector));

    for(int i = 0; i < 10; ++i)
    {
        hl_vector_append(&vector, &i);
        EXPECT_EQ_INT(i + 1, hl_vector_len(&vector));
    }
    for(int i = 0; i < 10; ++i)
    {
        EXPECT_EQ_INT(i, hl_vector_ref(int, &vector, i));
    }
    EXPECT_EQ_INT(10, hl_vector_len(&vector));
    EXPECT_EQ_INT(0, *(int *)hl_vector_first(&vector));
    EXPECT_EQ_INT(9, *(int *)hl_vector_last(&vector));

    hl_vector_free(&vector);

    hl_vector_new(&vector, 0, sizeof(char));
    EXPECT_EQ_INT(0, hl_vector_len(&vector));

    char ch = 0;
    for(int i = 0; i < 10; ++i)
    {
        hl_vector_append(&vector, &ch);
        EXPECT_EQ_INT(i + 1, hl_vector_len(&vector));
        ++ch;
    }
    for(int i = 0; i < 10; ++i)
    {
        EXPECT_EQ_INT(i, hl_vector_ref(char, &vector, i));
    }

    EXPECT_EQ_INT(10, hl_vector_len(&vector));
    EXPECT_EQ_INT(0, *(char *)hl_vector_first(&vector));
    EXPECT_EQ_INT(9, *(char *)hl_vector_last(&vector));

    hl_vector_free(&vector);

    double double_num = 0;
    hl_vector_new(&vector, 0, sizeof(double));
    EXPECT_EQ_INT(0, hl_vector_len(&vector));

    for(int i = 0; i < 10; ++i)
    {
        hl_vector_append(&vector, &double_num);
        EXPECT_EQ_INT(i + 1, hl_vector_len(&vector));
        ++double_num;
    }
    for(int i = 0; i < 10; ++i)
    {
        EXPECT_EQ_DOUBLE(i, hl_vector_ref(double, &vector, i));
    }

    EXPECT_EQ_INT(10, hl_vector_len(&vector));
    EXPECT_EQ_DOUBLE(0, *(double *)hl_vector_first(&vector));
    EXPECT_EQ_DOUBLE(9, *(double *)hl_vector_last(&vector));

    hl_vector_free(&vector);
}

CASE(test_vector_prepend)
{
    hl_vector vector;
    hl_vector_new(&vector, 0, sizeof(int));
    EXPECT_EQ_INT(0, hl_vector_len(&vector));

    for(int i = 0; i < 10; ++i)
    {
        hl_vector_prepend(&vector, &i);
        EXPECT_EQ_INT(i + 1, hl_vector_len(&vector));
    }

    for(int i = 0; i < 10; ++i)
    {
        EXPECT_EQ_INT(10 - 1 - i, hl_vector_ref(int, &vector, i));
    }

    hl_vector_free(&vector);

    hl_vector_new(&vector, 0, sizeof(char));
    EXPECT_EQ_INT(0, hl_vector_len(&vector));

    char ch = 0;
    for(int i = 0; i < 10; ++i)
    {
        hl_vector_prepend(&vector, &ch);
        EXPECT_EQ_INT(i + 1, hl_vector_len(&vector));
        ++ch;
    }
    for(int i = 0; i < 10; ++i)
    {
        EXPECT_EQ_INT(10 - 1 - i, hl_vector_ref(char, &vector, i));
    }

    hl_vector_free(&vector);

    double double_num = 0;
    hl_vector_new(&vector, 0, sizeof(double));
    EXPECT_EQ_INT(0, hl_vector_len(&vector));

    for(int i = 0; i < 10; ++i)
    {
        hl_vector_prepend(&vector, &double_num);
        EXPECT_EQ_INT(i + 1, hl_vector_len(&vector));
        ++double_num;
    }
    for(int i = 0; i < 10; ++i)
    {
        EXPECT_EQ_DOUBLE(10 - 1 - i, hl_vector_ref(double, &vector, i));
    }

    hl_vector_free(&vector);
}

CASE(test_vector_array)
{
    hl_vector vector;
    hl_vector_new(&vector, 10, sizeof(int));

    int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    hl_vector_clone_array(&vector, data, sizeof(data) / sizeof(int));
    EXPECT_EQ_INT(10, hl_vector_len(&vector));
    EXPECT_EQ_MEM(data, hl_vector_array(&vector), sizeof(data));
    hl_vector_free(&vector);
}

CASE(test_verctor_insert)
{
    hl_vector vector;
    hl_vector_new(&vector, 20, sizeof(int));

    int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    hl_vector_clone_array(&vector, data, sizeof(data) / sizeof(int));

    for(int i = 0; i < 10; ++i)
    {
        hl_vector_insert(&vector, 5, &i);
    }

    int data2[] = {0, 1, 2, 3, 4, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 5, 6, 7, 8, 9};
    EXPECT_EQ_INT(20, hl_vector_len(&vector));
    EXPECT_EQ_MEM(data2, hl_vector_array(&vector), sizeof(data2));

    hl_vector_free(&vector);
}

CASE(test_vector_swap)
{
    hl_vector vec1;
    hl_vector vec2;

    hl_vector_new(&vec1, 10, sizeof(int));
    hl_vector_new(&vec2, 10, sizeof(int));

    for(int i = 0; i < 10; ++i)
    {
        hl_vector_append(&vec1, &i);
    }
    EXPECT_EQ_INT(10, hl_vector_len(&vec1));
    EXPECT_EQ_INT(0, hl_vector_len(&vec2));

    hl_vector_swap(&vec1, &vec2);
    EXPECT_EQ_INT(0, hl_vector_len(&vec1));
    EXPECT_EQ_INT(10, hl_vector_len(&vec2));

    for(int i = 0; i < 10; ++i)
    {
        EXPECT_EQ_INT(i, hl_vector_ref(int, &vec2, i));
    }

    hl_vector_free(&vec1);
    hl_vector_free(&vec2);
}

CASE(test_vector_reserve_and_fit)
{
    hl_vector vector;

    hl_vector_new(&vector, 0, sizeof(int));
    EXPECT_EQ_INT(0, hl_vector_cap(&vector));
    hl_vector_reserve(&vector, 10);
    EXPECT_EQ_INT(16, hl_vector_cap(&vector));
    hl_vector_shrink_to_fit(&vector);
    EXPECT_EQ_INT(0, hl_vector_cap(&vector));
    hl_vector_reserve(&vector, 100);
    for(int i = 0; i < 10; ++i)
    {
        hl_vector_append(&vector, &i);
    }
    hl_vector_shrink_to_fit(&vector);
    EXPECT_EQ_INT(10, hl_vector_cap(&vector));
    hl_vector_free(&vector);

    hl_vector_new(&vector, 1, sizeof(int));
    EXPECT_EQ_INT(1, hl_vector_cap(&vector));
    hl_vector_free(&vector);

    hl_vector_new(&vector, 10, sizeof(int));
    EXPECT_EQ_INT(10, hl_vector_cap(&vector));
    hl_vector_free(&vector);
}


static int s_find_int;
static BOOL find_if_int(const void* item)
{
    int i = *(const int*)item;
    return i == s_find_int;
}

CASE(test_vector_find)
{
    hl_vector vector;
    int i;
    size_t iter;
    hl_vector_new(&vector, 0, sizeof(int));

    for(i = 0; i < 10; ++i)
    {
        hl_vector_append(&vector, &i);
    }

    for(i = 0; i < 10; ++i)
    {
        iter = hl_vector_find(&vector, 0, &i, hl_equals_int);
        EXPECT_EQ_INT(i, hl_vector_ref(int, &vector, iter));
        s_find_int = i;
        iter = hl_vector_find_if(&vector, 0, find_if_int);
        EXPECT_EQ_INT(i, hl_vector_ref(int, &vector, iter));
    }

    int not_found = 100;
    iter = hl_vector_find(&vector, 0, &not_found, hl_equals_int);
    EXPECT_EQ_INT(hl_vector_end(&vector), iter);
    s_find_int = not_found;
    iter = hl_vector_find_if(&vector, 0, find_if_int);
    EXPECT_EQ_INT(hl_vector_end(&vector), iter);

    not_found = -1;
    iter = hl_vector_find(&vector, 0, &not_found, hl_equals_int);
    EXPECT_EQ_INT(hl_vector_end(&vector), iter);
    s_find_int = not_found;
    iter = hl_vector_find_if(&vector, 0, find_if_int);
    EXPECT_EQ_INT(hl_vector_end(&vector), iter);

    hl_vector_free(&vector);
}

CASE(test_vector_lower_bound)
{
    hl_vector vector;
    hl_vector_new(&vector, 0, sizeof(int));

    // 测试空vector
    int search_val = 5;
    size_t pos = hl_vector_lower_bound(&vector, &search_val, hl_less_int);
    EXPECT_EQ_INT(0, pos);

    // 添加一些有序数据
    int data[] = {1, 3, 3, 7, 9, 12, 15, 18};
    size_t data_len = sizeof(data) / sizeof(int);
    for(size_t i = 0; i < data_len; ++i)
    {
        hl_vector_append(&vector, &data[i]);
    }

    // 测试查找存在的值
    search_val = 3;
    pos = hl_vector_lower_bound(&vector, &search_val, hl_less_int);
    EXPECT_EQ_INT(1, pos); // 第一个3的位置
    EXPECT_EQ_INT(3, hl_vector_ref(int, &vector, pos));

    search_val = 7;
    pos = hl_vector_lower_bound(&vector, &search_val, hl_less_int);
    EXPECT_EQ_INT(3, pos);
    EXPECT_EQ_INT(7, hl_vector_ref(int, &vector, pos));

    search_val = 1;
    pos = hl_vector_lower_bound(&vector, &search_val, hl_less_int);
    EXPECT_EQ_INT(0, pos);
    EXPECT_EQ_INT(1, hl_vector_ref(int, &vector, pos));

    search_val = 18;
    pos = hl_vector_lower_bound(&vector, &search_val, hl_less_int);
    EXPECT_EQ_INT(7, pos);
    EXPECT_EQ_INT(18, hl_vector_ref(int, &vector, pos));

    // 测试查找不存在的值
    search_val = 0; // 小于所有元素
    pos = hl_vector_lower_bound(&vector, &search_val, hl_less_int);
    EXPECT_EQ_INT(0, pos);

    search_val = 2; // 在1和3之间
    pos = hl_vector_lower_bound(&vector, &search_val, hl_less_int);
    EXPECT_EQ_INT(1, pos);
    EXPECT_EQ_INT(3, hl_vector_ref(int, &vector, pos));

    search_val = 5; // 在3和7之间
    pos = hl_vector_lower_bound(&vector, &search_val, hl_less_int);
    EXPECT_EQ_INT(3, pos);
    EXPECT_EQ_INT(7, hl_vector_ref(int, &vector, pos));

    search_val = 20; // 大于所有元素
    pos = hl_vector_lower_bound(&vector, &search_val, hl_less_int);
    EXPECT_EQ_INT(8, pos); // 等于vector长度

    hl_vector_free(&vector);
}

UNIT(test_vector, test_vector_get_and_append, test_vector_prepend, test_vector_array, test_verctor_insert,
     test_vector_swap, test_vector_reserve_and_fit, test_vector_find, test_vector_lower_bound)
