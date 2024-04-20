import random
N = random.randint(4, 20)
K = random.randint(20, 20)

print(N, K)
for i in range(K):
    a = random.randint(1, N)
    b = random.randint(1, N)
    print(a, b)