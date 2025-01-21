n = int(input('Enter the number of integers:'))
a = list(map(int,input().split()))

for i in range(n):
    for j in range(i+1, n):
        s = -a[i] - a[j]
        k = a[j+1:n+1]
        if (s in k):
            print(1)
            break

if (i==n): print(0)