from random import randint, shuffle

N = randint(25, 25)
M = randint(1, N * (N - 1) // 25)

edges = []
for i in range(N):
    for j in range(i + 1, N):
        edges.append((i + 1, j + 1))

shuffle(edges)

print(N, M)
for i in range(M):
    print(edges[i][0], edges[i][1])
