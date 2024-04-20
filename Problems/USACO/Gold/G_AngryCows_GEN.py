import random
N = random.randint(4, 100)

print(N)

pos = [i for i in range(1, 1000)]
random.shuffle(pos)

for i in range(N):
    print(pos[i])
