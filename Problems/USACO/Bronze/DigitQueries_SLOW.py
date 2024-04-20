S = " "

for i in range(1, 9999):
    S += str(i)

q = int(input())

for i in range(q):
    k = int(input())
    print(S[k])