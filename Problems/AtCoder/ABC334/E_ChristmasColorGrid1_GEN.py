from random import randint

H = randint(800, 900)
W = randint(800, 900)
print(H, W)
for i in range(H):
    for j in range(W):
        v = randint(0, 1)
        if v == 0:
            print('#', end="")
        else:
            print('.', end="")
    print()