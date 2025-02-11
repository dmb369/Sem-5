#include <stdio.h>
#include <string.h>
#include <ctype.h>

int prodCount;
char gr[10][10], firstSet[10][10], followSet[10][10];
char firstTmp[10], followTmp[10];

// Compute FIRST set for a given symbol
void fFirst(char sym, int *idx) {
    if (!isupper(sym)) {
        firstTmp[(*idx)++] = sym;
        return;
    }

    for (int i = 0; i < prodCount; i++) {
        if (gr[i][0] == sym) {
            for (int j = 3; gr[i][j] != '\0'; j++) {
                if (gr[i][j] == '|') {
                    continue;  // Skip '|'
                }
                if (gr[i][j] == 'e') {  // Handle epsilon
                    firstTmp[(*idx)++] = 'e';
                    break;
                } else if (islower(gr[i][j]) || gr[i][j] == '(' || gr[i][j] == ')') {
                    firstTmp[(*idx)++] = gr[i][j];
                    break;
                } else {
                    fFirst(gr[i][j], idx);
                    if (strchr(firstTmp, 'e') == NULL) {
                        break;
                    }
                }
            }
        }
    }
}

// Compute FOLLOW set for a given symbol
void fFollow(char sym, int *idx) {
    if (gr[0][0] == sym) {
        followTmp[(*idx)++] = '$';  // Add $ to follow of start symbol
    }

    for (int i = 0; i < prodCount; i++) {
        for (int j = 3; j < strlen(gr[i]); j++) {
            if (gr[i][j] == sym) {
                if (gr[i][j + 1] != '\0' && gr[i][j + 1] != '|') {
                    int tmpIdx = 0;
                    fFirst(gr[i][j + 1], &tmpIdx);

                    for (int k = 0; k < tmpIdx; k++) {
                        if (firstTmp[k] != 'e') {
                            followTmp[(*idx)++] = firstTmp[k];
                        }
                    }
                }
                if ((gr[i][j + 1] == '\0' || gr[i][j + 1] == '|') && gr[i][0] != sym) {
                    fFollow(gr[i][0], idx);
                }
            }
        }
    }
}

int main() {
    int i, j;
    char curNT;

    printf("Enter total number of productions: ");
    scanf("%d", &prodCount);

    printf("Enter the productions (e.g., E->E+T|T or E->e):\n");
    for (i = 0; i < prodCount; i++) {
        scanf("%s", gr[i]);
    }

    for (i = 0; i < prodCount; i++) {
        curNT = gr[i][0];
        memset(firstTmp, 0, sizeof(firstTmp));

        int idx = 0;
        fFirst(curNT, &idx);

        printf("FIRST(%c) = { ", curNT);
        for (j = 0; firstTmp[j] != '\0'; j++) {
            printf("%c ", firstTmp[j]);
        }
        printf("}\n");
    }

    for (i = 0; i < prodCount; i++) {
        curNT = gr[i][0];
        memset(followTmp, 0, sizeof(followTmp));

        int idx = 0;
        fFollow(curNT, &idx);

        printf("FOLLOW(%c) = { ", curNT);
        for (j = 0; followTmp[j] != '\0'; j++) {
            printf("%c ", followTmp[j]);
        }
        printf("}\n");
    }

    return 0;
}
