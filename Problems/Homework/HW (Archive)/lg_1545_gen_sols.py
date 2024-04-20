from random import randint

N = 4
L = 16

print(N, L)

A = randint(1, L // 2)
B = A + 1
print(A, B)

for i in range(N):
    S = randint(1, L // 4)
    E = randint(S + 1, S + 5)
    print(S, E)