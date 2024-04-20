from random import randint

n = randint(3, 10)
print(n)

c = randint(1, 10)
for i in range(n):
    c += 1
    print(c, randint(3, 12))