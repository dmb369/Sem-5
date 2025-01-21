#include <stdio.h>

// I am using a dynamic programming approach here
int rod(int p[], int n) 
{
    int a[n+1];
    a[0] = 0; 

   
    for (int i=1; i<=n; i++) {
        int m=0; 
        for (int j=0; j<i; j++) 
        {
            if (m < p[j]+a[i-j-1])   m = p[j]+a[i-j-1];
            a[i] = m;
        }
    }

    return a[n];
}

void main() 
{
    int n; 
    printf("Length of the rod: ");
    scanf("%d", &n);

    int p[n];
    printf("Prices for lengths 1 to %d: ", n);
    for (int i=0; i<n; i++)  scanf("%d", &p[i]);

    int mp = rod(p, n);
    printf("The maximum value one can get is %d\n", mp);
}
