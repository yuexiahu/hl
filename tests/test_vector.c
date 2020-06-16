#include "hl_vector.h"
#include "simpletest.h"

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

UNIT(test_vector, test_vector_get_and_append, test_vector_prepend, test_vector_array, test_verctor_insert,
     test_vector_swap, test_vector_reserve_and_fit)
