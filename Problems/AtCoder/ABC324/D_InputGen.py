import random

N = 7
S = ""
for i in range(N):
    S += chr(random.randint(0, 9) + ord('0'))

print(N)
print(S)