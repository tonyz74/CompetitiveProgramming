print(1)
from random import randint, choice


n = randint(1, 10)
k = randint(1, 10)
m = randint(40, 50)

x = [chr(ord('a') + v) for v in range(k)]

print(n, k, m)
for i in range(m):
    print(choice(x), end="")
print()
