print(1)
from random import randint, shuffle

N = randint(20, 40)
X = randint(2, N - 4)
Y = randint(1, N - X)

print(N, X, Y)
v = [i + 1 for i in range(N)]
shuffle(v)

for i in range(X):
    print(v[i], end=" ")
print()