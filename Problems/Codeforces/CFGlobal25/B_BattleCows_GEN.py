print(1)
from random import randint, shuffle
n = randint(10, 1000)
k = randint(1, n)

print(n, k)
x = [i + 1 for i in range(n)]
shuffle(x)
for i in range(n):
    print(x[i], end=" ")
print()