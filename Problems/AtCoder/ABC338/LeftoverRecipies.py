def read_int_list():
    return [int(i) for i in input().split()]

N = int(input())
Q = read_int_list()
A = read_int_list()
B = read_int_list()

max_a = 1e7

for i in range(N):
    if A[i] != 0:
        max_a = min(max_a, Q[i] // A[i])

max_total = 0
for numA in range(0, max_a + 1):
    rem = list(Q)
    for i in range(N):
        rem[i] -= numA * A[i]

    numB = 1e7
    for i in range(N):
        if B[i] != 0:
            numB = min(rem[i] // B[i], numB)

    # print(numA, numB, rem)
    max_total = max(max_total, numA + numB)

print(max_total)
