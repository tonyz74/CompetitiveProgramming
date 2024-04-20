from random import randint
N = randint(4000, 4000)
K = randint(2, N)

print(N, K)

for i in range(N):
    print(randint(1000, 200000), end=" ")
print()
