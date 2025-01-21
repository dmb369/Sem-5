#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Helper function to calculate maximum
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to calculate maximum robbery
int robHelper(struct TreeNode *root, int *robbed, int *notRobbed) {
    if (!root) {
        *robbed = 0;
        *notRobbed = 0;
        return 0;
    }
    int leftRobbed, leftNotRobbed, rightRobbed, rightNotRobbed;
    
    robHelper(root->left, &leftRobbed, &leftNotRobbed);
    robHelper(root->right, &rightRobbed, &rightNotRobbed);
    
    *robbed = root->val + leftNotRobbed + rightNotRobbed;
    *notRobbed = max(leftRobbed, leftNotRobbed) + max(rightRobbed, rightNotRobbed);
    
    return max(*robbed, *notRobbed);
}

int rob(struct TreeNode *root) {
    int robbed, notRobbed;
    return robHelper(root, &robbed, &notRobbed);
}

// Helper function to create a new TreeNode
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Example usage
int main() {
    struct TreeNode* root = newNode(3);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->right = newNode(3);
    root->right->right = newNode(1);

    printf("Maximum amount: %d\n", rob(root));
    return 0;
}
