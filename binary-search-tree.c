#include "binary-search-tree.h"

#include <stdlib.h>

static BinarySearchTreeNode* BinarySearchTree_CreateNode(void* value)
{
    BinarySearchTreeNode* node = malloc(sizeof(*node));

    if (!node)
    {
        return NULL;
    }

    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static void BinarySearchTree_ClearNode(BinarySearchTreeNode* node)
{
    if (!node)
    {
        return;
    }

    BinarySearchTree_ClearNode(node->left);
    BinarySearchTree_ClearNode(node->right);
    free(node);
}

static void BinarySearchTree_ForeachNodeInOrder(
    BinarySearchTreeNode* node,
    void (*callback)(void* value))
{
    if (!node)
    {
        return;
    }

    BinarySearchTree_ForeachNodeInOrder(node->left, callback);
    callback(node->value);
    BinarySearchTree_ForeachNodeInOrder(node->right, callback);
}

static void* BinarySearchTree_RemoveNode(
    BinarySearchTree* tree,
    BinarySearchTreeNode** node_pointer,
    const void* value)
{
    BinarySearchTreeNode* node = *node_pointer;

    if (!node)
    {
        return NULL;
    }

    int comparison = tree->compare(value, node->value);

    if (comparison < 0)
    {
        return BinarySearchTree_RemoveNode(tree, &node->left, value);
    }

    if (comparison > 0)
    {
        return BinarySearchTree_RemoveNode(tree, &node->right, value);
    }

    void* removed_value = node->value;

    if (!node->left)
    {
        *node_pointer = node->right;
        free(node);
        --tree->count;
        return removed_value;
    }

    if (!node->right)
    {
        *node_pointer = node->left;
        free(node);
        --tree->count;
        return removed_value;
    }

    BinarySearchTreeNode** successor_pointer = &node->right;
    BinarySearchTreeNode* successor = node->right;

    while (successor->left)
    {
        successor_pointer = &successor->left;
        successor = successor->left;
    }

    node->value = successor->value;
    *successor_pointer = successor->right;
    free(successor);
    --tree->count;

    return removed_value;
}

BinarySearchTree* BinarySearchTree_Create(BinarySearchTreeCompare compare)
{
    if (!compare)
    {
        return NULL;
    }

    BinarySearchTree* tree = malloc(sizeof(*tree));

    if (!tree)
    {
        return NULL;
    }

    tree->root = NULL;
    tree->compare = compare;
    tree->count = 0;

    return tree;
}

void BinarySearchTree_Clear(BinarySearchTree* tree)
{
    if (!tree)
    {
        return;
    }

    BinarySearchTree_ClearNode(tree->root);
    tree->root = NULL;
    tree->count = 0;
}

void BinarySearchTree_Delete(BinarySearchTree* tree)
{
    if (!tree)
    {
        return;
    }

    BinarySearchTree_Clear(tree);
    free(tree);
}

BinarySearchTreeNode* BinarySearchTree_Insert(BinarySearchTree* tree, void* value)
{
    if (!tree)
    {
        return NULL;
    }

    BinarySearchTreeNode** current_pointer = &tree->root;

    while (*current_pointer)
    {
        int comparison = tree->compare(value, (*current_pointer)->value);

        if (comparison < 0)
        {
            current_pointer = &(*current_pointer)->left;
        }
        else if (comparison > 0)
        {
            current_pointer = &(*current_pointer)->right;
        }
        else
        {
            (*current_pointer)->value = value;
            return *current_pointer;
        }
    }

    *current_pointer = BinarySearchTree_CreateNode(value);

    if (!*current_pointer)
    {
        return NULL;
    }

    ++tree->count;

    return *current_pointer;
}

void* BinarySearchTree_Find(const BinarySearchTree* tree, const void* value)
{
    if (!tree)
    {
        return NULL;
    }

    BinarySearchTreeNode* current = tree->root;

    while (current)
    {
        int comparison = tree->compare(value, current->value);

        if (comparison < 0)
        {
            current = current->left;
        }
        else if (comparison > 0)
        {
            current = current->right;
        }
        else
        {
            return current->value;
        }
    }

    return NULL;
}

void* BinarySearchTree_Remove(BinarySearchTree* tree, const void* value)
{
    if (!tree)
    {
        return NULL;
    }

    return BinarySearchTree_RemoveNode(tree, &tree->root, value);
}

void BinarySearchTree_ForeachInOrder(
    BinarySearchTree* tree,
    void (*callback)(void* value))
{
    if (!tree || !callback)
    {
        return;
    }

    BinarySearchTree_ForeachNodeInOrder(tree->root, callback);
}

size_t BinarySearchTree_Count(const BinarySearchTree* tree)
{
    if (!tree)
    {
        return 0;
    }

    return tree->count;
}
