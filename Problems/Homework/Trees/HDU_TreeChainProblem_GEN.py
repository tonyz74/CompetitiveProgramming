from random import randint, choice

print(1)
N = 10000
M = 1000
nodes = [i for i in range(1, N + 1)]

print(N, M)

nodes = [i for i in range(1, N + 1)]

unused_nodes = list(nodes)
unused_nodes.remove(1)
tree_nodes = [1]

for i in range(N - 1):
    a = choice(unused_nodes)
    b = choice(tree_nodes)
    print(a, b)
    unused_nodes.remove(a)
    tree_nodes.append(a)

for i in range(M):
    print(choice(nodes), choice(nodes), randint(800, 1000))