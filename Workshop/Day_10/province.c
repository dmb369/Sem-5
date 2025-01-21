#include <stdio.h>
#include <stdbool.h>

void dfs(int c[][200], int n, bool v[], int ct) {
    v[ct] = true;
    for (int i = 0; i < n; i++) {
        if (c[ct][i] == 1 && !v[i]) {
            dfs(c, n, v, i);
        }
    }
}

int p(int c[][200], int n) {
    bool v[200] = {false};
    int tot = 0;

    for (int i = 0; i < n; i++) {
        if (!v[i]) {
            dfs(c, n, v, i);
            tot++;
        }
    }
    return tot;
}

int main() {
    int n, c[200][200]; // Assumed 200x200 connectivity matrix
    printf("Enter the number of cities: ");
    scanf("%d", &n);

    // Trivial case
    if (n < 0) 
    { 
        printf("Number of cities cannot be less than 0.\n");
        return 1;
    }

    printf("Enter the %dx%d connectivity matrix:\n", n, n);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) scanf("%d", &c[i][j]);
    
    int provinces = p(c, n);
    printf("Number of provinces: %d\n", provinces);

    return 0;
}
