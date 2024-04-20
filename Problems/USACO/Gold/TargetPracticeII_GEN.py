from random import randint
T = 1
print(T)

N = randint(400, 2000)
X1 = randint(2000, 4000)

print(N, X1)

for i in range(N):
    bottom = randint(1, int(9e8))
    top = randint(1, int(9e8))

    if bottom == top:
        top += 1
    elif bottom > top:
        top, bottom = bottom, top

    right = randint(X1, X1 + int(9e8))
    print(bottom, top, right)