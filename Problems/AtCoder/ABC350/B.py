N, Q = [(int(i)) for i in input().split()]

teeth = [1 for i in range(N)]

T = [int(i) - 1 for i in input().split()]

for pos in T:
    if teeth[pos] == 1:
        teeth[pos] = 0
    else:
        teeth[pos] = 1

s = 0
for i in teeth:
    s += i

print(s)