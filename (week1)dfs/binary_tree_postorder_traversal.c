#include <stdio.h>
#include <stdlib.h>

#include "..\header\cstack.h"

typedef struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
} TreeNode;

void postorderTraversalHelper(TreeNode *root, int *count, int *traversal,
                              int v) {
    if (!root) return;

    postorderTraversalHelper(root->left, count, traversal, v);
    postorderTraversalHelper(root->right, count, traversal, v);
    if (v)
        traversal[(*count)++] = root->val;
    else
        (*count)++;
}

int *postorderTraversal(TreeNode *root, int *returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }

    int count = 0;
    // count nodes
    postorderTraversalHelper(root, &count, NULL, 0);

    int *traversal = (int *)malloc(sizeof(int) * count);
    // traverse
    postorderTraversalHelper(root, returnSize, traversal, 1);
    return traversal;
}

/*
 * Iterative version
int *postorderTraversal(TreeNode *root, int *returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    } else {
        cstack(TreeNode *) cs = NULL;
        TreeNode *current = root;
        TreeNode *visited = NULL;
        int *ans = NULL;
        int count = 0;
        while (current || !cstack_empty(cs)) {
            while (current) {
                cstack_push(cs, current);
                current = current->left;
            }
            current = *cstack_top(cs);
            if (!current->right || current->right == visited) {
                ans = (int *)realloc(ans, (++count) * sizeof(int));
                ans[count - 1] = current->val;
                visited = current;
                cstack_pop(cs);
                current = NULL;
            } else {
                current = current->right;
            }
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

//     int *ans = postorderTraversal(root, &returnSize);

//     for (int i = 0; i < returnSize; i++) {
//         printf("%d, ", *(ans + i));
//     }
//     free(ans);
// }