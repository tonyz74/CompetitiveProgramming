print(1)

from random import randint, choice

pins = ['<', '>']

N = randint(5, 10)
print(N)
for i in range(N):
    print(choice(pins), end="")
print()