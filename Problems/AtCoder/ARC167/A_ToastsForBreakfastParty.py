#!/usr/bin/python3

N, M = map(int, input().split())
A = list(map(int, input().split()))

A.sort()
# print("after sorting: a = ", end="")
# print(A)

n_doubles = N - M
n_singles = M - n_doubles

# print(n_doubles, n_singles)

total = 0

doubles = A[:n_doubles * 2]
for i in range(len(doubles) // 2):
    total += (doubles[i] + doubles[-1 - i]) ** 2

singles = A[n_doubles * 2:]
for i in singles:
    total += i ** 2

print(total)