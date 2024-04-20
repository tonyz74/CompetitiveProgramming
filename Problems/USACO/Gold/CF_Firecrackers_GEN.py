print(1)
from random import randint
N = randint(7, 12)
M = randint(3, 4)
A = randint(2, 4)
B = randint(A + 2, N)

print(N, M, A, B)
for i in range(M):
    print(randint(1, 4))
