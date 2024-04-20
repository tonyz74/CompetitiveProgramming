from random import randint

N = randint(20, 50)
K = randint(10, 20)
L = randint(10, 20)

print(N, K, L)

for i in range(N):
    print(randint(0, 15), end=" ")
print()