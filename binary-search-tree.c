#include "binary-search-tree.h"

#include <stdlib.h>

// The link (root or a child pointer) that holds the node equal to `value`,
// or the empty link where it would go.
static BinarySearchTreeNode** FindLink(BinarySearchTree* tree, const void* value)
{
    BinarySearchTreeNode** link = &tree->root;

    while (*link)
    {
        int comparison = tree->compare(value, (*link)->value);

        if (comparison == 0)
        {
            break;
        }

        link = comparison < 0 ? &(*link)->left : &(*link)->right;
    }

    return link;
}

// The node equal to `value`, or nullptr.
static BinarySearchTreeNode* FindNode(const BinarySearchTree* tree, const void* value)
{
    BinarySearchTreeNode* node = tree->root;

    while (node)
    {
        int comparison = tree->compare(value, node->value);

        if (comparison == 0)
        {
            break;
        }

        node = comparison < 0 ? node->left : node->right;
    }

    return node;
}

BinarySearchTree* BinarySearchTree_Create(BinarySearchTreeCompare compare)
{
    if (!compare)
    {
        return nullptr;
    }

    BinarySearchTree* tree = malloc(sizeof(*tree));

    if (tree)
    {
        *tree = (BinarySearchTree){.compare = compare};
    }

    return tree;
}

void BinarySearchTree_Clear(BinarySearchTree* tree)
{
    if (!tree)
    {
        return;
    }

    // Rotate left children up until the node has none, then free it and
    // continue with the right child: every node is visited once, no stack.
    BinarySearchTreeNode* node = tree->root;

    while (node)
    {
        if (node->left)
        {
            BinarySearchTreeNode* left = node->left;
            node->left = left->right;
            left->right = node;
            node = left;
        }
        else
        {
            BinarySearchTreeNode* right = node->right;
            free(node);
            node = right;
        }
    }

    tree->root = nullptr;
    tree->count = 0;
}

void BinarySearchTree_Delete(BinarySearchTree* tree)
{
    BinarySearchTree_Clear(tree);
    free(tree);
}

BinarySearchTreeNode* BinarySearchTree_Insert(BinarySearchTree* tree, void* value)
{
    if (!tree)
    {
        return nullptr;
    }

    BinarySearchTreeNode** link = FindLink(tree, value);

    if (*link)
    {
        (*link)->value = value;
        return *link;
    }

    BinarySearchTreeNode* node = malloc(sizeof(*node));

    if (!node)
    {
        return nullptr;
    }

    *node = (BinarySearchTreeNode){.value = value};
    *link = node;
    ++tree->count;

    return node;
}

void* BinarySearchTree_Find(const BinarySearchTree* tree, const void* value)
{
    if (!tree)
    {
        return nullptr;
    }

    BinarySearchTreeNode* node = FindNode(tree, value);

    return node ? node->value : nullptr;
}

bool BinarySearchTree_Contains(const BinarySearchTree* tree, const void* value)
{
    return tree && FindNode(tree, value) != nullptr;
}

void* BinarySearchTree_Remove(BinarySearchTree* tree, const void* value)
{
    if (!tree)
    {
        return nullptr;
    }

    BinarySearchTreeNode** link = FindLink(tree, value);
    BinarySearchTreeNode* node = *link;

    if (!node)
    {
        return nullptr;
    }

    void* removed = node->value;

    if (node->left && node->right)
    {
        // Two children: take over the in-order successor's value and unlink
        // that node instead (it has no left child by definition).
        BinarySearchTreeNode** successor_link = &node->right;

        while ((*successor_link)->left)
        {
            successor_link = &(*successor_link)->left;
        }

        BinarySearchTreeNode* successor = *successor_link;
        node->value = successor->value;
        *successor_link = successor->right;
        free(successor);
    }
    else
    {
        *link = node->left ? node->left : node->right;
        free(node);
    }

    --tree->count;

    return removed;
}

void* BinarySearchTree_Min(const BinarySearchTree* tree)
{
    if (!tree || !tree->root)
    {
        return nullptr;
    }

    BinarySearchTreeNode* node = tree->root;

    while (node->left)
    {
        node = node->left;
    }

    return node->value;
}

void* BinarySearchTree_Max(const BinarySearchTree* tree)
{
    if (!tree || !tree->root)
    {
        return nullptr;
    }

    BinarySearchTreeNode* node = tree->root;

    while (node->right)
    {
        node = node->right;
    }

    return node->value;
}

void BinarySearchTree_ForeachInOrder(BinarySearchTree* tree, BinarySearchTreeCallback callback, void* context)
{
    if (!tree || !callback)
    {
        return;
    }

    // Morris traversal: the right pointer of each left subtree's rightmost
    // node temporarily threads back to its ancestor, which replaces the
    // stack; every thread is removed again on the way back up.
    BinarySearchTreeNode* node = tree->root;

    while (node)
    {
        if (!node->left)
        {
            callback(node->value, context);
            node = node->right;
            continue;
        }

        BinarySearchTreeNode* predecessor = node->left;

        while (predecessor->right && predecessor->right != node)
        {
            predecessor = predecessor->right;
        }

        if (!predecessor->right)
        {
            predecessor->right = node; // thread, then descend left
            node = node->left;
        }
        else
        {
            predecessor->right = nullptr; // left subtree done
            callback(node->value, context);
            node = node->right;
        }
    }
}

size_t BinarySearchTree_Count(const BinarySearchTree* tree)
{
    return tree ? tree->count : 0;
}
