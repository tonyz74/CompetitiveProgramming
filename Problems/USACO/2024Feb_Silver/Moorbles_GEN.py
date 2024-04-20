from random import randint
from random import shuffle

print(1)
N = randint(4, 10)
M = randint(4, 5)
K = randint(2, 4)

print(N, M, K)
for i in range(M):
    cho = [i + 1 for i in range(4)]
    shuffle(cho)

    for j in range(K):
        print(cho[j], end=" ")
    print()