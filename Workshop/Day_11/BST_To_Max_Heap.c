#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int value;
    struct Node *left;
    struct Node *right;
};

struct Node* getNode(int value) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void inorder(struct Node* root, int* a, int* index) 
{
    if (root == NULL) return;
    inorder(root->left, a, index);
    a[(*index)++] = root->value;
    inorder(root->right, a, index);
}


void BTMH(struct Node* root, int* a, int* index) 
{
    if (root == NULL) return;
    BTMH(root->left, a, index);
    BTMH(root->right, a, index);
    root->value = a[(*index)++];
}


void convert(struct Node* root) 
{
    int a[100]; // Maximum of 100 elements
    int size = 0;
    inorder(root, a, &size);
    int index = 0;
    BTMH(root, a, &index);
}

void postorder(struct Node* root) 
{
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->value);
}

int main()
{
    struct Node* root = getNode(4);
    root->left = getNode(2);
    root->right = getNode(6);
    root->left->left = getNode(1);
    root->left->right = getNode(3);
    root->right->left = getNode(5);
    root->right->right = getNode(7);

    convert(root);

    printf("Postorder Traversal of Tree:\n");
    postorder(root);

    return 0;
}