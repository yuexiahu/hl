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
        EXPECT_EQ_INT(i, hl_vector_get(int, &vector, i));
    }

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
        EXPECT_EQ_INT(i, hl_vector_get(char, &vector, i));
    }

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
        EXPECT_EQ_DOUBLE(i, hl_vector_get(double, &vector, i));
    }

    hl_vector_free(&vector);
}

CASE(test_vector_prepend)
{
}

CASE(test_vector_swap)
{
}

CASE(test_vector_reserve_and_fit)
{
}

UNIT(test_vector, test_vector_get_and_append, test_vector_prepend, test_vector_swap, test_vector_reserve_and_fit)
