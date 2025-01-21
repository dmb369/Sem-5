# include<stdio.h>

int find(int a[], int l, int h, int n)
{
    int mid = (l + h)/2;

    if (((mid==0) || (a[mid-1] <= a[mid])) && ((mid==n-1) || (a[mid] >= a[mid+1]))) return mid;
    else if ((mid>0) && (a[mid-1] > a[mid])) return find(a,l,mid-1,n);
    else return find(a,mid+1,h,n);
}

int main()
{
    int n;
    printf("Enter the size of the array:");
    scanf("%d", &n);

    int a[n];
    for (int i=0; i<n; i++) scanf("%d", &a[i]);

    int peak = find(a, 0 ,n-1, n);
    printf("%d", a[peak]);
    return 0;
}