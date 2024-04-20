from random import randint

N = randint(20, 30)
M = randint(2, N)

print(N, M)
for i in range(N):
    print(randint(0, 100), end=" ")
print()

for i in range(M):
    print(randint(0, N-1), end=" ")
print()
