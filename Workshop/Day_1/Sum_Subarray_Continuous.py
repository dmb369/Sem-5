n = int(input('Enter the number of integers:'))
s = int(input('Enter the expected sum:'))

a = list(map(int,input().split()))

for i in range(n):
    k = a[i]

    if (k==s): print(i+1,i+1)
    
    for j in range(i+1, n):
        k = k+a[j]
        if (k==s):
            print(i+1 ,j+1)
            break

if (i==n): print(-1)

        