def cycle(u):

    for x in adj[u]:
        if not visited[x]:
            if cycle(x): return True
        elif st[x]: return True
    
    st[u] = False
    return False

v = int(input('Enter the number of vertices: '))
adj = [[] for _ in range(v)]

e = int(input('Enter the number of edges: '))
edges = [list(map(int, input().split())) for _ in range(e)]

for i, j in edges:
    adj[i].append(j)
    adj[j].append(i)

visited = [False] * v
st = [False] * v

for i in range(v):
    
    if not visited[i]:
        visited[i] = True
        st[i] = True

        if cycle(i):
            print("Contains Cycle")
            break
        else:
            print("No Cycle")
            
