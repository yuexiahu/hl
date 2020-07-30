#include "hl_map.h"

// make x to left node
HL_INLINE void hl_map_left_rotate(hl_map* map, hl_map_node* x)
{
    hl_map_node* y = x->right;
    x->right = y->left;
    if(y->left)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL)
    {
        map->root = y;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// make y to right node
HL_INLINE void hl_map_right_rotate(hl_map* map, hl_map_node* y)
{
    hl_map_node* x = y->left;
    y->left = x->right;
    if(x->right)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == NULL)
    {
        map->root = x;
    }
    else if(y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

HL_INLINE BOOL hl_map_is_red(hl_map_node* node)
{
    return node && (node->color == HL_MAP_RED);
}

HL_INLINE BOOL hl_map_is_black(hl_map_node* node)
{
    return !hl_map_is_red(node);
}

HL_INLINE int hl_map_color(hl_map_node* node)
{
    return node ? node->color : HL_MAP_BLACK;
}

HL_INLINE void hl_map_insert_fixup(hl_map* map, hl_map_node* node)
{
    hl_map_node* parent;
    hl_map_node* gparent;
    while((parent = node->parent) && hl_map_is_red(parent))
    {
        gparent = parent->parent;
        if(parent == gparent->left) // node的父节点是node祖父节点的左子
        {
            hl_map_node* uncle = gparent->right; //叔叔节点
            if(hl_map_is_red(uncle))             //叔叔为红色
            {
                parent->color = HL_MAP_BLACK;
                uncle->color = HL_MAP_BLACK;
                gparent->color = HL_MAP_RED;
                node = gparent;
                continue;
            }

            if(node == parent->right) //叔叔是黑色，且当前节点是右子
            {
                hl_map_node* tmp;
                hl_map_left_rotate(map, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            //叔叔是黑色，且当前节点是左子
            parent->color = HL_MAP_BLACK;
            gparent->color = HL_MAP_RED;
            hl_map_right_rotate(map, gparent);
        }
        else // node的父节点是node祖父节点的右子
        {
            hl_map_node* uncle = gparent->left; //叔叔节点
            if(hl_map_is_red(uncle))            //叔叔为红色
            {
                parent->color = HL_MAP_BLACK;
                uncle->color = HL_MAP_BLACK;
                gparent->color = HL_MAP_RED;
                node = gparent;
                continue;
            }

            if(node == parent->left) //叔叔是黑色，且当前节点是左子
            {
                hl_map_node* tmp;
                hl_map_right_rotate(map, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            //叔叔是黑色，且当前节点是右子
            parent->color = HL_MAP_BLACK;
            gparent->color = HL_MAP_RED;
            hl_map_left_rotate(map, gparent);
        }
    }
    map->root->color = HL_MAP_BLACK;
}

HL_INLINE void hl_map_erase_fixup(hl_map* map, hl_map_node* node, hl_map_node* parent)
{
    hl_map_node* other;
    while(hl_map_is_black(node) && node != map->root)
    {
        if(parent->left == node)
        {
            other = parent->right;
            if(hl_map_is_red(other))
            {
                other->color = HL_MAP_BLACK;
                parent->color = HL_MAP_RED;
                hl_map_left_rotate(map, parent);
                other = parent->right;
            }
            if(hl_map_is_black(other->left) && hl_map_is_black(other->right))
            {
                other->color = HL_MAP_RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if(hl_map_is_black(other->right))
                {
                    other->left->color = HL_MAP_BLACK;
                    other->color = HL_MAP_RED;
                    hl_map_right_rotate(map, other);
                    other = parent->right;
                }
                other->color = hl_map_color(parent);
                parent->color = HL_MAP_BLACK;
                other->right->color = HL_MAP_BLACK;
                hl_map_left_rotate(map, parent);
                node = map->root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if(hl_map_is_red(other))
            {
                other->color = HL_MAP_BLACK;
                parent->color = HL_MAP_RED;
                hl_map_right_rotate(map, parent);
                other = parent->left;
            }
            if(hl_map_is_black(other->left) && hl_map_is_black(other->right))
            {
                other->color = HL_MAP_RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if(hl_map_is_black(other->left))
                {
                    other->right = HL_MAP_BLACK;
                    other->color = HL_MAP_RED;
                    hl_map_left_rotate(map, other);
                    other = parent->left;
                }

                other->color = hl_map_color(parent);
                parent->color = HL_MAP_BLACK;
                other->left = HL_MAP_BLACK;
                hl_map_right_rotate(map, parent);
                node = map->root;
                break;;
            }
        }
    }
    if(node)
    {
        node->color = HL_MAP_BLACK;
    }
}

HL_INLINE void hl_map_replace_node(hl_map* map, hl_map_node* old, hl_map_node* new)
{
    if(old->parent == NULL) //被替换的是根节点
    {
        map->root = new;
    }
    else if(new == new->parent->left) //新节点是左子树
    {
        old->parent->left = new;
    }
    else //新节点是右子树
    {
        old->parent->right = new;
    }
    new->parent = old->parent;
}

void hl_map_new(hl_map* map, BOOL (*less)(const void* item1, const void* item2))
{
    hl_assert(map != NULL && less != NULL);

    map->len = 0;
    map->root = NULL;
    map->less = less;
}

void hl_map_free(hl_map* map)
{
    hl_map_clear(map);
    map->less = NULL;
}

void hl_map_free_node(hl_map_node* node)
{
    if(node != NULL)
    {
        hl_map_free_node(node->left);
        hl_map_free_node(node->right);
        hl_free(node);
    }
}

void hl_map_clear(hl_map* map)
{
    hl_assert(map != NULL);
    hl_map_free_node(map->root);
    map->root = NULL;
    map->len = 0;
}

hl_map_node* hl_map_clone_node(hl_map_node* node, size_t item_size)
{
    if(node == NULL)
    {
        return NULL;
    }

    hl_map_node* new_node = hl_malloc(sizeof(hl_map_node) + item_size);
    new_node->parent = NULL;
    new_node->left = hl_map_clone_node(node->left, item_size);
    new_node->right = hl_map_clone_node(node->right, item_size);
    new_node->color = node->color;
    memcpy(new_node->data, node->data, item_size);
    if(new_node->left)
    {
        new_node->left->parent = new_node;
    }
    else
    {
        new_node->left = NULL;
    }

    if(new_node->right)
    {
        new_node->right->parent = new_node;
    }
    else
    {
        new_node->right = NULL;
    }
    return new_node;
}

void hl_map_clone(hl_map* map, const hl_map* from, size_t item_size)
{
    hl_assert(map != NULL && from != NULL);
    hl_map_clear(map);
    map->root = hl_map_clone_node(from->root, item_size);
    map->len = from->len;
    map->less = from->less;
}

hl_map_node* hl_map_insert(hl_map* map, const void* item, size_t item_size)
{
    hl_assert(map != NULL);

    hl_map_node* x = map->root;
    hl_map_node* y = NULL;
    hl_map_node* node = hl_malloc(sizeof(hl_map_node) + item_size);
    node->left = NULL;
    node->right = NULL;
    node->color = HL_MAP_RED;
    memcpy(node->data, item, item_size);

    while(x != NULL)
    {
        y = x;
        if(map->less(item, x->data))
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    node->parent = y;

    if(y == NULL)
    {
        map->root = node;
    }
    else if(map->less(item, y->data))
    {
        y->left = node;
    }
    else
    {
        y->right = node;
    }
    hl_map_insert_fixup(map, node);
    ++map->len;
    return node;
}

void hl_map_swap(hl_map* map1, hl_map* map2)
{
    hl_map tmp;
    memcpy(&tmp, map1, sizeof(hl_map));
    memcpy(map1, map2, sizeof(hl_map));
    memcpy(map2, &tmp, sizeof(hl_map));
}

hl_map_node* hl_map_erase(hl_map* map, hl_map_node* iter)
{
    hl_map_node* replace;
    hl_map_node* child;
    hl_map_node* parent;
    int color;

    hl_assert(map != NULL);
    if(iter == hl_map_end(map))
    {
        return iter;
    }

    //左右节点均非空
    if(iter->left != NULL && iter->right != NULL)
    {
        //用后继节点来取代被删节点
        replace = iter->right;
        while(replace->left != NULL)
        {
            replace = replace->left;
        }

        //被删节点非根节点
        if(iter->parent != NULL)
        {
            if(iter->parent->left == iter)
            {
                iter->parent->left = replace;
            }
            else
            {
                iter->parent->right = replace;
            }
        }
        else
        {
            map->root = replace;
        }

        // child是取代节点的右子，需要调整
        //因为取代节点是被删节点的后继肯定不存在左子
        child = replace->right;
        parent = replace->parent;
        color = replace->color;

        //被删节点是后继的父节点
        if(parent == iter)
        {
            parent = replace;
        }
        else
        {
            if(child != NULL)
            {
                child->parent = parent;
            }
            parent->left = child;
            replace->right = iter->right;
            iter->right->parent = replace;
        }

        replace->parent = iter->parent;
        replace->color = iter->color;
        replace->left = iter->left;
        iter->left->parent = replace;
    }
    else
    {
        if(iter->left != NULL)
        {
            child = iter->left;
        }
        else
        {
            child = iter->right;
        }
        replace = child;
        parent = iter->parent;
        color = iter->color;

        if(child != NULL)
        {
            child->parent = parent;
        }
        if(parent != NULL)
        {
            if(parent->left == iter)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
        }
        else
        {
            map->root = child;
        }
    }

    if(color == HL_MAP_BLACK)
    {
        hl_map_erase_fixup(map, child, parent);
    }
    hl_free(iter);
    --map->len;
    return replace;
}

hl_map_node* hl_map_find(const hl_map* map, const void* item)
{
    hl_assert(map != NULL);

    hl_map_node* x = map->root;
    hl_map_node* y = map->root;
    while(x)
    {
        if(!map->less(x->data, item))
        {
            y = x;
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    if(y == NULL || map->less(item, y->data))
    {
        return NULL;
    }
    return y;
}

void hl_map_prev(const hl_map* map, hl_map_node** iter)
{
    hl_map_node* node = *iter;
    hl_assert(map != NULL && iter != NULL);

    if(node == NULL)
    {
        *iter = hl_map_max(map);
        return;
    }

    if(node->left != NULL)
    {
        node = node->left;
        while(node->right != NULL)
        {
            node = node->right;
        }
        *iter = node;
        return;
    }

    while(node->parent != NULL)
    {
        if(node == node->parent->right)
        {
            *iter = node->parent;
            return;
        }
        node = node->parent;
    }
}

void hl_map_next(const hl_map* map, hl_map_node** iter)
{
    hl_map_node* node = *iter;
    hl_assert(map != NULL && iter != NULL);
    hl_return_check(node != NULL);

    if(node->right != NULL)
    {
        node = node->right;
        while(node->left != NULL)
        {
            node = node->left;
        }
        *iter = node;
        return;
    }

    while(node->parent != NULL)
    {
        if(node == node->parent->left)
        {
            *iter = node->parent;
            return;
        }
        node = node->parent;
    }

    *iter = NULL;
}

hl_map_node* hl_map_min(const hl_map* map)
{
    hl_map_node* node;
    hl_assert(map != NULL);

    node = map->root;
    if(node == NULL)
    {
        return NULL;
    }

    while(node->left)
    {
        node = node->left;
    }
    return node;
}

hl_map_node* hl_map_max(const hl_map* map)
{
    hl_map_node* node;
    hl_assert(map != NULL);

    node = map->root;
    if(node == NULL)
    {
        return NULL;
    }

    while(node->right)
    {
        node = node->right;
    }
    return node;
}
