from random import randint, shuffle

print(1)
N = randint(30, 30)
print(N)

N_pow2 = randint(0, N)

choices = []
for i in range(N_pow2):
    choices.append((1 << randint(1, 29)))

for i in range(N - N_pow2):
    choices.append(randint(1, (int(1e9))))

shuffle(choices)
for i in range(N):
    print(choices[i], end=" ")
print()