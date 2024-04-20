from random import randint

N = randint(40, 400)
M = randint(40, 400)

print(N, M)
for i in range(N):
    a = randint(1, M - 1)
    b = randint(1, M - 1)
    if a == b:
        b += 1
    print(a, b)