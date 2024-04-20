import random

out = ""

for i in range(4):
    l = random.randint(1, 3)
    val = random.randint(0, 1)

    for i in range(l):
        out += "%s" % val

print(len(out))
print(out)