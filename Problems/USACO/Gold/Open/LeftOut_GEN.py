from random import randint, choice

N = randint(2, 10)
print(N)

x = ['R', 'L']
for i in range(N):
    for j in range(N):
        print(choice(x), end="")
    print()