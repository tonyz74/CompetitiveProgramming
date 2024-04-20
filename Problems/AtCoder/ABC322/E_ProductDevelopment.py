from functools import cache

N, K, P = map(int, input().split())

INF = 1e18

C = []
A = []
for i in range(N):
    inp = list(map(int, input().split()))
    C.append(inp[0])
    A.append(inp[1:])

@cache
def dfs(x, v):
    if x == N:
        return 0 if all([e == P for e in v]) else INF
    else:
        a = dfs(x + 1, v)
        b = dfs(x + 1, tuple([min(e + A[x][j], P) for j, e in enumerate(v)])) + C[x]
        return min(a, b)
    
val = dfs(0, (0,) * K)
print(-1) if val == INF else print(val)