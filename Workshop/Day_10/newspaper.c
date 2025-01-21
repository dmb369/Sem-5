#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_cost(int n, int m, int e[m][3]) {
    int c[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = INT_MAX / 2;
        }
    }
    for (int i = 0; i < m; i++) {
        int u = e[i][0], v = e[i][1], w = e[i][2];
        c[u][v] = w;
        c[v][u] = w;
    }

    int dp[1 << n][n];
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INT_MAX / 2;
        }
    }
    dp[1][0] = 0;

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) continue;
            for (int j = 0; j < n; j++) {
                if ((mask & (1 << j)) || c[i][j] == INT_MAX / 2) continue;
                dp[mask | (1 << j)][j] = 
                    dp[mask | (1 << j)][j] < (dp[mask][i] + c[i][j])
                    ? dp[mask | (1 << j)][j]
                    : (dp[mask][i] + c[i][j]);
            }
        }
    }

    int min_cost = INT_MAX / 2;
    for (int i = 1; i < n; i++) {
        if (c[i][0] != INT_MAX / 2) {
            int cost = dp[(1 << n) - 1][i] + c[i][0];
            min_cost = min_cost < cost ? min_cost : cost;
        }
    }

    return min_cost == INT_MAX / 2 ? -1 : min_cost;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int e[m][3];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &e[i][0], &e[i][1], &e[i][2]);
    }
    printf("Min Cost: %d\n", min_cost(n, m, e));
    return 0;
}
