from random import randint, choice

N = randint(4, 20)
print(N)
for i in range(N):
    print(randint(4, 12), end=" ")
print()

colors = []
for i in range(N):
    color = randint(1, 10)
    colors.append(color)
    print(color, end=" ")
print()

Q = randint(4, 10)
print(Q)

for i in range(Q):
    print(randint(1, 2), choice(colors), randint(10, 20))