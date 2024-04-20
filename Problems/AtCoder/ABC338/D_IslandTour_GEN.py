from random import randint
N = randint(50, 100)
M = randint(N - 4, N + 2)
print(N, M)
for i in range(M):
    print(randint(1, N))