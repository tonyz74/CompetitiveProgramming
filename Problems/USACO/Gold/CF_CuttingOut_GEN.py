from random import randint, choice
N = randint(10, 20)
K = randint(4, N - 1)
print(N, K)

x = []

for i in range(randint(7, N)):
    x.append(randint(1, 40))

for i in range(N):
    print(choice(x))