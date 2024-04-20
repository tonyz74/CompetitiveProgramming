from random import randint, shuffle

print(1)
N = randint(1, 14)
print(N)
x = [i for i in range(N)]

shuffle(x)
for i in range(N):
    print(x[i], end=" ")
print()