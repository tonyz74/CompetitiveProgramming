from random import randint

x = randint(8, 16)
print(x, end=' ')

p = randint(3, 8)

print(p)

for i in range(1, x + 1):
    print(i, end=' ')
print()

for k in range(p):
    if k % 2 == 0:
        l = randint(1, 5)
        print(1, l, randint(l + 1, x), randint(4, 10), randint(4, 10))
    else:
        print(2, randint(1, x))