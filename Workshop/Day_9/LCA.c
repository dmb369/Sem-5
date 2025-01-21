#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *left, *right;
    int key;
} Node;

Node* newNode(int key)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

Node* find(Node* root, int n1, int n2)
{
    if (root == NULL) return NULL;
    if (root->key == n1 || root->key == n2) return root;

    Node* l = find(root->left, n1, n2);
    Node* r = find(root->right, n1, n2);

    if (l && r) return root;
    return (l != NULL) ? l : r;
}

int main()
{
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    printf("LCA(4, 5) = %d\n", find(root, 4, 5)->key);
    return 0;
}
