#include <stdio.h>
#include <stdlib.h>

struct L 
{
    int data;
    struct L* next;
};

struct T 
{
    int data;
    struct T* left;
    struct T* right;
};

struct L* newL(int data) {
    struct L* node = (struct L*)malloc(sizeof(struct L));
    node->data = data;
    node->next = NULL;
    return node;
}

struct T* newT(int data) {
    struct T* node = (struct T*)malloc(sizeof(struct T));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void printList(struct L* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void preOrder(struct T* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

struct L* getMid(struct L* head) {
    if (head == NULL) return head;
    
    struct L* slow = head;
    struct L* fast = head->next;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

struct L* mergeSL(struct L* a, struct L* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    struct L* result = NULL;
    if (a->data <= b->data) 
    {
        result = a;
        result->next = mergeSL(a->next, b);
    } 
    else 
    {
        result = b;
        result->next = mergeSL(a, b->next);
    }
    
    return result;
}

struct L* mergeSort(struct L* head) {
    if (head == NULL || head->next == NULL)
        return head;

    struct L* middle = getMid(head);
    struct L* nextom = middle->next;

    middle->next = NULL;

    struct L* left = mergeSort(head);
    struct L* right = mergeSort(nextom);

    return mergeSL(left, right);
}

struct T* LTBR(struct L** head_ref, int n) {
    if (n <= 0)
        return NULL;

    struct T* left = LTBR(head_ref, n / 2);
    struct T* root = newT((*head_ref)->data);

    root->left = left;

    *head_ref = (*head_ref)->next;
    root->right = LTBR(head_ref, n - n / 2 - 1);

    return root;
}

int count(struct L* head) {
    int count = 0;
    struct L* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

struct T* LTB(struct L* head) {
    int n = count(head);
    return LTBR(&head, n);
}

int main() {

    struct L* head = newL(10);
    head->next = newL(1);
    head->next->next = newL(8);
    head->next->next->next = newL(5);
    head->next->next->next->next = newL(6);

    printf("Unsorted Linked List:\n");
    printList(head);

    head = mergeSort(head);

    printf("Sorted Linked List:\n");
    printList(head);

    struct T* root = LTB(head);

    printf("Preorder Traversal of constructed BST:\n");
    preOrder(root);

    return 0;
}