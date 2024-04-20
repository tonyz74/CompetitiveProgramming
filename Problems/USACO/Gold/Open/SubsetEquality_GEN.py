from random import randint, choice
N = randint(4, 10)
letters = [chr(i) for i in range(ord('a'), ord('r') + 1)]

S = []
T = []
for i in range(N):
    S.append(choice(letters))
    T.append(choice(letters))

S = "".join(S)
T = "".join(T)

print(S)
print(T)

Q = randint(10, 20)
print(Q)
for q in range(Q):
    cnt = randint(1, 18)
    subset = list(letters)[:cnt]
    print("".join(subset))