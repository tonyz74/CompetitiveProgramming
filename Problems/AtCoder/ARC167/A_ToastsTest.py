from itertools import permutations

x = [8, 9, 10, 11, 12, 13]

min_val = 1e100
best = []
for i in permutations(x):
    ver = list(i)
    candidate = (ver[0] + ver[1]) ** 2 + (ver[2] + ver[3]) ** 2 + (ver[4] + ver[5]) ** 2
    if (candidate < min_val):
        best = list(ver)
        min_val = candidate
        print(best)

print(min_val)
print(best)
