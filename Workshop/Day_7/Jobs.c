#include <stdio.h>
#include <stdlib.h>

int *endTimes;

int compare(const void *a, const void *b) {
    return endTimes[*(int *)a] - endTimes[*(int *)b];
}

int maxProfit(int s[], int e[], int p[], int n) {
    endTimes = e;

    int ind[n];
    for (int i = 0; i < n; i++) ind[i] = i;

    qsort(ind, n, sizeof(int), compare);

    int dp[n];
    dp[0] = p[ind[0]];

    for (int i = 1; i < n; i++) {
        int current = ind[i];
        dp[i] = p[current];

        for (int j = 0; j < i; j++) {
            int prev = ind[j];
            if (s[current] >= e[prev]) {
                if (dp[j] + p[current] > dp[i]) {
                    dp[i] = dp[j] + p[current];
                }
            }
        }
    }

    int maxProfit = dp[0];
    for (int i = 1; i < n; i++) {
        if (dp[i] > maxProfit) {
            maxProfit = dp[i];
        }
    }

    return maxProfit;
}

int main() {
    int n;
    scanf("%d", &n);

    int s[n], e[n], p[n];
    for (int i = 0; i < n; i++) scanf("%d", &s[i]);
    for (int i = 0; i < n; i++) scanf("%d", &e[i]);
    for (int i = 0; i < n; i++) scanf("%d", &p[i]);

    printf("Maximum Profit: %d\n", maxProfit(s, e, p, n));
    return 0;
}
