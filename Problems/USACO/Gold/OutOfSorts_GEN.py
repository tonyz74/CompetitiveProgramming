import random

l = [i for i in range(1, 14)]
random.shuffle(l)

for i in range(18):
    l.append(random.randint(1, 9))

print(len(l))
for i in l:
    print(i)