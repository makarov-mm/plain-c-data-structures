#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <stddef.h>
#include "binary-search-tree-node.h"

typedef int (*BinarySearchTreeCompare)(const void* left, const void* right);

typedef struct BinarySearchTree {
    struct BinarySearchTreeNode* root;
    BinarySearchTreeCompare compare;
    size_t count;
} BinarySearchTree;

extern BinarySearchTree* BinarySearchTree_Create(BinarySearchTreeCompare compare);
extern void BinarySearchTree_Clear(BinarySearchTree* tree);
extern void BinarySearchTree_Delete(BinarySearchTree* tree);

extern BinarySearchTreeNode* BinarySearchTree_Insert(BinarySearchTree* tree, void* value);
extern void* BinarySearchTree_Find(const BinarySearchTree* tree, const void* value);
extern void* BinarySearchTree_Remove(BinarySearchTree* tree, const void* value);

extern void BinarySearchTree_ForeachInOrder(
    BinarySearchTree* tree,
    void (*callback)(void* value)
);

extern size_t BinarySearchTree_Count(const BinarySearchTree* tree);

#endif
