#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    char op;
    int prec;
} Op;

// Stack for operators
typedef struct {
    char items[MAX];
    int top;
} Stack;

// Stack functions
void initStack(Stack* s) {
    s->top = -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, char item) {
    if (!isFull(s)) {
        s->items[++(s->top)] = item;
    } else {
        printf("Stack overflow\n");
    }
}

char pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0'; // return null char if stack is empty
}

char peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return '\0'; // return null char if stack is empty
}

// Function to return precedence of operators
int getPrec(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Function to evaluate a simple operation
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("Division by zero!\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
    }
    return 0;
}

// Function to evaluate the expression
int eval(char* expr) {
    Stack valStack;
    Stack opStack;
    initStack(&valStack);
    initStack(&opStack);

    for (int i = 0; i < strlen(expr); i++) {
        // Skip whitespace
        if (isspace(expr[i])) {
            continue;
        }

        // If the character is a number, push it to the values stack
        if (isdigit(expr[i])) {
            int v = 0;
            while (i < strlen(expr) && isdigit(expr[i])) {
                v = v * 10 + (expr[i] - '0');
                i++;
            }
            i--; // Decrement i because it will be incremented in the for loop
            push(&valStack, v);
        } 
        // If the character is an operator
        else {
            while (!isEmpty(&opStack) && getPrec(peek(&opStack)) >= getPrec(expr[i])) {
                int b = pop(&valStack);
                int a = pop(&valStack);
                char op = pop(&opStack);
                int res = applyOp(a, b, op);
                push(&valStack, res);
            }
            push(&opStack, expr[i]);
        }
    }

    // After the end of the expression, apply remaining operations
    while (!isEmpty(&opStack)) {
        int b = pop(&valStack);
        int a = pop(&valStack);
        char op = pop(&opStack);
        int res = applyOp(a, b, op);
        push(&valStack, res);
    }

    return pop(&valStack); // The final result is at the top of the values stack
}

int main() {
    char expr[MAX];
    printf("Enter an arithmetic expression: ");
    fgets(expr, MAX, stdin);

    // Remove newline character
    expr[strcspn(expr, "\n")] = 0;

    int result = eval(expr);
    printf("Result: %d\n", result);

    return 0;
}
