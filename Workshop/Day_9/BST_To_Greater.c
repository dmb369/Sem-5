#include <stdio.h>
#include <stdlib.h>

struct TNode {
    int val;
    struct TNode *left;
    struct TNode *right;
};


struct TNode* newNode(int val) {
    if (val == -1) return NULL; 
    struct TNode* node = (struct TNode*)malloc(sizeof(struct TNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}


struct TNode* buildTree(int arr[], int n, int i) {
    if (i >= n || arr[i] == -1) return NULL;

    struct TNode* root = newNode(arr[i]);
    root->left = buildTree(arr, n, 2 * i + 1);  
    root->right = buildTree(arr, n, 2 * i + 2); 

    return root;
}


void btg(struct TNode* root, int* sum) {
    if (root == NULL) return;
    btg(root->right, sum);
    *sum += root->val;
    root->val = *sum;
    btg(root->left, sum);
}


void convert(struct TNode* root) {
    int sum = 0;
    btg(root, &sum);
}


void traverse(struct TNode* root) {
    if (root != NULL) {
        traverse(root->left);
        printf("%d ", root->val);
        traverse(root->right);
    }
}

int main() {
    int arr[] = {4, 1, 6, 0, 2, 5, 7, -1, -1, -1, 3, -1, -1, -1, 8};  // -1 as NULL
    int n = sizeof(arr) / sizeof(arr[0]);

    struct TNode* root = buildTree(arr, n, 0);

    convert(root);

    printf("In-order traversal of GST: ");
    traverse(root);
    printf("\n");

    return 0;
}
