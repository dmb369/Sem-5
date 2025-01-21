def check(p,m,n,mid):
    sr = 1
    curr_sum = 0

    for i in range(n):

        if (p[i] > mid):
            return False
        if (curr_sum + p[i] > mid):
            sr += 1
            curr_sum = p[i]
            if (sr > m):
                return False
        else:
            curr_sum += p[i]

    return True


def pages(p,m,n):

    if (m>n): print(-1)
    
    s = sum(p)
    start, end = 0, s
    res = 10**5

    while (start < end):
        mid = (start+end)//2

        if (check(p,m,n,mid)): 
            res = mid
            end = mid-1 
        else: 
            start = mid + 1

    return res


n = int(input("Enter the number of books: "))
m = int(input("Enter the number of students: "))
p = list(map(int, input().split()))

print(pages(p,m,n))

