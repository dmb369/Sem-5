#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int data;
    struct Node* next;
    struct Node* down;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    node->down = NULL;
    return node;
}

struct Node* flatten(struct Node* head) {
    if (head == NULL) return NULL;
    
    struct Node* h = head;
    struct Node* stack[100]; 
    int top = -1;          
    struct Node* prev = NULL;

    stack[++top] = head;

    while (top != -1) {
        struct Node* temp = stack[top--];

        if (temp->next != NULL)
            stack[++top] = temp->next;
        if (temp->down != NULL)
            stack[++top] = temp->down;

        if (prev != NULL)
            prev->next = temp;

        prev = temp;
    }

    return h;
}

void print(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(4);
    head->next->down = newNode(5);
    head->next->down->next = newNode(6);
    head->next->down->next->next = newNode(7);
    head->next->down->next->next->next = newNode(8);
    head->next->down->next->down = newNode(9);
    head->next->down->next->down->next = newNode(10);
    head->next->down->next->down->next->next = newNode(11);

    // Flatten the list
    struct Node* flattenedList = flatten(head);

    // Print the flattened list
    print(flattenedList);

    return 0;
}
