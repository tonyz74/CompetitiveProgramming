from random import randint, choice, shuffle

print(1)
N = randint(7, 10)
Q = randint(2, N - 3)
C = randint(3, 6)
print(N, Q, C)

choices = [0, 1, 1]
for i in range(N):
    ch = choice(choices)
    val = 0
    if ch == 1:
        val = randint(1, C)

    print(val, end=" ")
print()

a_vals = [i for i in range(1, N - 3 + 1)]
shuffle(a_vals)
for i in range(Q):
    h = randint(a_vals[i] + 1, N)
    print(a_vals[i], h)