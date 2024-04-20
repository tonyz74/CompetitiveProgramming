from random import randint
N = randint(5, 10)
A = randint(4, 6)
B = randint(4, 6)

print(N, A, B)

a = []
for i in range(N):
    a.append(randint(0, 10) * A)
a = sorted(a)

for i in range(N):
    print(a[i], end=" ")
print()