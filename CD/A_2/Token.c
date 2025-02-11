#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1000

enum TokenCategory {
    VAR_IDENTIFIER,
    RESERVED_WORD,
    NUMERIC_LITERAL,
    MATH_OPERATOR,
    TOKEN_SEPARATOR,
    UNRECOGNIZED
};

const char *reservedWords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

int isReservedWord(const char *term) {
    for (int idx = 0; idx < sizeof(reservedWords) / sizeof(reservedWords[0]); idx++) {
        if (strcmp(term, reservedWords[idx]) == 0) {
            return 1;
        }
    }
    return 0;
}

enum TokenCategory categorizeToken(const char *token) {
    if (isReservedWord(token)) {
        return RESERVED_WORD;
    } else if (isdigit(token[0])) {
        return NUMERIC_LITERAL;
    } else if (isalpha(token[0]) || token[0] == '_') {
        return VAR_IDENTIFIER;
    } else if (strchr("+-*/%=&|!<>^", token[0]) != NULL) {
        return MATH_OPERATOR;
    } else if (strchr(",;(){}[]", token[0]) != NULL) {
        return TOKEN_SEPARATOR;
    }
    return UNRECOGNIZED;
}

const char* describeTokenCategory(enum TokenCategory category) {
    switch (category) {
        case VAR_IDENTIFIER: return "Variable Identifier";
        case RESERVED_WORD: return "Reserved Word";
        case NUMERIC_LITERAL: return "Numeric Literal";
        case MATH_OPERATOR: return "Mathematical Operator";
        case TOKEN_SEPARATOR: return "Token Separator";
        case UNRECOGNIZED: return "Unrecognized";
    }
    return "Unrecognized";
}

void analyzeCodeTokens(const char *sourceCode) {
    char tempCode[strlen(sourceCode) + 1];
    strcpy(tempCode, sourceCode);

    char *currentToken = strtok(tempCode, " \t\n");
    while (currentToken != NULL) {
        enum TokenCategory category = categorizeToken(currentToken);
        printf("Token: %-15s Type: %s\n", currentToken, describeTokenCategory(category));
        currentToken = strtok(NULL, " \t\n");
    }
}

int main() {
    char inputCode[BUFFER_SIZE];

    printf("Enter a C code snippet:\n");
    fgets(inputCode, BUFFER_SIZE, stdin);

    analyzeCodeTokens(inputCode);
    return 0;
}
