T = [int(i) for i in input().split()]
A = [int(i) for i in input().split()]

tscore = 0
for i in T:
    tscore += i

ascore = 0
for j in A:
    ascore += j

print(tscore - ascore + 1)
