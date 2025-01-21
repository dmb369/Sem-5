#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// I am using a dynamic porgramming approach here
int mn(int a, int b, int c) 
{
    if (a < b) return (a < c) ? a : c;
    else return (b < c) ? b : c;
}

int mo(const char* a, const char* b) {
    int m = strlen(a);
    int n = strlen(b);
    
    // Using a dynamic memory allocation
    int arr[m][n];
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) 
        {
            if (i == 0) arr[i][j] = j; 
            else if (j == 0) arr[i][j] = i; 
            else if (a[i - 1] == b[j - 1]) 
                arr[i][j] = arr[i - 1][j - 1];
            else arr[i][j] = 1 + mn(arr[i][j - 1], arr[i - 1][j], arr[i - 1][j - 1]); 
        }
    }

    int ans = arr[m][n]; 

    return ans;
}

int main() 
{
    char a[100], b[100];   //Here, I am assuming that string length is not more than 100 
    printf("Enter 1st string: ");
    scanf("%s", a);
    printf("Enter 2nd string: ");
    scanf("%s", b);

    int ans = mo(a, b);
    printf("The minimum operations that are required are %d\n", ans);

    return 0;
}
