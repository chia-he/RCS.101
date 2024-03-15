#include <stdio.h>
#include <stdlib.h>

#include "..\header\cstack.h"

typedef struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
} TreeNode;

int kthSmallest(TreeNode *root, int k) {
    if (!root) return 0;

    cstack(TreeNode *) cs = NULL;
    TreeNode *current = root;
    int ans = 0;
    int count = 0;

    while (current || !cstack_empty(cs)) {
        while (current) {
            cstack_push(cs, current);
            current = current->left;
        }
        current = *cstack_top(cs);
        cstack_pop(cs);
        count++;
        if (count == k) {
            ans = current->val;
            break;
        }
        current = current->right;
    }
    cstack_free(cs);

    return ans;
}
/* 
 * Recursive version
void inorderTraversalHelper(TreeNode *root, int *count, int *ans, int k) {
    if (!root) return;
    inorderTraversalHelper(root->left, count, ans, k);
    (*count)++;
    if ((*count)==k){
        *ans = root->val;
        return;
    }
    inorderTraversalHelper(root->right, count, ans, k);
}

int kthSmallest(TreeNode *root, int k) {
    if (!root) return 0;

    int count = 0;
    int ans = 0;
    inorderTraversalHelper(root, &count, &ans, k);

    return ans;
}
*/
// TreeNode *createNode(int value) {
//     TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
//     if (newNode) {
//         newNode->val = value;
//         newNode->left = NULL;
//         newNode->right = NULL;
//     }
//     return newNode;
// }

// int main() {
//     int k = 3;
//     TreeNode *root = createNode(5);
//     root->left = createNode(3);
//     root->right = createNode(6);
//     root->left->left = createNode(2);
//     root->left->right = createNode(4);
//     root->left->left->left = createNode(1);

//     printf("output: %d", kthSmallest(root, k));
// }