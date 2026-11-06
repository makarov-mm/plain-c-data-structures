#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct BinarySearchTreeNode
{
    void* value;
    struct BinarySearchTreeNode* left;
    struct BinarySearchTreeNode* right;
} BinarySearchTreeNode;

// Returns < 0, 0 or > 0 like strcmp.
typedef int (*BinarySearchTreeCompare)(const void* left, const void* right);

// An unbalanced binary search tree of void* values ordered by `compare`.
// Nodes are owned; values are not. No operation recurses, so a degenerate
// (list-shaped) tree is slow but never overflows the stack.
typedef struct BinarySearchTree
{
    BinarySearchTreeNode* root;
    BinarySearchTreeCompare compare;
    size_t count;
} BinarySearchTree;

typedef void (*BinarySearchTreeCallback)(void* value, void* context);

[[nodiscard]] BinarySearchTree* BinarySearchTree_Create(BinarySearchTreeCompare compare);
void BinarySearchTree_Clear(BinarySearchTree* tree);
void BinarySearchTree_Delete(BinarySearchTree* tree);

// Inserts the value; if an equal value is already stored, replaces it and
// returns that node. nullptr if memory ran out.
BinarySearchTreeNode* BinarySearchTree_Insert(BinarySearchTree* tree, void* value);
// The stored value equal to `value`, or nullptr.
void* BinarySearchTree_Find(const BinarySearchTree* tree, const void* value);
bool BinarySearchTree_Contains(const BinarySearchTree* tree, const void* value);
// Removes the value equal to `value` and returns the stored one (nullptr when absent).
void* BinarySearchTree_Remove(BinarySearchTree* tree, const void* value);
// Smallest / largest stored value (nullptr when empty).
void* BinarySearchTree_Min(const BinarySearchTree* tree);
void* BinarySearchTree_Max(const BinarySearchTree* tree);

// Visits the values in ascending order. The tree must not be modified from
// the callback.
void BinarySearchTree_ForeachInOrder(BinarySearchTree* tree, BinarySearchTreeCallback callback, void* context);

size_t BinarySearchTree_Count(const BinarySearchTree* tree);
