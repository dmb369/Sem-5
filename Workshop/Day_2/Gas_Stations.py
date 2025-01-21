# 1 unit of gas = 1 km

def check(gas, cost):
    tank = 0
    current = 0 
    start = 0

    for i in range(n):
        tank += gas[i] - cost[i]
        current += gas[i] - cost[i]
        if current<0:  start = i+1
        return start if tank >=0 else 0

n = int(input())

gas = list(map(int,input().split()))
cost = list(map(int,input().split()))

ans = check(gas, cost)
print(ans-1)
    



