from random import randint
N = randint(5, 8)
print(1)

b = ""
a = ""
for i in range(N):
    b = b + str(randint(1, 9))
    a = a + str(randint(1, 9))
print(a)
print(b)
