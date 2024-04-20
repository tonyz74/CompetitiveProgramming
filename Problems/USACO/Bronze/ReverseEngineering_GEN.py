import random
N = 14

print(1)
print(N, 8)

cmps = []
choices = random.randint(4, N - 2)

for i in range(choices):
    rand_idx = random.randint(0, N - 1)
    rand_val = random.randint(0, 1)
    rand_output = random.randint(0, 1)
    cmps.append((rand_idx, rand_val, rand_output))

def program(data):
    for (i, v, o) in cmps:
        if data[i] == v:
            return o

    return 0

for i in range(8):
    S = []
    DSP = ""
    for j in range(N):
        S.append(random.randint(0, 1))
        DSP += str(S[-1])
    
    print(DSP, program(S))