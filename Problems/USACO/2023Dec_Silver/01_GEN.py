from random import randint, shuffle

N = randint(4, 100000)
M = randint(4, 240)
K = randint(2, 140)

weights = [i for i in range(1, N * 4)]
shuffle(weights)

print(N, M, K)
for i in range(N):
    print(weights[i], randint(1, 14))
