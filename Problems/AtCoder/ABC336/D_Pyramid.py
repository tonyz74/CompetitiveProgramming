N = int(input())

if N == 1 or N == 2:
    print(1)
    exit()

A = [int(i) for i in input().split()]

max_pre = [0 for i in range(N)]
max_suf = [0 for i in range(N)]

max_pre[0] = 1
for i in range(1, N):
    max_pre[i] = min(A[i], max_pre[i - 1] + 1)

max_suf[N - 1] = 1
for i in range(N - 2, -1, -1):
    max_suf[i] = min(A[i], max_suf[i + 1] + 1)

ans = -1
for i in range(1, N - 1):
    ans = max(ans, min(max_pre[i], max_suf[i]))

print(ans)
