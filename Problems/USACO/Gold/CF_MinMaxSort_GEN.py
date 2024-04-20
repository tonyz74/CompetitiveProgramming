from random import randint, shuffle
print(1)
N = randint(5, 7)
print(N)
v = [i + 1 for i in range(N)]
shuffle(v)
for i in v:
    print(i, end=" ")
print()