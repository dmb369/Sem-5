#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Get precedence of an operator
int get_precedence(char operator) 
{
    if (operator == '+' || operator == '-') return 1;
    if (operator == '*' || operator == '/') return 2;
    return 0;
}

// Check if character is an operator
int is_operator(char c) 
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Check if character is a number
int is_operand(char c) 
{
    return isdigit(c);
}

// Convert infix expression to postfix
void infix_to_postfix(const char* expression, char* postfix) 
{
    char operators[100];
    int top = -1, j = 0;

    for (int i = 0; expression[i]; i++) 
    {
        if (is_operand(expression[i])) 
        {
            postfix[j++] = expression[i];
        } 
        else if (expression[i] == '(') 
        {
            operators[++top] = expression[i];
        } 
        else if (expression[i] == ')')
        {
            while (top >= 0 && operators[top] != '(') 
            {
                postfix[j++] = operators[top--];
            }
            top--;  // Remove '(' from stack
        } 
        else if (is_operator(expression[i])) 
        {
            while (top >= 0 && get_precedence(operators[top]) >= get_precedence(expression[i])) 
            {
                postfix[j++] = operators[top--];
            }
            operators[++top] = expression[i];
        }
    }

    while (top >= 0) 
    {
        postfix[j++] = operators[top--];
    }
    postfix[j] = '\0';
}

// Evaluate the postfix expression
int evaluate_postfix(const char* postfix) {
    int stack[100], top = -1;

    for (int i = 0; postfix[i]; i++) {
        if (is_operand(postfix[i])) {
            stack[++top] = postfix[i] - '0';
        } else {
            int right = stack[top--];
            int left = stack[top--];

            switch (postfix[i]) {
                case '+': stack[++top] = left + right; break;
                case '-': stack[++top] = left - right; break;
                case '*': stack[++top] = left * right; break;
                case '/': stack[++top] = left / right; break;
            }
        }
    }
    return stack[top];
}

int main() {
    char expression[100], postfix[100];

    printf("Enter an infix expression: ");
    scanf("%s", expression);

    infix_to_postfix(expression, postfix);
    printf("Postfix expression: %s\n", postfix);

    int result = evaluate_postfix(postfix);
    printf("Evaluation result: %d\n", result);

    return 0;
}
