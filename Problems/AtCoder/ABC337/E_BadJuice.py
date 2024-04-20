import sys
from math import log2, ceil

N = int(input())

# N friends
requests = ceil(log2(N))
print(requests)

for i in range(requests):
    n_juices = 0
    targets = []
    for j in range(1, N + 1):
        if j & (1 << i) != 0:
            # has the ith bit on
            targets.append(j)

    print(len(targets), end=" ") 
    for x in targets:
        print(x, end=" ")
    print()

sys.stdout.flush()

rev = "".join(reversed(input()))
val = int(rev, base=2)

if val == 0:
    print(N)
else:
    print(val)
