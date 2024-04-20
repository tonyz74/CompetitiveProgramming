from random import randint, shuffle
L = randint(8, 90)
N = randint(4, L - 1)

x = [i for i in range(1, L + 1)]
shuffle(x)

print(N, L)
for i in range(N):
    d = randint(0, 1)
    if d == 0:
        d = -1
    print(1, x[i], d)
