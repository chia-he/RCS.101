#include <stdio.h>
#include <stdlib.h>

#include "..\header\cstack.h"

typedef struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
} TreeNode;

void preorderTraversalHelper(TreeNode *root, int *count, int *traversal,
                             int v) {
    if (!root) return;

    if (v)
        traversal[(*count)++] = root->val;
    else
        (*count)++;
    preorderTraversalHelper(root->left, count, traversal, v);
    preorderTraversalHelper(root->right, count, traversal, v);
}

int *preorderTraversal(TreeNode *root, int *returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }

    int count = 0;
    // count nodes
    preorderTraversalHelper(root, &count, NULL, 0);

    int *traversal = (int *)malloc(sizeof(int) * count);
    // traverse
    preorderTraversalHelper(root, returnSize, traversal, 1);
    return traversal;
}

/*
 * Iterative version
int *preorderTraversal(TreeNode *root, int *returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    } else {
        cstack(TreeNode *) cs = NULL;
        TreeNode *current = root;
        int *ans = NULL;
        int count = 0;
        while (current || !cstack_empty(cs)) {
            while (current) {
                ans = (int *)realloc(ans, (++count) * sizeof(int));
                ans[count - 1] = current->val;
                cstack_push(cs, current);
                current = current->left;
            }
            current = *cstack_top(cs);
            cstack_pop(cs);
            current = current->right;
        }
        cstack_free(cs);

        *returnSize = count;
        return ans;
    }
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
//     int returnSize = 0;
//     TreeNode *root = createNode(1);
//     root->right = createNode(2);
//     root->right->left = createNode(3);

//     int *ans = preorderTraversal(root, &returnSize);

//     for (int i = 0; i < returnSize; i++) {
//         printf("%d, ", *(ans + i));
//     }
//     free(ans);
// }