#include <stdlib.h>
#include <stdio.h>
#include "..\header\cvector.h"

typedef struct TreeNode {
        int val;
        struct TreeNode *left, *right;
} TreeNode;

int find_closest_leaf(TreeNode *root, int k) {
    if (!root) return 0;
    if (!root->left && !root->right) return root->val;

    TreeNode *curr = root;
    cvector(TreeNode *) cq = NULL;
    cvector_push_back(cq, curr);

    // find the target k
    TreeNode *target = NULL;
    while (!cvector_empty(cq)) {
        curr = *cvector_front(cq);
        cvector_erase(cq, 0);
        // find the closest
        if (curr->val == k) {
            target = curr;
            break;
        }
        if (curr->left) cvector_push_back(cq, curr->left);
        if (curr->right) cvector_push_back(cq, curr->right);
    }
    // cannot find target k, return any leaf.
    if (!target) return curr->val;

    cvector_clear(cq);
    cvector_push_back(cq, curr);
    // find the closest leaf
    while (!cvector_empty(cq)) {
        curr = *cvector_front(cq);
        cvector_erase(cq, 0);
        if (!curr->left && !curr->right) return curr->val;
        if (curr->left) cvector_push_back(cq, curr->left);
        if (curr->right) cvector_push_back(cq, curr->right);
    }
}

TreeNode *createNode(int data) {
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->val = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}
// int main() {
//     int k = 2;
//     TreeNode *root = createNode(1);
//     root->left = createNode(3);
//     root->right = createNode(2);
//     root->right->left = createNode(4);
//     root->right->right = createNode(5);
//     root->right->left->left = createNode(6);

//     int ans = find_closest_leaf(root, k);
//     printf("Output: %d\n", ans);
// }