#ifndef __BST_H
#define __BST_H

#include <stddef.h>

/**
 * Definition for a binary tree node (LeetCode style).
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/* Allocate and initialize a new node */
struct TreeNode *create_node(int val);

/* Insert a value into the BST */
struct TreeNode *bst_insert(struct TreeNode *root, int val);

/* Search for a value in the BST */
struct TreeNode *bst_search(struct TreeNode *root, int val);

/* Find the node with the minimum value */
struct TreeNode *bst_minimum(struct TreeNode *root);

/* Find the node with the maximum value */
struct TreeNode *bst_maximum(struct TreeNode *root);

/* Delete a value from the BST */
struct TreeNode *bst_delete(struct TreeNode *root, int val);

/* Print BST in in-order traversal */
void bst_inorder_print(struct TreeNode *root);

#endif // __BST_H

