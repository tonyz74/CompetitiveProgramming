from random import randint
N = randint(1, 500)
M = randint(1, 500)

print(N, M)
for i in range(M):
    print(randint(1, N + 1), randint(1, N + 1))