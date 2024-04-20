N, K = [int(i) for i in input().split()]
A = [int(i) for i in input().split()]

A = list(set(A))
A.sort()
all_sum = (K * (K + 1)) // 2;

for i in A:
    if (i <= K):
        all_sum -= i

print(all_sum)