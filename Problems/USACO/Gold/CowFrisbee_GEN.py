import random

N = random.randint(5, 8)
L = [i + 1 for i in range(N)]
random.shuffle(L)

print(N)
for x in L:
    print(x, end=" ")
print()