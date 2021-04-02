#define __USE_MINGW_ANSI_STDIO 1

#include "tree.h"

tree_node_t *node_create(long data)
{
    tree_node_t *new = malloc(sizeof(tree_node_t));
    if (new)
    {
        new->data = data;
        new->left = NULL;
        new->right = NULL;
    }

    return new;
}

tree_node_t *init_tree(FILE *f)
{
    long buf;
    tree_node_t *head = NULL;
    tree_node_t *node = NULL;

    while (fscanf(f, "%ld", &buf) == 1)
    {
        node = node_create(buf);
        if (!node)
        {
            tree_free(head);
            return NULL;
        }
        head = insert(head, node);
    }

    if (feof(f))
        return head;
    else
    {
        tree_free(head);
        return NULL;
    }
}

void tree_free(tree_node_t *head)
{
    if (!head)
        return;

    tree_free(head->right);
    tree_free(head->left);

    free(head);
}

tree_node_t *find(tree_node_t *head, long elem)
{
    if (!head)
        return NULL;

    if (head->data == elem)
        return head;

    if (head->data > elem)
        return find(head->right, elem);
    else
        return find(head->left, elem);
}

tree_node_t *insert(tree_node_t *head, tree_node_t *elem)
{
    if (!head)
        return elem;

    if (elem->data < head->data)
        head->left = insert(head->left, elem);
    else
        head->right = insert(head->right, elem);

    return head;
}

size_t get_height(tree_node_t *head)
{
    if (!head)
        return 0;

    size_t l, r;

    l = get_height(head->left);
    r = get_height(head->right);

    if (l > r)
        return l + 1;
    else
        return r + 1;
}

tree_node_t *rotate_right(tree_node_t *node)
{
    tree_node_t *buf = node->left;
    node->left = buf->right;
    buf->right = node;

    return buf;
}

tree_node_t *rotate_left(tree_node_t *node)
{
    tree_node_t *buf = node->right;
    node->right = buf->left;
    buf->left = node;

    return buf;
}

int cmp_balance(tree_node_t *node)
{
    if (!node)
        return 0;

    return get_height(node->right) - get_height(node->left);
}

tree_node_t *balance(tree_node_t *node)
{
    if (cmp_balance(node) == -2)
    {
        if (cmp_balance(node->left) > 0)
            node->left = rotate_left(node->left);

        return rotate_right(node);
    }

    if (cmp_balance(node) == 2)
    {
        if (cmp_balance(node->right) < 0)
            node->right = rotate_right(node->right);

        return rotate_left(node);
    }

    return node;
}

tree_node_t *insert_in_avl(tree_node_t *head, tree_node_t *elem)
{
    if (!head)
        return elem;

    if (elem->data > head->data)
        head->right = insert_in_avl(head->right, elem);
    else
        head->left = insert_in_avl(head->left, elem);

    return balance(head);
}

tree_node_t *init_balance_tree(FILE *f)
{
    fseek(f, 0, SEEK_SET);

    tree_node_t *head = NULL;
    tree_node_t *node = NULL;
    long buf;

    while (fscanf(f, "%ld", &buf) == 1)
    {
        node = node_create(buf);
        if (!node)
        {
            tree_free(head);
            return NULL;
        }
        head = insert_in_avl(head, node);
    }
    return head;
}

tree_node_t *remove_min(tree_node_t *head)
{
    if (!head->left)
        return head->right;
    head->left = remove_min(head->left);
    return head;
}

tree_node_t *find_min(tree_node_t *head)
{
    if (head->left)
        return find_min(head->left);
    return head;
}

tree_node_t *del(tree_node_t *head, long elem)
{
    if (!head)
        return NULL;

    if (elem < head->data)
        head->left = del(head->left, elem);
    else if (elem > head->data)
        head->right = del(head->right, elem);
    else
    {
        tree_node_t *l = head->left;
        tree_node_t *r = head->right;

        if (!r)
            return l;

        tree_node_t *min = find_min(r);
        min->right = remove_min(r);
        min->left = l;

        free(head);

        return min;
    }
    return head;
}

tree_node_t *del_in_avl(tree_node_t *head, long elem)
{
    if (!head)
        return NULL;

    if (elem < head->data)
        head->left = del_in_avl(head->left, elem);
    else if (elem > head->data)
        head->right = del_in_avl(head->right, elem);
    else
    {
        tree_node_t *l = head->left;
        tree_node_t *r = head->right;

        if (!r)
            return l;

        tree_node_t *min = find_min(r);
        min->right = remove_min(r);
        min->left = l;

        free(head);

        return balance(min);
    }
    return balance(head);
}

void export_node_dot(tree_node_t *node, FILE *f)
{
    if (node->left)
        fprintf(f, "%ld -> %ld;\n", node->data, node->left->data);
    if (node->right)
        fprintf(f, "%ld -> %ld;\n", node->data, node->right->data);
}

void export_prev_dot(tree_node_t *head, FILE *f)
{
    if (!head)
        return;

    export_node_dot(head, f);
    export_prev_dot(head->left, f);
    export_prev_dot(head->right, f);
}

void export_dot_tree(FILE *f, tree_node_t *head)
{
    fprintf(f, "digraph G {\n");

    export_prev_dot(head, f);

    fprintf(f, "}");
}
