#include <stdio.h>
#include <stdlib.h>

int min(int a, int b, int c) {
    if (a < b && a < c) return a;
    if (b < c) return b;
    return c;
}

int cost(int** a, int m, int n) {
    int dp[m][n]; 
    dp[0][0] = a[0][0];

    for (int i = 1; i < m; i++) dp[i][0] = dp[i - 1][0] + a[i][0];
    for (int j = 1; j < n; j++) dp[0][j] = dp[0][j - 1] + a[0][j];

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = a[i][j] + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
        }
    }

    return dp[m - 1][n - 1];
}

int main() {
    int m, n;
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &m, &n);

    int a[m][n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int* pointer[m];
    for (int i = 0; i < m; i++) {
        pointer[i] = a[i];
    }

    int result = cost(pointer, m, n);
    printf("Minimum cost is: %d\n", result);

    return 0;
}
