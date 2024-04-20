import random

N = random.randint(3, 1000)
S = " "
E = [0]

while True:
    S = " "
    E = [0 for i in range(N + 1)]

    seen_H = False

    for i in range(1, N + 1):
        x = random.randint(0, 1)
        if x == 1:
            S += "G"
        else:
            S += "H"
        
        if (i != N):
            E[i] = random.randint(i + 1, N + 1)
        else:
            E[i] = N

        E[i] = min(E[i], N)

    # check
    G_pos = S.find("G")
    H_pos = S.find("H")

    last_G_pos = S.rfind("G")
    last_H_pos = S.rfind("H")

    if (G_pos == -1 or H_pos == -1):
        continue
    
    E[H_pos] = min(last_H_pos + 1, N)
    E[G_pos] = min(last_G_pos + 1, N)

    if (E[G_pos] < last_G_pos and E[H_pos] < last_H_pos):
        continue

    break

print(N)
print(S[1:])

for x in E[1:]:
    print(x, end=" ")
print()