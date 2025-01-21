def lsb(a, b):
    if len(a) == 0 or len(b) == 0: return 0
    elif a[0] == b[0]: return 1 + lsb(a[1:], b[1:])
    else: return max(lsb(a[1:], b), lsb(a, b[1:]))

a = str(input())
b = str(input())

ans = lsb(a, b)
print(ans)

# Dynamic Programming Approach
'''
def lcs(a, b):
    n, m = len(a), len(b)
    
    # Create a 2D DP table initialized with 0s
    dp = [[0] * (m + 1) for _ in range(n + 1)]
    
    # Fill the DP table
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if a[i - 1] == b[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    
    # The length of the LCS is in dp[n][m]
    return dp[n][m]

a = str(input())
b = str(input())

ans = lcs(a, b)
print(ans)
'''


