#include <stdio.h>

long long find(int a) 
{
    if (a == 0) return 1;  
    if (a == 1) return 1;  
    if (a == 2) return 2;  
    
    long long dp[a + 1]; 
    dp[0] = 1;            
    dp[1] = 1;           
    dp[2] = 2;            

    for (int i = 3; i <= a; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2] + dp[i - 3]) % (1000000007);  
    }
    
    return dp[a];  
}

int main() {
    int a;
    printf("Enter the value of N: ");
    scanf("%d", &a);
    int n = find(a);
    printf("%d",n);

    return 0;
}
