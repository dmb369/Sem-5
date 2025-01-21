#include <stdio.h>
#include <stdlib.h>

struct TNode {
    int value;
    struct TNode* left;
    struct TNode* right;
};

struct Res {
    int include;
    int exclude;
};

// Function to create a new tree node
struct TNode* create(int value) {
    struct TNode* newNode = (struct TNode*)malloc(sizeof(struct TNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Depth-first search function to calculate max resources
struct Res dfs(struct TNode* node) {
    if (node == NULL) {
        struct Res res = {0, 0};
        return res;
    }

    struct Res l = dfs(node->left);
    struct Res r = dfs(node->right);
    
    int includeNode = node->value + l.exclude + r.exclude;
    int excludeNode = (l.include > l.exclude ? l.include : l.exclude) + 
                      (r.include > r.exclude ? r.include : r.exclude);

    struct Res res = {includeNode, excludeNode};
    return res;
}

// Function to get the maximum resources allocation
int get(struct TNode* root) {
    struct Res result = dfs(root);
    return (result.include > result.exclude) ? result.include : result.exclude;
}

int main() {
    struct TNode* ceo = create(10);
    struct TNode* finance = create(1);
    struct TNode* sales = create(2);
    struct TNode* hr = create(4);
    struct TNode* it = create(5);
    struct TNode* marketing = create(3);

    ceo->left = finance;
    ceo->right = sales;
    finance->left = hr;
    finance->right = it;
    sales->right = marketing;

    int maxResources = get(ceo);
    printf("Maximum resource allocation: %d\n", maxResources);

    return 0;
}
