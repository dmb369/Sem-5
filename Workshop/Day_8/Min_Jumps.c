#include <stdio.h>
#include <limits.h>

int jump(int a[], int l, int h)
{
    // Base case: when source and destination are same
    if (h == l) return 0;

    // When nothing is reachable from the given source
    if (a[l] == 0) return INT_MAX;

    int m = INT_MAX;
    for (int i = l + 1; i <= h && i <= l + a[l]; i++) 
    {
        int j = jump(a, i, h);
        if (j != INT_MAX && j + 1 < m) m = j + 1;
    }
    return m;
}

int main()
{
    int n;
    printf("Enter the number of elements:");
    scanf("%d",&n);

    int a[n];
    for (int i=0; i<n; i++) scanf("%d", &a[i]);
    
    printf("Minimum number of j to reach end is %d ", jump(a, 0, n - 1));
    return 0;
}