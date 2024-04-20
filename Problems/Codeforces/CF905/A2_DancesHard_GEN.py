print(1)

from random import randint
N = randint(40, 10000)
M = randint(100, 2000)

print(N, M)

for i in range(N - 1):
    print(randint(14, 1000000), end=" ")
print()

for i in range(N):
    print(randint(14, 1000000), end=" ")
print()