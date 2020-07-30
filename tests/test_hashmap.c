#include "hl_hashmap.h"
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

static size_t hash_pair_str_int(const void* item)
{
    return hl_hash_cstr(((const struct pair_str_int*)item)->key);
}

CASE(test_hashmap_insert_and_find)
{
    hl_hashmap hashmap;
    hl_hashmap_node* iter;
    int i;
    struct pair_int_int int_int;
    struct pair_str_int str_int;
    int values[100];

    hl_hashmap_new(&hashmap, hl_hash_int, hl_equals_int);
    EXPECT_EQ_INT(0, hl_hashmap_len(&hashmap));

    for(i = 0; i < 100; ++i)
    {
        int_int.key = i;
        int_int.value = i+1;
        hl_hashmap_insert(&hashmap, &int_int, sizeof(struct pair_int_int));
        EXPECT_EQ_INT(i + 1, hl_hashmap_len(&hashmap));
    }

    for(i = 0; i < 100; ++i)
    {
        int_int.key = i;
        iter = hl_hashmap_find(&hashmap, &int_int);
        EXPECT(iter != hl_hashmap_end(&hashmap));
        EXPECT_EQ_INT(i + 1, hl_hashmap_ref(struct pair_int_int, iter).value);
    }

    memset(values, 0, sizeof(values));
    for(iter = hl_hashmap_begin(&hashmap); iter != hl_hashmap_end(&hashmap); hl_hashmap_next(&hashmap, &iter))
    {
        struct pair_int_int* ppair = hl_hashmap_at(iter);
        values[ppair->key] = ppair->value;
    }
    for(i = 0; i < 100; ++i)
    {
        EXPECT_EQ_INT(i+1, values[i]);
    }

    hl_hashmap_free(&hashmap);

    hl_hashmap_new(&hashmap, hl_hash_cstr, hl_equals_cstr);
    EXPECT_EQ_INT(0, hl_hashmap_len(&hashmap));

    for(i = 0; i < 100; ++i)
    {
        sprintf(str_int.key, "%d", i);
        str_int.value = i+1;
        hl_hashmap_insert(&hashmap, &str_int, sizeof(struct pair_str_int));
        EXPECT_EQ_INT(i + 1, hl_hashmap_len(&hashmap));
    }

    for(i = 0; i < 100; ++i)
    {
        sprintf(str_int.key, "%d", i);
        iter = hl_hashmap_find(&hashmap, &str_int);
        EXPECT(iter != hl_hashmap_end(&hashmap));
        EXPECT_EQ_INT(i + 1, hl_hashmap_ref(struct pair_str_int, iter).value);
    }

    memset(values, 0, sizeof(values));
    for(iter = hl_hashmap_begin(&hashmap); iter != hl_hashmap_end(&hashmap); hl_hashmap_next(&hashmap, &iter))
    {
        struct pair_str_int* ppair = hl_hashmap_at(iter);
        values[strtol(ppair->key, 0, 10)] = ppair->value;
    }
    for(i = 0; i < 100; ++i)
    {
        EXPECT_EQ_INT(i+1, values[i]);
    }

    hl_hashmap_free(&hashmap);
}

CASE(test_hashmap_swap)
{
    hl_hashmap hashmap1;
    hl_hashmap hashmap2;
    hl_hashmap_node* iter;
    struct pair_int_int int_int;
    int i;

    hl_hashmap_new(&hashmap1, hl_hash_int, hl_equals_int);
    hl_hashmap_new(&hashmap2, hl_hash_int, hl_equals_int);

    for(i = 0; i < 10; ++i)
    {
        int_int.key = i;
        int_int.value = i+1;
        hl_hashmap_insert(&hashmap1, &int_int, sizeof(struct pair_int_int));
    }
    EXPECT_EQ_INT(10, hl_hashmap_len(&hashmap1));
    EXPECT_EQ_INT(0, hl_hashmap_len(&hashmap2));

    hl_hashmap_swap(&hashmap1, &hashmap2);
    EXPECT_EQ_INT(0, hl_hashmap_len(&hashmap1));
    EXPECT_EQ_INT(10, hl_hashmap_len(&hashmap2));

    for(i = 0; i < 10; ++i)
    {
        int_int.key = i;
        iter = hl_hashmap_find(&hashmap2, &int_int);
        EXPECT(iter != hl_hashmap_end(&hashmap2));
        EXPECT_EQ_INT(i + 1, hl_hashmap_ref(struct pair_int_int, iter).value);
    }

    hl_hashmap_free(&hashmap1);
    hl_hashmap_free(&hashmap2);
}

CASE(test_hashmap_clear_and_clone)
{
    hl_hashmap hashmap;
    hl_hashmap hashmap2;
    struct pair_int_int int_int;
    hl_hashmap_node* iter;
    int i;

    hl_hashmap_new(&hashmap, hl_hash_int, hl_equals_int);
    hl_hashmap_new(&hashmap2, hl_hash_int, hl_equals_int);
    for(i = 0; i < 10; ++i)
    {
        int_int.key = i;
        int_int.value = i+1;
        hl_hashmap_insert(&hashmap, &int_int, sizeof(struct pair_int_int));
    }

    EXPECT_EQ_INT(10, hl_hashmap_len(&hashmap));
    hl_hashmap_clear(&hashmap);

    EXPECT_EQ_INT(0, hl_hashmap_len(&hashmap));
    for(i = 0; i < 10; ++i)
    {
        int_int.key = i;
        int_int.value = i+1;
        hl_hashmap_insert(&hashmap, &int_int, sizeof(struct pair_int_int));
    }
    EXPECT_EQ_INT(10, hl_hashmap_len(&hashmap));

    hl_hashmap_clone(&hashmap2, &hashmap, sizeof(struct pair_int_int));
    EXPECT_EQ_INT(10, hl_hashmap_len(&hashmap));
    EXPECT_EQ_INT(10, hl_hashmap_len(&hashmap2));

    for(i = 0; i < 10; ++i)
    {
        int_int.key = i;
        iter = hl_hashmap_find(&hashmap2, &int_int);
        EXPECT(iter != hl_hashmap_end(&hashmap2));
        EXPECT_EQ_INT(i + 1, hl_hashmap_ref(struct pair_int_int, iter).value);
    }

    hl_hashmap_free(&hashmap);
    hl_hashmap_free(&hashmap2);
}

CASE(test_hashmap_erase)
{
    hl_hashmap hashmap;
    int i;
    const int count = 100;
    hl_hashmap_node* iter;

    hl_hashmap_new(&hashmap, hl_hash_int, hl_equals_int);
    for(i = 0; i < count; ++i)
    {
        hl_hashmap_insert(&hashmap, &i, sizeof(int));
    }
    EXPECT_EQ_INT(count, hl_hashmap_len(&hashmap));


    for(i = 0; i < count; ++i)
    {
        iter = hl_hashmap_find(&hashmap, &i);
        if(iter != hl_hashmap_end(&hashmap))
        {
            EXPECT_EQ_INT(i, hl_hashmap_ref(int, iter));
            hl_hashmap_erase(&hashmap, iter);
            EXPECT_EQ_INT(count-i-1, hl_hashmap_len(&hashmap));
            EXPECT(hl_hashmap_end(&hashmap) == hl_hashmap_find(&hashmap, &i));
        }
    }
    hl_hashmap_free(&hashmap);
}

UNIT(test_hashmap, test_hashmap_insert_and_find, test_hashmap_swap, test_hashmap_clear_and_clone, test_hashmap_erase)
