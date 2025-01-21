#include <stdio.h>

int main()
{
    int n;
    printf("Enter the number of elements in array:");
    scanf("%d",&n);

    int a[n];
    for (int i=0; i<n; i++) scanf("%d", &a[i]);

    int j=0, k=n-1;
    int max = a[k]+1;

    for (int i=0; i<n; i++)
    {
        if (i%2==0)
        {
            a[i] = a[i] + (a[k]%max) * max;
            k--;
        }

        else
        {
            a[i] = a[i] + (a[j]%max) * max;
            j++;
        }
    }

    for (int i=0; i<n; i++)
    {
        a[i]/=max;
    }

    for (int i=0; i<n; i++) printf("%d ", a[i]);
}