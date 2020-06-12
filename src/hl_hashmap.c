#include "hl_hashmap.h"

#define _hl_num_primes 28
static const size_t _hl_prime_list[_hl_num_primes] =
{
    53ul,         97ul,         193ul,       389ul,       769ul,
    1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
    49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
    1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
    50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul, 
    1610612741ul, 3221225473ul, 4294967291ul
};

HL_INLINE size_t _hl_lower_bound(const size_t* a, int n, size_t x)
{
    int l = 0;
    int h = n;
    while(l < h)
    {
        int mid = l + (h - l) / 2;
        if(x <= a[mid])
        {
            h = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return l;
}

HL_INLINE size_t _hl_next_prime(size_t n)
{
    const size_t pos = _hl_lower_bound(_hl_prime_list, _hl_num_primes, n);
    return _hl_prime_list[pos < _hl_num_primes ? pos : (_hl_num_primes-1)];
}

HL_INLINE size_t _hl_hashmap_bucket_num(const hl_hashmap* hashmap, const void* item, size_t bucket_size)
{
    return hashmap->hash_key(item) % bucket_size;
}

void hl_hashmap_new(hl_hashmap* hashmap,
                    size_t (*hash_key)(const void* item),
                    BOOL (*equals)(const void* item1, const void* item2))
{
    hl_assert(hashmap != NULL && hash_key != NULL && equals != NULL);

    size_t bucket_size;
    hashmap->hash_key = hash_key;
    hashmap->equals = equals;
    hashmap->len = 0;
    hashmap->bucket_size = _hl_next_prime(0);
    hashmap->buckets = hl_calloc(hashmap->bucket_size, sizeof(hl_hashmap_node*));
}

void hl_hashmap_free(hl_hashmap* hashmap)
{
    hl_assert(hashmap != NULL);

    hashmap->hash_key = 0;
    hashmap->equals = 0;

    hl_hashmap_node* node;
    for(size_t n = 0; n < hashmap->bucket_size; ++n)
    {
        node = hashmap->buckets[n];
        while(node != NULL)
        {
            hl_hashmap_node* next = node->next;
            hl_free(node);
            node = next;
        }
    }
    free(hashmap->buckets);
    hashmap->buckets = NULL;
    hashmap->bucket_size = 0;
    hashmap->len = 0;
}

void hl_hashmap_clear(hl_hashmap* hashmap)
{
    hl_assert(hashmap != NULL);

    hl_hashmap_node* node;
    for(size_t n = 0; n < hashmap->bucket_size; ++n)
    {
        node = hashmap->buckets[n];
        while(node != NULL)
        {
            hl_hashmap_node* next = node->next;
            hl_free(node);
            node = next;
        }
    }
    memset(hashmap->buckets, 0, hashmap->bucket_size * sizeof(hl_hashmap_node*));
    hashmap->len = 0;
}

void hl_hashmap_clone(hl_hashmap* hashmap, const hl_hashmap* from, size_t item_size)
{
    hl_assert(hashmap != NULL && from != NULL);

    hl_hashmap_clear(hashmap);
}

void hl_hashmap_insert(hl_hashmap* hashmap, const void* item, size_t item_size)
{
    hl_assert(hashmap != NULL);

    hl_hashmap_resize(hashmap, hl_hashmap_len(hashmap)+1);
    hl_hashmap_insert_noresize(hashmap, item, item_size);
}

void hl_hashmap_insert_noresize(hl_hashmap* hashmap, const void* item, size_t item_size)
{
    hl_assert(hashmap != NULL);

    size_t bucket = _hl_hashmap_bucket_num(hashmap, item, hashmap->bucket_size);
    hl_hashmap_node* first = hashmap->buckets[bucket];

    for(hl_hashmap_node* cur = first; cur; cur = cur->next)
    {
        if(hashmap->equals(item, cur->data))
        {
            return;
        }
    }

    hl_hashmap_node* tmp = hl_malloc(sizeof(hl_hashmap_node));
    tmp->next = first;
    hashmap->buckets[bucket] = tmp;
    ++hashmap->len;
}

void hl_hashmap_swap(hl_hashmap* hashmap1, hl_hashmap* hashmap2)
{
    hl_assert(hashmap1 != NULL && hashmap2 != NULL);
    hl_hashmap tmp;
    memcpy(&tmp, hashmap1, sizeof(hl_hashmap));
    memcpy(hashmap1, hashmap2, sizeof(hl_hashmap));
    memcpy(hashmap1, &tmp, sizeof(hl_hashmap));
}

hl_hashmap_node* hl_hashmap_erase(hl_hashmap* hashmap, hl_hashmap_node* iter)
{
    hl_assert(hashmap != NULL);

    size_t bucket = _hl_hashmap_bucket_num(hashmap, hl_hashmap_at(iter), hashmap->bucket_size);
    hl_hashmap_node* prev_iter = hashmap->buckets[bucket];
    hl_hashmap_node* next_iter = iter;
    hl_hashmap_next(hashmap, &next_iter);

    if(prev_iter == iter)
    {
        hashmap->buckets[bucket] = iter->next;
        hl_free(iter);
        --hashmap->len;
    }
    else
    {
        while(prev_iter)
        {
            if(prev_iter->next == iter)
            {
                prev_iter->next = iter->next;
                hl_free(iter);
                --hashmap->len;
                break;
            }
            prev_iter = prev_iter->next;
        }
    }
    return next_iter;
}

hl_hashmap_node* hl_hashmap_find(const hl_hashmap* hashmap, const void* item)
{
    hl_assert(hashmap != NULL);

    size_t bucket = _hl_hashmap_bucket_num(hashmap, item, hashmap->bucket_size);
    hl_hashmap_node* iter = hashmap->buckets[bucket];
    while(iter != NULL)
    {
        if(hashmap->equals(iter->data, item))
        {
            break;
        }
        iter = iter->next;
    }
    return iter;
}

hl_hashmap_node* hl_hashmap_begin(const hl_hashmap* hashmap)
{
    hl_assert(hashmap != NULL);
    hl_hashmap_node* iter = NULL;
    for(size_t n = 0; n < hashmap->bucket_size; ++n)
    {
        if(hashmap->buckets[n])
        {
            iter = hashmap->buckets[n];
            break;
        }
    }
    return iter;
}

hl_hashmap_node* hl_hashmap_end(const hl_hashmap* hashmap)
{
    hl_assert(hashmap != NULL);
    return NULL;
}

void hl_hashmap_next(const hl_hashmap* hashmap, hl_hashmap_node** iter)
{
    hl_assert(hashmap != NULL && iter != NULL);

    hl_hashmap_node* old = *iter;
    *iter = old->next;

    if(*iter)
    {
        size_t bucket = _hl_hashmap_bucket_num(hashmap, old->data, hashmap->bucket_size);
        while(!*iter && ++bucket < hashmap->bucket_size)
        {
            *iter = hashmap->buckets[bucket];
        }
    }
}

void hl_hashmap_resize(hl_hashmap* hashmap, size_t len_hint)
{
    hl_assert(hashmap != NULL);

    size_t old_bucket_size = hashmap->bucket_size;
    if(len_hint > old_bucket_size)
    {
        size_t new_bucket_size = _hl_next_prime(len_hint);
        if(new_bucket_size > old_bucket_size)
        {
            hl_hashmap_node** new_buckets = hl_calloc(new_bucket_size, sizeof(hl_hashmap_node*));
            for(size_t bucket = 0; bucket < old_bucket_size; ++bucket)
            {
                hl_hashmap_node* first = hashmap->buckets[bucket];
                while(first)
                {
                    size_t new_bucket = _hl_hashmap_bucket_num(hashmap, first->data, new_bucket_size);
                    hashmap->buckets[bucket] = first->next;
                    first->next = new_buckets[new_bucket];
                    new_buckets[new_bucket] = first;
                    first = hashmap->buckets[bucket];
                }
            }
            hl_free(hashmap->buckets);
            hashmap->buckets = new_buckets;
        }
    }
}