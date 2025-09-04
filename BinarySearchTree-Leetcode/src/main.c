// src/main.c
#include "bst.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ---------- helpers ---------- */

static void free_tree(struct TreeNode *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

static int is_bst_rec(struct TreeNode *root, long minv, long maxv) {
    if (!root) return 1;
    if (!(minv < root->val && root->val < maxv)) return 0;
    return is_bst_rec(root->left, minv, root->val) &&
           is_bst_rec(root->right, root->val, maxv);
}

static int is_bst(struct TreeNode *root) {
    return is_bst_rec(root, LONG_MIN, LONG_MAX);
}

static int inorder_collect(struct TreeNode *root, int *out, int i) {
    if (!root) return i;
    i = inorder_collect(root->left, out, i);
    out[i++] = root->val;
    i = inorder_collect(root->right, out, i);
    return i;
}

static int node_count(struct TreeNode *root) {
    if (!root) return 0;
    return 1 + node_count(root->left) + node_count(root->right);
}

static void print_inorder(struct TreeNode *root, const char *tag) {
    int n = node_count(root);
    int *buf = n ? malloc(sizeof(int) * n) : NULL;
    int m = inorder_collect(root, buf, 0);
    printf("%s (%d nodes):", tag, m);
    for (int i = 0; i < m; ++i) printf(" %d", buf[i]);
    printf("\n");
    free(buf);
}

/* ---------- tests ---------- */

static void test_build_and_search(void) {
    printf("\n== test_build_and_search ==\n");
    int vals[] = {5, 3, 7, 2, 4, 6, 8};
    struct TreeNode *root = NULL;
    for (size_t i = 0; i < sizeof(vals)/sizeof(vals[0]); ++i)
        root = bst_insert(root, vals[i]);

    assert(is_bst(root));
    print_inorder(root, "inorder after inserts");

    // search existing
    assert(bst_search(root, 5) != NULL);
    assert(bst_search(root, 2) != NULL);
    assert(bst_search(root, 8) != NULL);
    // search missing
    assert(bst_search(root, 42) == NULL);

    // min / max
    struct TreeNode *mn = bst_minimum(root);
    struct TreeNode *mx = bst_maximum(root);
    assert(mn && mn->val == 2);
    assert(mx && mx->val == 8);

    free_tree(root);
}

static void test_delete_leaf_onechild_twochildren(void) {
    printf("\n== test_delete_leaf_onechild_twochildren ==\n");
    int vals[] = {5, 3, 7, 2, 4, 6, 8};
    struct TreeNode *root = NULL;
    for (size_t i = 0; i < sizeof(vals)/sizeof(vals[0]); ++i)
        root = bst_insert(root, vals[i]);
    print_inorder(root, "initial");

    // 1) delete leaf: 2
    root = bst_delete(root, 2);
    assert(is_bst(root));
    assert(bst_search(root, 2) == NULL);
    print_inorder(root, "after delete leaf (2)");

    // 2a) delete leaf 8 so that 7 becomes one-child (only left 6)
    root = bst_delete(root, 8);
    assert(is_bst(root));
    print_inorder(root, "after delete leaf (8)");

    // 2b) delete one-child node: 7 (has only left child 6 now)
    root = bst_delete(root, 7);
    assert(is_bst(root));
    assert(bst_search(root, 7) == NULL);
    print_inorder(root, "after delete one-child (7)");

    // 3) delete two-children node: 5 (root has left=3 subtree, right=6)
    root = bst_delete(root, 5);
    assert(is_bst(root));
    assert(bst_search(root, 5) == NULL);
    print_inorder(root, "after delete two-children (5)");

    free_tree(root);
}

int main(void) {
    printf("BST (LeetCode TreeNode) test runner\n");

    test_build_and_search();
    test_delete_leaf_onechild_twochildren();

    printf("\nAll tests passed (assertions held).\n");
    return 0;
}

