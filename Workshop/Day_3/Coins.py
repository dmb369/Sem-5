def coins(c, t):
    dp = [10**9 for i in range(t+1)]
    dp[0] = 0

    for i in range(len(c)):
        for j in range(c[i], t+1):  
            dp[j] = min(dp[j], dp[j-c[i]] + 1)

    if dp[t] == 10**9:
        return -1
    else:
        return dp[t]

coin = list(map(int, input("Enter the coin denominations: ").split()))
target = int(input("Enter the target amount: "))

print(coins(coin, target))
