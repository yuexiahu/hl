#include "hl_map.h"
#include "hl_utils.h"
#include "simpletest.h"

struct pair_int_int
{
    int key;
    int value;
};

struct pair_str_int
{
    char key[20];
    int value;
};

CASE(test_map_insert_and_find)
{
    hl_map map;
    hl_map_node* iter;
    int i;
    struct pair_int_int int_int;
    struct pair_str_int str_int;
    int values[100];

    hl_map_new(&map, hl_less_int);
    EXPECT_EQ_INT(0, hl_map_len(&map));

    for(i = 0; i < 100; ++i)
    {
        int_int.key = i;
        int_int.value = i+1;
        hl_map_insert(&map, &int_int, sizeof(struct pair_int_int));
        EXPECT_EQ_INT(i + 1, hl_map_len(&map));
    }

    for(i = 0; i < 100; ++i)
    {
        int_int.key = i;
        iter = hl_map_find(&map, &int_int);
        EXPECT(iter != hl_map_end(&map));
        EXPECT_EQ_INT(i + 1, hl_map_ref(struct pair_int_int, iter).value);
    }

    memset(values, 0, sizeof(values));
    for(iter = hl_map_begin(&map); iter != hl_map_end(&map); hl_map_next(&map, &iter))
    {
        struct pair_int_int* ppair = hl_map_at(iter);
        values[ppair->key] = ppair->value;
    }
    for(i = 0; i < 100; ++i)
    {
        EXPECT_EQ_INT(i+1, values[i]);
    }

    hl_map_free(&map);

    hl_map_new(&map, hl_less_cstr);
    EXPECT_EQ_INT(0, hl_map_len(&map));

    for(i = 0; i < 100; ++i)
    {
        sprintf(str_int.key, "%d", i);
        str_int.value = i+1;
        hl_map_insert(&map, &str_int, sizeof(struct pair_str_int));
        EXPECT_EQ_INT(i + 1, hl_map_len(&map));
    }

    for(i = 0; i < 100; ++i)
    {
        sprintf(str_int.key, "%d", i);
        iter = hl_map_find(&map, &str_int);
        EXPECT(iter != hl_map_end(&map));
        EXPECT_EQ_INT(i + 1, hl_map_ref(struct pair_str_int, iter).value);
    }

    memset(values, 0, sizeof(values));
    for(iter = hl_map_begin(&map); iter != hl_map_end(&map); hl_map_next(&map, &iter))
    {
        struct pair_str_int* ppair = hl_map_at(iter);
        values[strtol(ppair->key, 0, 10)] = ppair->value;
    }
    for(i = 0; i < 100; ++i)
    {
        EXPECT_EQ_INT(i+1, values[i]);
    }

    hl_map_free(&map);
}

CASE(test_map_swap)
{
    hl_map map1;
    hl_map map2;
    hl_map_node* iter;
    struct pair_int_int int_int;
    int i;

    hl_map_new(&map1, hl_less_int);
    hl_map_new(&map2, hl_less_int);

    for(i = 0; i < 10; ++i)
    {
        int_int.key = i;
        int_int.value = i+1;
        hl_map_insert(&map1, &int_int, sizeof(struct pair_int_int));
    }
    EXPECT_EQ_INT(10, hl_map_len(&map1));
    EXPECT_EQ_INT(0, hl_map_len(&map2));

    hl_map_swap(&map1, &map2);
    EXPECT_EQ_INT(0, hl_map_len(&map1));
    EXPECT_EQ_INT(10, hl_map_len(&map2));

    for(i = 0; i < 10; ++i)
    {
        int_int.key = i;
        iter = hl_map_find(&map2, &int_int);
        EXPECT(iter != hl_map_end(&map2));
        EXPECT_EQ_INT(i + 1, hl_map_ref(struct pair_int_int, iter).value);
    }

    hl_map_free(&map1);
    hl_map_free(&map2);
}

CASE(test_map_clear_and_clone)
{
    hl_map map;
    hl_map map2;
    struct pair_int_int int_int;
    hl_map_node* iter;
    int i;

    hl_map_new(&map, hl_less_int);
    hl_map_new(&map2, hl_less_int);
    for(i = 0; i < 10; ++i)
    {
        int_int.key = i;
        int_int.value = i+1;
        hl_map_insert(&map, &int_int, sizeof(struct pair_int_int));
    }

    EXPECT_EQ_INT(10, hl_map_len(&map));
    hl_map_clear(&map);

    EXPECT_EQ_INT(0, hl_map_len(&map));
    for(i = 0; i < 10; ++i)
    {
        int_int.key = i;
        int_int.value = i+1;
        hl_map_insert(&map, &int_int, sizeof(struct pair_int_int));
    }
    EXPECT_EQ_INT(10, hl_map_len(&map));

    hl_map_clone(&map2, &map, sizeof(struct pair_int_int));
    EXPECT_EQ_INT(10, hl_map_len(&map));
    EXPECT_EQ_INT(10, hl_map_len(&map2));

    for(i = 0; i < 10; ++i)
    {
        int_int.key = i;
        iter = hl_map_find(&map2, &int_int);
        EXPECT(iter != hl_map_end(&map2));
        EXPECT_EQ_INT(i + 1, hl_map_ref(struct pair_int_int, iter).value);
    }

    hl_map_free(&map);
    hl_map_free(&map2);
}

CASE(test_map_erase)
{
    hl_map map;
    int i;
    const int count = 100;
    hl_map_node* iter;

    hl_map_new(&map, hl_less_int);
    for(i = 0; i < count; ++i)
    {
        hl_map_insert(&map, &i, sizeof(int));
    }
    EXPECT_EQ_INT(count, hl_map_len(&map));


    for(i = 0; i < count; ++i)
    {
        iter = hl_map_find(&map, &i);
        if(iter != hl_map_end(&map))
        {
            EXPECT_EQ_INT(i, hl_map_ref(int, iter));
            hl_map_erase(&map, iter);
            EXPECT_EQ_INT(count-i-1, hl_map_len(&map));
            EXPECT(hl_map_end(&map) == hl_map_find(&map, &i));
        }
    }
    hl_map_free(&map);
}

CASE(test_map_iter)
{
    hl_map map;
    int i;
    const int count = 100;
    hl_map_node* iter;
    hl_map_node* begin_iter;

    hl_map_new(&map, hl_less_int);
    for(i = 0; i < count; ++i)
    {
        hl_map_insert(&map, &i, sizeof(int));
    }
    EXPECT_EQ_INT(count, hl_map_len(&map));

    i = 0;
    for(iter = hl_map_begin(&map); iter != hl_map_end(&map); hl_map_next(&map, &iter))
    {
        EXPECT_EQ_INT(i, hl_map_ref(int, iter));
        ++i;
    }

    iter = hl_map_max(&map);
    begin_iter = hl_map_begin(&map);
    i = count-1;
    do
    {
        EXPECT_EQ_INT(i, hl_map_ref(int, iter));
        --i;
        hl_map_prev(&map, &iter);
    } while(begin_iter != iter);

    hl_map_free(&map);
}

UNIT(test_map, test_map_insert_and_find, test_map_swap, test_map_clear_and_clone, test_map_erase, test_map_iter)
